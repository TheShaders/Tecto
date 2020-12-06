#include <physics.h>
#include <collision.h>
#include <ecs.h>
#include <mathutils.h>
#include <config.h>

#define ARCHETYPE_POSVEL (Bit_Position | Bit_Velocity)
#define ARCHETYPE_GRAVITY (Bit_Velocity | Bit_Gravity)

void applyGravityCallback(size_t count, UNUSED void *arg, void **componentArrays)
{
    // Components: Velocity, Gravity
    Vec3 *curVel = componentArrays[COMPONENT_INDEX(Velocity, ARCHETYPE_GRAVITY)];
    GravityParams *gravity = componentArrays[COMPONENT_INDEX(Gravity, ARCHETYPE_GRAVITY)];

    while (count)
    {
        (*curVel)[1] += gravity->accel;

        if ((*curVel)[1] < gravity->terminalVelocity)
        {
            (*curVel)[1] = gravity->terminalVelocity;
        }
        
        curVel++;
        gravity++;
        count--;
    }
}

void applyVelocityCallback(size_t count, UNUSED void *arg, void **componentArrays)
{
    // Components: Position, Velocity
    Vec3 *curPos = componentArrays[COMPONENT_INDEX(Position, ARCHETYPE_POSVEL)];
    Vec3 *curVel = componentArrays[COMPONENT_INDEX(Velocity, ARCHETYPE_POSVEL)];

    while (count)
    {
        VEC3_ADD(*curPos, *curPos, *curVel);

        curPos++;
        curVel++;
        count--;
    }
}

void physicsTick(void)
{
    // Apply gravity to all objects that are affected by it
    iterateOverEntities(applyGravityCallback, NULL, ARCHETYPE_GRAVITY, 0);
    // Apply every object's velocity to their position
    iterateOverEntities(applyVelocityCallback, NULL, ARCHETYPE_POSVEL, 0);

    // Resolve intersections
    // TODO resolve intersections
}
