#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <types.h>
#include <stdint.h>

typedef struct PlayerState_t
{
    Entity *playerEntity;
    u8 state;
    u8 subState;
    u16 stateArg;
    Entity *heldEntity;
} PlayerState;

#define MAX_PLAYER_SPEED 8.0f
#define MAX_PLAYER_SPEED_SQ POW2(MAX_PLAYER_SPEED)
#define INV_MAX_PLAYER_SPEED_SQ (1.0f / MAX_PLAYER_SPEED_SQ)
#define PLAYER_AIR_ACCEL_TIME_CONST (0.025f)
#define PLAYER_GROUND_ACCEL_TIME_CONST (0.2f)
#define PLAYER_CAMERA_TURN_SPEED 0x100

// Size of player's "hitbox"
#define PLAYER_HEIGHT 180.0f
#define PLAYER_RADIUS 50.0f
// Number of times to cast the radial rays
#define PLAYER_WALL_RAYCAST_HEIGHT_COUNT 3
#define PLAYER_GRAVITY 1.0f

void createPlayer(PlayerState *state);
void createPlayerCallback(size_t count, void *arg, void **componentArrays);
void playerCallback(void **components, void *data);

// Player states
#define PSTATE_GROUND 0
#define PSTATE_AIR    1

// Ground substates
#define PGSUBSTATE_STANDING 0
#define PGSUBSTATE_WALKING  1
#define PGSUBSTATE_JUMPING  2

// Air substates
#define PASUBSTATE_FALLING  0
#define PASUBSTATE_JUMPING  1

#endif
