#include <ultra64.h>
#include <mem.h>

static u8* segmentTable[SEGMENT_COUNT];

void setSegment(u32 segmentIndex, void* virtualAddress)
{
    segmentTable[segmentIndex] = (u8*) virtualAddress;
}

void* segmentedToVirtual(void* segmentedAddress)
{
    u32 segmentIndex = (u32)segmentedAddress >> 24;
    if (segmentIndex == 0x80)
        return segmentedAddress;
    return segmentTable[segmentIndex] + ((u32)segmentedAddress & 0xFFFFFF);
}
