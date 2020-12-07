#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include <types.h>

#define GRAVITY (-16.67f)

// Max step up and down heights for objects
#define MAX_STEP_UP   20.0f
#define MAX_STEP_DOWN 20.0f

typedef struct GravityParams_t {
    float accel;
    float terminalVelocity;
} GravityParams;

typedef struct HoldState_t {
    Entity *holder;
} HoldState;

typedef struct HoldOffset_t {
    Vec3 holdOffset;
} HoldOffset;

void physicsTick(void);

#endif
