#include <ultra64.h>
#include <mem.h>
#include <stdint.h>
#include <string.h>

static uintptr_t segmentTable[SEGMENT_COUNT];

void setSegment(u32 segmentIndex, void* virtualAddress)
{
    segmentTable[segmentIndex] = (uintptr_t) virtualAddress;
}

void* segmentedToVirtual(void* segmentedAddress)
{
    u32 segmentIndex = (uintptr_t)segmentedAddress >> 24;
    if (segmentIndex == 0x80)
        return segmentedAddress;
    return (void*)(segmentTable[segmentIndex] + ((uintptr_t)segmentedAddress & 0xFFFFFF));
}

// Pointer to the start of an array with an owner_t for each chunk representing
// what it was allocated by, or 0 if free
owner_t *chunkTable;

// The address of the first memory chunk
uintptr_t chunksStart = NULL;

// The number of memory chunks
int totalChunks = 0;

// Index of the first free chunk
int firstFreeChunk = 0;

#define CHUNK_ADDR_FROM_INDEX(i) ((void*)(chunksStart + (i) * MEM_CHUNK_SIZE))

// Initializes the memory allocation settings (chunk table, number of chunks, first chunk address)
void initMemAllocator(void *start, void *end)
{
    // Calculate the number of chunks in the available memory
    // This is equal to the available memory divided by the chunk size plus the size of an owner, since
    // an extra owner value is needed for each chunk in the chunk table
    totalChunks = ((uintptr_t)end - (uintptr_t)start) / (MEM_CHUNK_SIZE + sizeof(owner_t));
    chunksStart = (uintptr_t)end - (totalChunks * MEM_CHUNK_SIZE);
    chunkTable = start;

    bzero(chunkTable, totalChunks);
}

void updateFirstFreeChunk(int startIndex)
{
    int i;
    owner_t* chunkTableEntry;
    for (i = startIndex, chunkTableEntry = &chunkTable[i]; i < totalChunks; i++, chunkTableEntry++)
    {
        if (*chunkTableEntry == ALLOC_FREE)
        {
            firstFreeChunk = i;
            return;
        }
    }
    // No free chunks left, set the first chunk index accordingly
    firstFreeChunk = -1;
}

// Allocates a number of contiguous chunks
void *allocChunks(int numChunks, owner_t owner)
{
    int retVal;
    // No free chunks, return NULL
    if (firstFreeChunk == -1)
        return NULL;
    
    // Only allocating 1 chunk, simply return the first free one and update the first free chunk index
    if (numChunks == 1)
    {
        retVal = firstFreeChunk;
        chunkTable[retVal] = owner;
        updateFirstFreeChunk(retVal + 1);
        return CHUNK_ADDR_FROM_INDEX(retVal);
    }
    else
    {
        int i;
        owner_t* chunkTableEntry;
        // Iterate over every chunk starting with the first free one to find a large enough contiguous region of free chunks
        for (i = firstFreeChunk, chunkTableEntry = &chunkTable[i]; i < totalChunks; i++, chunkTableEntry++)
        {
            if (*chunkTableEntry == ALLOC_FREE)
            {
                int j;
                owner_t* jChunkTableEntry;
                for (j = i + 1, jChunkTableEntry = &chunkTable[j]; j < i + numChunks; j++, jChunkTableEntry++)
                {
                    // At the end of the chunk list, not enough room to allocate the given number of chunks
                    if (j >= totalChunks)
                        return NULL;
                    // Contiguous region not available at index i, set i's value to j to skip checking these chunks a second time
                    if (*jChunkTableEntry != ALLOC_FREE)
                    {
                        i = j;
                        chunkTableEntry = jChunkTableEntry;
                        break;
                    }
                }
                // If the inner loop ended and i is not equal to j, then an appropriate region starting at i was found
                if (i != j)
                {
                    // j would be the chunk after the region allocated at this point
                    // Set the owner of the first chunk allocated to the provided owner
                    *chunkTableEntry = owner;
                    // Set all subsequent allocated chunks to be part of the previous chunk
                    for (jChunkTableEntry = &chunkTable[i + 1]; jChunkTableEntry < &chunkTable[j]; jChunkTableEntry++)
                    {
                        *jChunkTableEntry = ALLOC_CONTIGUOUS;
                    }

                    // If we allocated the first free chunk, find a new first free chunk
                    if (i == firstFreeChunk)
                        updateFirstFreeChunk(j);

                    return CHUNK_ADDR_FROM_INDEX(i);
                }
            }
        }
    }
    return NULL;
}

void *allocRegion(int length, owner_t owner)
{
    // Rounded up integer division: (x + (y - 1)) / y
    return allocChunks((length + (MEM_CHUNK_SIZE - 1)) / MEM_CHUNK_SIZE, owner);
}

void freeAlloc(void *start)
{
    // Calculate the index of the chunk provided
    int chunkIndex = ((uintptr_t)start - chunksStart) / MEM_CHUNK_SIZE;
    owner_t *chunkTableEntry;

    // Free the chunk
    chunkTable[chunkIndex] = ALLOC_FREE;

    // Free any other chunks included in this allocation (subsequent chunks with owner ALLOC_CONTIGUOUS)
    for (chunkTableEntry = &chunkTable[chunkIndex + 1]; chunkTableEntry < &chunkTable[totalChunks]; chunkTableEntry++)
    {
        if (*chunkTableEntry == ALLOC_CONTIGUOUS)
        {
            *chunkTableEntry = ALLOC_FREE;
        }
        else
        {
            break;
        }
    }

    // If this is the new first free chunk, set it to be so
    if (chunkIndex < firstFreeChunk)
        firstFreeChunk = chunkIndex;
}
