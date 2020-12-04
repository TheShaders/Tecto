#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <types.h>

#define MAX_STEP_HEIGHT 30.0f
#define MAX_PLAYER_SPEED 4.0f
#define MAX_PLAYER_SPEED_SQ POW2(MAX_PLAYER_SPEED)
#define INV_MAX_PLAYER_SPEED_SQ (1.0f / MAX_PLAYER_SPEED_SQ)
#define PLAYER_AIR_ACCEL_TIME_CONST (0.025f)
#define PLAYER_GROUND_ACCEL_TIME_CONST (0.2f)
#define PLAYER_CAMERA_TURN_SPEED 0x100

// Size of player's "hitbox"
#define PLAYER_HEIGHT 180.0f
#define PLAYER_RADIUS 50.0f
#define PLAYER_GRAVITY 1.0f

// Offset from the player's position to start the downward ground raycast
#define PLAYER_GROUND_RAYCAST_OFFSET 50.0f
// Minimum length of the ray to cast downward to find ground (added to y velocity)
#define PLAYER_GROUND_RAYCAST_MIN_LENGTH 30.0f
// Max step up and down heights
#define PLAYER_MAX_STEP_UP   30.0f
#define PLAYER_MAX_STEP_DOWN 30.0f
// Number of radial rays to cast to find walls
#define PLAYER_WALL_RAYCAST_RADIAL_COUNT 16
// Number of times to cast the radial rays
#define PLAYER_WALL_RAYCAST_HEIGHT_COUNT 3

void createPlayer(void);
void createPlayerCallback(size_t count, void *arg, void **componentArrays);
void playerCallback(void **components, void *data);

#endif
