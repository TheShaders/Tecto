#include <physics.h>
#include <collision.h>
#include <ecs.h>
#include <mathutils.h>
#include <config.h>

#define ARCHETYPE_POSVEL      (Bit_Position | Bit_Velocity)
#define ARCHETYPE_HOLDPOSVEL  (Bit_Position | Bit_Velocity | Bit_Holdable)
#define ARCHETYPE_GRAVITY     (Bit_Velocity | Bit_Gravity)
#define ARCHETYPE_HOLDGRAVITY (Bit_Velocity | Bit_Gravity | Bit_Holdable)
#define ARCHETYPE_HOLDER      (Bit_Position | Bit_Velocity | Bit_Holder)
#define ARCHETYPE_COLLIDER    (Bit_Position | Bit_Velocity | Bit_Collider)

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

void applyHoldableGravityCallback(size_t count, UNUSED void *arg, void **componentArrays)
{
    // Components: Velocity, Gravity, Holdable
    Vec3 *curVel = componentArrays[COMPONENT_INDEX(Velocity, ARCHETYPE_HOLDGRAVITY)];
    GravityParams *curGravity = componentArrays[COMPONENT_INDEX(Gravity, ARCHETYPE_HOLDGRAVITY)];
    HoldState *curHoldState = componentArrays[COMPONENT_INDEX(Holdable, ARCHETYPE_HOLDGRAVITY)];

    while (count)
    {
        if (curHoldState->holder == NULL)
        {
            (*curVel)[1] += curGravity->accel;

            if ((*curVel)[1] < curGravity->terminalVelocity)
            {
                (*curVel)[1] = curGravity->terminalVelocity;
            }
        }
        
        curVel++;
        curGravity++;
        curHoldState++;
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

void applyHoldableVelocityCallback(size_t count, UNUSED void *arg, void **componentArrays)
{
    // Components: Position, Velocity, Holdable
    Vec3 *curPos = componentArrays[COMPONENT_INDEX(Position, ARCHETYPE_HOLDPOSVEL)];
    Vec3 *curVel = componentArrays[COMPONENT_INDEX(Velocity, ARCHETYPE_HOLDPOSVEL)];
    HoldState *curHeldState = componentArrays[COMPONENT_INDEX(Holdable, ARCHETYPE_HOLDPOSVEL)];

    while (count)
    {
        if (curHeldState->holder == NULL)
        {
            VEC3_ADD(*curPos, *curPos, *curVel);
        }
        else
        {
            // Array of component pointers for the holding entity (position, rotation, holder)
            void *holderComponents[NUM_COMPONENTS(ARCHETYPE_HOLDER)];
            // TODO Set position held entity's position + their hold offset rotated by their rotation
        }

        curPos++;
        curVel++;
        curHeldState++;
        count--;
    }
}

void resolveCollisionsCallback(size_t count, UNUSED void *arg, void **componentArrays)
{
    // Components: Position, Velocity, Collider
    Vec3 *curPos = componentArrays[COMPONENT_INDEX(Position, ARCHETYPE_COLLIDER)];
    Vec3 *curVel = componentArrays[COMPONENT_INDEX(Velocity, ARCHETYPE_COLLIDER)];
    ColliderParams *curCollider = componentArrays[COMPONENT_INDEX(Collider, ARCHETYPE_COLLIDER)];

    while (count)
    {
        // Handle wall collision (since it's universal across states currently)
        handleWalls(*curPos, *curVel, curCollider);
        if (curCollider->floor != NULL)
        {
            curCollider->floor = handleFloorOnGround(*curPos, *curVel, MAX_STEP_UP, MAX_STEP_DOWN);
        }
        else
        {
            curCollider->floor = handleFloorInAir(*curPos, *curVel);
        }

        curPos++;
        curVel++;
        curCollider++;
        count--;
    }
}

void physicsTick(void)
{
    // Apply gravity to all objects that are affected by it and cannot be held
    iterateOverEntities(applyGravityCallback, NULL, ARCHETYPE_GRAVITY, Bit_Holdable);
    // Apply gravity to all holdable objects if they aren't being held
    iterateOverEntities(applyHoldableGravityCallback, NULL, ARCHETYPE_HOLDGRAVITY, 0);
    // Apply every non-holdable object's velocity to their position
    iterateOverEntities(applyVelocityCallback, NULL, ARCHETYPE_POSVEL, Bit_Holdable);
    // Apply every holdable object's velocity to their position if they aren't being held
    iterateOverEntities(applyHoldableVelocityCallback, NULL, ARCHETYPE_HOLDPOSVEL, 0);

    // Resolve intersections
    iterateOverEntities(resolveCollisionsCallback, NULL, ARCHETYPE_COLLIDER, 0);
}
