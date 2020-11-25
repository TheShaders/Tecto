#include <multiarraylist.h>
#include <mem.h>
#include <ecs.h>

// For bzero, MIN
#include <ultra64.h>

// Seems like the best option because it doesn't require a lookup table (slow ram performance)
// or multiplication (delay slots)
// https://stackoverflow.com/questions/757059/position-of-least-significant-bit-that-is-set
int lowest_bit(u32 value)
{
    int i16 = !(value & 0xffff) << 4;
    value >>= i16;

    int i8 = !(value & 0xff) << 3;
    value >>= i8;

    int i4 = !(value & 0xf) << 2;
    value >>= i4;

    int i2 = !(value & 0x3) << 1;
    value >>= i2;

    int i1 = !(value & 0x1);

    return i16 + i8 + i4 + i2 + i1;
}

void multiarraylist_init(MultiArrayList *arr, archetype_t archetype)
{
    size_t totalElementSize = 0;
    archetype_t archetypeShifted;
    int i;

    archetypeShifted = archetype;

    for (i = 0; i < NUM_COMPONENT_TYPES; i++)
    {
        if (archetypeShifted & 0x01)
        {
            totalElementSize += g_componentSizes[i];
        }
        archetypeShifted >>= 1;
    }

    arr->archetype = archetype;
    arr->totalElementSize = totalElementSize;
    arr->elementCount = ROUND_DOWN((MEM_CHUNK_SIZE - sizeof(MultiArrayListBlock)) / totalElementSize, 4);
    arr->end = arr->start = (MultiArrayListBlock*) allocChunks(1, ALLOC_ECS);
    bzero(arr->start, MEM_CHUNK_SIZE);
}

void multiarraylist_alloccount(MultiArrayList *arr, size_t count)
{
    size_t elementCount = arr->elementCount;
    size_t remainingInCurrentBlock = elementCount - arr->end->numElements;
    if (count < remainingInCurrentBlock)
    {
        arr->end->numElements += count;
    }
    else
    {
        arr->end->numElements = elementCount;
        count -= remainingInCurrentBlock;
        while (count > 0)
        {
            MultiArrayListBlock *newSeg = (MultiArrayListBlock*) allocChunks(1, ALLOC_ECS);
            bzero(newSeg, MEM_CHUNK_SIZE);

            arr->end->next = newSeg;
            arr->end = newSeg;
            
            newSeg->numElements = MIN(count, elementCount);
            count -= newSeg->numElements;
        }
    }
}

size_t multiarraylist_get_component_offset(MultiArrayList *arr, size_t componentIndex)
{
    archetype_t archetype = arr->archetype;
    size_t elementCount = arr->elementCount;
    size_t offset = sizeof(MultiArrayListBlock); // The arrays start after the segment header
    size_t curComponentType;

    // Iterate over each component in the archetype until we reach the provided one
    // If the current component being iterated over isn't the provided one, increase the offset by the component's array size
    while ((curComponentType = lowest_bit(archetype)) != componentIndex)
    {
        offset += g_componentSizes[curComponentType] * elementCount;
        archetype &= ~(1 << curComponentType);
    }
    return offset;
}
