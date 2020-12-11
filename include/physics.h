#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include <types.h>

#define GRAVITY (-16.67f)

// Max step up and down heights for objects
#define MAX_STEP_UP   50.0f
#define MAX_STEP_DOWN 20.0f

typedef enum HoldType_t {
    HOLD_NORMAL, // Standard holdable object
    HOLD_GLIDE, // Holdable object that allows you to glide
} HoldType;

typedef struct GravityParams_t {
    float accel;
    float terminalVelocity;
} GravityParams;

typedef struct HoldState_t {
    Entity *holder;
    HoldType type;
} HoldState;

typedef struct HoldOffset_t {
    Vec3 holdOffset;
} HoldOffset;

void physicsTick(void);

#endif
