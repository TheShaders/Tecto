#include <physics.h>
#include <collision.h>
#include <ecs.h>
#include <mathutils.h>
#include <config.h>

#define ARCHETYPE_POSVEL       (Bit_Position | Bit_Velocity)
#define ARCHETYPE_GRAVITY      (Bit_Velocity | Bit_Gravity)
#define ARCHETYPE_HOLDGRAVITY  (Bit_Velocity | Bit_Gravity | Bit_Holdable)
#define ARCHETYPE_HOLDABLEVEL  (Bit_Position | Bit_Velocity | Bit_Rotation | Bit_Holdable)
#define ARCHETYPE_COLLIDER     (Bit_Position | Bit_Velocity | Bit_Collider)
#define ARCHETYPE_HELDCOLLIDER (Bit_Position | Bit_Velocity | Bit_Collider | Bit_Holdable)

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

extern void debug_printf(const char* message, ...);

void applyHoldableVelocityCallback(size_t count, UNUSED void *arg, void **componentArrays)
{
    // Components: Position, Velocity, Rotation, Holdable
    Vec3 *curPos = componentArrays[COMPONENT_INDEX(Position, ARCHETYPE_HOLDABLEVEL)];
    Vec3 *curVel = componentArrays[COMPONENT_INDEX(Velocity, ARCHETYPE_HOLDABLEVEL)];
    Vec3s *curRot = componentArrays[COMPONENT_INDEX(Rotation, ARCHETYPE_HOLDABLEVEL)];
    HoldState *curHeldState = componentArrays[COMPONENT_INDEX(Holdable, ARCHETYPE_HOLDABLEVEL)];

    while (count)
    {
        if (curHeldState->holder == NULL)
        {
            VEC3_ADD(*curPos, *curPos, *curVel);
        }
        else
        {
            archetype_t holderArchetype = curHeldState->holder->archetype;
            // Array of component pointers for the holding entity (position, rotation, holder)
            void *holderComponents[NUM_COMPONENTS(holderArchetype)];
            Vec3 *holderPos;
            Vec3 *holderVel;
            Vec3s *holderRot;
            HoldOffset *holderOffset;
            MtxF holderRotMatrix;
            Vec3 rotatedOffset;
            // TODO Set position held entity's position + their hold offset rotated by their rotation
            getEntityComponents(curHeldState->holder, holderComponents);

            holderPos = holderComponents[COMPONENT_INDEX(Position, holderArchetype)];
            holderVel = holderComponents[COMPONENT_INDEX(Velocity, holderArchetype)];
            holderRot = holderComponents[COMPONENT_INDEX(Rotation, holderArchetype)];
            holderOffset = holderComponents[COMPONENT_INDEX(Holder, holderArchetype)];

            mtxfEulerXYZ(holderRotMatrix, (*holderRot)[0], (*holderRot)[1], (*holderRot)[2]);
            mtxfRotateVec(holderRotMatrix, holderOffset->holdOffset, rotatedOffset);
            // VEC3_COPY(rotatedOffset, holderOffset->holdOffset);

            VEC3_ADD(*curPos, *holderPos, rotatedOffset);
            VEC3_COPY(*curRot, *holderRot);
            VEC3_COPY(*curVel, *holderVel);
        }

        curPos++;
        curVel++;
        curRot++;
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
            curCollider->floor = handleFloorOnGround(*curPos, *curVel, MAX_STEP_UP, MAX_STEP_DOWN, &curCollider->floorSurfaceType);
        }
        else
        {
            curCollider->floor = handleFloorInAir(*curPos, *curVel, &curCollider->floorSurfaceType);
        }
        if (curCollider->floor != NULL)
        {
            (*curVel)[0] *= curCollider->frictionDamping;
            (*curVel)[2] *= curCollider->frictionDamping;
        }

        curPos++;
        curVel++;
        curCollider++;
        count--;
    }
}

void resolveHoldableCollisionsCallback(size_t count, UNUSED void *arg, void **componentArrays)
{
    // Components: Position, Velocity, Collider
    Vec3 *curPos = componentArrays[COMPONENT_INDEX(Position, ARCHETYPE_HELDCOLLIDER)];
    Vec3 *curVel = componentArrays[COMPONENT_INDEX(Velocity, ARCHETYPE_HELDCOLLIDER)];
    ColliderParams *curCollider = componentArrays[COMPONENT_INDEX(Collider, ARCHETYPE_HELDCOLLIDER)];
    HoldState *curHeldState = componentArrays[COMPONENT_INDEX(Holdable, ARCHETYPE_HELDCOLLIDER)];

    while (count)
    {
        if (curHeldState->holder == NULL)
        {
            // Handle wall collision (since it's universal across states currently)
            handleWalls(*curPos, *curVel, curCollider);
            if (curCollider->floor != NULL)
            {
                curCollider->floor = handleFloorOnGround(*curPos, *curVel, MAX_STEP_UP, MAX_STEP_DOWN, &curCollider->floorSurfaceType);
            }
            else
            {
                curCollider->floor = handleFloorInAir(*curPos, *curVel, &curCollider->floorSurfaceType);
            }
            if (curCollider->floor != NULL)
            {
                (*curVel)[0] *= curCollider->frictionDamping;
                (*curVel)[2] *= curCollider->frictionDamping;
            }
        }

        curPos++;
        curVel++;
        curCollider++;
        curHeldState++;
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
    // Apply every holdable object's velocity to their position if they aren't being held, otherwise snap them to the holder
    iterateOverEntities(applyHoldableVelocityCallback, NULL, ARCHETYPE_HOLDABLEVEL, 0);

    // Resolve intersections
    iterateOverEntities(resolveCollisionsCallback, NULL, ARCHETYPE_COLLIDER, Bit_Holdable);
    // Resolve intersections for held objects that aren't being held
    iterateOverEntities(resolveHoldableCollisionsCallback, NULL, ARCHETYPE_HELDCOLLIDER, 0);
}
