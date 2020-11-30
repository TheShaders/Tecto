#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <types.h>

#define MAX_STEP_HEIGHT 30.0f
#define MAX_PLAYER_SPEED 4.0f
#define MAX_PLAYER_SPEED_SQ POW2(MAX_PLAYER_SPEED)
#define INV_MAX_PLAYER_SPEED_SQ (1.0f / MAX_PLAYER_SPEED_SQ)
#define PLAYER_ACCEL_TIME_CONST (0.2f)

void createPlayer(void);
void createPlayerCallback(size_t count, void *arg, void **componentArrays);
void playerCallback(void **components, void *data);

#endif
