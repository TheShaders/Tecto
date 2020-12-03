#include <physics.h>
#include <collision.h>
#include <ecs.h>
#include <mathutils.h>
#include <config.h>

#define ARCHETYPE_POSVEL (Bit_Position | Bit_Velocity)

void applyVelocityCallback(size_t count, __attribute__((unused)) void *arg, void **componentArrays)
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
    // Apply every object's velocity to their position
    iterateOverEntities(applyVelocityCallback, NULL, ARCHETYPE_POSVEL, 0);

    // Resolve intersections
    // TODO resolve intersections
}
