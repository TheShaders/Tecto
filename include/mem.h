#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <PR/ultratypes.h>
#include <PR/os_pi.h>

#define SEGMENT_COUNT 32
#define ROUND_UP(val, multiple) (((val) + (multiple) - 1) & ~((multiple) - 1))

extern OSPiHandle *g_romHandle;
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

#endif
