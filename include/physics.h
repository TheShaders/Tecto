#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#define GRAVITY (-16.67f)

typedef struct GravityParams_t {
    float accel;
    float terminalVelocity;
} GravityParams;

void physicsTick(void);

#endif
