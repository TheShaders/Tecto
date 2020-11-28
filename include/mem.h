#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <types.h>
#include <PR/os_pi.h>

#ifdef USE_EXT_RAM
#define MEM_END 0x80800000
#else
#define MEM_END 0x80400000
#endif

typedef u8 owner_t;

// Ids for what system allocated a chunk (owners)
#define ALLOC_FREE       0
#define ALLOC_GFX        1
#define ALLOC_AUDIO      2
#define ALLOC_ECS        3

#define ALLOC_CONTIGUOUS 255 // Allocation from previous chunk

#define MEM_CHUNK_SIZE 65536
#define SEGMENT_COUNT 32
#define ROUND_UP(val, multiple) (((val) + (multiple) - 1) & ~((multiple) - 1))
#define ROUND_DOWN(val, multiple) (((val) / (multiple)) * (multiple))

extern OSPiHandle *g_romHandle;
extern OSMesgQueue siMesgQueue;
extern u8 memPoolStart[];

extern u8 _introSegmentRomStart[];
extern u8 _introSegmentRomEnd[];

extern u8 _mainSegmentBssStart[];
extern u8 _mainSegmentBssEnd[];
extern u8 _gfxSegmentBssStart[];
extern u8 _gfxSegmentBssEnd[];
extern u8 _libultraSegmentBssStart[];
extern u8 _libultraSegmentBssEnd[];

void setSegment(u32 segmentIndex, void* virtualAddress);

void* segmentedToVirtual(void* segmented);

// Set up the memory allocation parameters
void initMemAllocator(void *start, void *end);

// Allocates a given number of contiguous memory chunks, each of size MEM_CHUNK_SIZE
void *allocChunks(int numChunks, owner_t owner);
// Allocates a contiguous region of memory at least as large as the given length
void *allocRegion(int length, owner_t owner);
// Free a region of allocated memory
void freeAlloc(void *start);

#endif
