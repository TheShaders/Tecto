#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <PR/ultratypes.h>
#include <PR/os_pi.h>

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

#endif
