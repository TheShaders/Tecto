#ifndef __MAIN_H__
#define __MAIN_H__

#include <types.h>

void mainThreadFunc(void *);

void startCreditsLoad(void);

extern u32 g_gameTimer; // Counts up every game logic frame (60 fps)
extern u32 g_graphicsTimer; // Counters up every graphics frame (dependent on if FPS30 is set)

#endif