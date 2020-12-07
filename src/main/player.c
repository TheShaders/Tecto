#include <ultra64.h>

#include <player.h>
#include <mem.h>
#include <model.h>
#include <main.h>
#include <input.h>
#include <camera.h>
#include <gfx.h>
#include <ecs.h>
#include <mathutils.h>
#include <collision.h>
#include <debug.h>
#include <physics.h>

extern Model character_model;
extern Animation character_anim_Idle_Long;
extern Animation character_anim_Walk;
extern Animation character_anim_Jump_Start;

void setAnim(AnimState *animState, Animation *newAnim)
{
    newAnim = (Animation *)segmentedToVirtual(newAnim);
    if (animState->anim != newAnim)
    {
        animState->anim = newAnim;
        animState->counter = 0;
        animState->speed = 1 << ANIM_COUNTER_SHIFT;
    }
}

void updateGround(PlayerState *state, InputData *input, UNUSED Vec3 pos, UNUSED Vec3 vel, ColliderParams *collider, UNUSED Vec3s rot, UNUSED AnimState *animState)
{
    if (collider->floor)
    {
        switch (state->subState)
        {
            case PGSUBSTATE_STANDING:
                if (input->buttonsPressed & A_BUTTON)
                    state->subState = PGSUBSTATE_JUMPING;
                else if (input->magnitude)
                    state->subState = PGSUBSTATE_WALKING;
                break;
            case PGSUBSTATE_WALKING:
                if (input->buttonsPressed & A_BUTTON)
                    state->subState = PGSUBSTATE_JUMPING;
                else if (input->magnitude == 0)
                    state->subState = PGSUBSTATE_STANDING;
                break;
            case PGSUBSTATE_JUMPING:
                if (!(input->buttonsHeld & A_BUTTON))
                {
                    state->state = PSTATE_AIR;
                    state->subState = PASUBSTATE_JUMPING;
                }
                break;
        }
    }
    else
    {
        state->state = PSTATE_AIR;
        state->subState = PASUBSTATE_FALLING;
    }
}

void processGround(PlayerState *state, InputData *input, UNUSED Vec3 pos, Vec3 vel, UNUSED ColliderParams *collider, UNUSED Vec3s rot, AnimState *animState)
{
    int adjustAnim = 0;
    float targetSpeed = 0.0f;
    float newSpeed;
    switch (state->subState)
    {
        case PGSUBSTATE_JUMPING:
            setAnim(animState, &character_anim_Jump_Start);
            if (animState->counter >= (23 << ANIM_COUNTER_SHIFT))
            {
                animState->counter = 23 << ANIM_COUNTER_SHIFT;
                animState->speed = 0;
            }
            break;
        case PGSUBSTATE_STANDING:
            adjustAnim = 1;
            break;
        case PGSUBSTATE_WALKING:
            targetSpeed = MAX_PLAYER_SPEED * g_PlayerInput.magnitude;
            adjustAnim = 1;
            break;
    }

    vel[0] = vel[0] * (1.0f - PLAYER_GROUND_ACCEL_TIME_CONST) + targetSpeed * (PLAYER_GROUND_ACCEL_TIME_CONST) * cossf(input->angle + g_Camera.yaw);
    vel[2] = vel[2] * (1.0f - PLAYER_GROUND_ACCEL_TIME_CONST) - targetSpeed * (PLAYER_GROUND_ACCEL_TIME_CONST) * sinsf(input->angle + g_Camera.yaw);

    newSpeed = POW2(vel[0]) + POW2(vel[2]);

    if (adjustAnim)
    {
        if (newSpeed >= POW2(0.1f))
        {
            rot[1] = atan2s(vel[2], vel[0]);
            setAnim(animState, &character_anim_Walk);
            animState->speed = (s16)(sqrtf(newSpeed) * (2.0f * ANIM_COUNTER_FACTOR / MAX_PLAYER_SPEED));
        }
        else
        {
            setAnim(animState, &character_anim_Idle_Long);
            animState->speed = (s16)(1.0f * ANIM_COUNTER_FACTOR);
        }
    }
}

void updateAir(PlayerState *state, InputData *input, UNUSED Vec3 pos, Vec3 vel, ColliderParams *collider, UNUSED Vec3s rot, UNUSED AnimState *animState)
{
    if (state->subState == PASUBSTATE_JUMPING)
    {
        vel[1] = 25.0f;
        if (input->magnitude)
        {
            rot[1] = input->angle + g_Camera.yaw + 0x4000;
            vel[0] = input->magnitude * MAX_PLAYER_SPEED * cossf(input->angle + g_Camera.yaw);
            vel[2] = input->magnitude * -MAX_PLAYER_SPEED * sinsf(input->angle + g_Camera.yaw);
        }
        state->subState = PASUBSTATE_FALLING;
    }
    else
    {
        if (collider->floor)
        {
            state->state = PSTATE_GROUND;
            if (input->magnitude)
                state->subState = PGSUBSTATE_WALKING;
            else
                state->subState = PGSUBSTATE_STANDING;
        }
        else
        {
            switch (state->subState)
            {
                case PASUBSTATE_FALLING: // No state transitions for falling besides landing, which was already handled
                    break;
            }
        }
    }
}

void processAir(PlayerState *state, InputData *input, UNUSED Vec3 pos, Vec3 vel, UNUSED ColliderParams *collider, UNUSED Vec3s rot, AnimState *animState)
{
    float targetSpeed = 0.0f;
    switch (state->subState)
    {
        case PASUBSTATE_JUMPING: // Will never happen
            break;
        case PASUBSTATE_FALLING:
            setAnim(animState, &character_anim_Jump_Start);
            animState->speed = 1 << ANIM_COUNTER_SHIFT;
            if (animState->counter <= (24 << ANIM_COUNTER_SHIFT))
            {
                animState->counter = 24 << ANIM_COUNTER_SHIFT;
            }
            else if (animState->counter >= (animState->anim->frameCount - 2) << ANIM_COUNTER_SHIFT)
            {
                animState->speed = 0;
            }
            targetSpeed = MAX_PLAYER_SPEED * g_PlayerInput.magnitude;
            break;
    }

    vel[0] = vel[0] * (1.0f - PLAYER_AIR_ACCEL_TIME_CONST) + targetSpeed * (PLAYER_AIR_ACCEL_TIME_CONST) * cossf(input->angle + g_Camera.yaw);
    vel[2] = vel[2] * (1.0f - PLAYER_AIR_ACCEL_TIME_CONST) - targetSpeed * (PLAYER_AIR_ACCEL_TIME_CONST) * sinsf(input->angle + g_Camera.yaw);
}

// These functions handle state transitions
void (*stateUpdateCallbacks[])(PlayerState *state, InputData *input, Vec3 pos, Vec3 vel, ColliderParams *collider, Vec3s rot, AnimState *anim) = {
    updateGround, // Ground
    updateAir, // Air
};

// These functions handle the actual state behavioral code
void (*stateProcessCallbacks[])(PlayerState *state, InputData *input, Vec3 pos, Vec3 vel, ColliderParams *collider, Vec3s rot, AnimState *anim) = {
    processGround, // Ground
    processAir, // Air
};

void createPlayer(PlayerState *state)
{
    debug_printf("Creating player entity\n");
    createEntitiesCallback(ARCHETYPE_PLAYER, state, 1, createPlayerCallback);
}

void createPlayerCallback(UNUSED size_t count, void *arg, void **componentArrays)
{
    // Components: Position, Velocity, Rotation, BehaviorParams, Model, AnimState, Gravity
    Vec3 *pos = componentArrays[COMPONENT_INDEX(Position, ARCHETYPE_PLAYER)];
    Vec3s *rot = componentArrays[COMPONENT_INDEX(Rotation, ARCHETYPE_PLAYER)];
    ColliderParams *collider = componentArrays[COMPONENT_INDEX(Collider, ARCHETYPE_PLAYER)];
    BehaviorParams *bhvParams = componentArrays[COMPONENT_INDEX(Behavior, ARCHETYPE_PLAYER)];
    Model **model = componentArrays[COMPONENT_INDEX(Model, ARCHETYPE_PLAYER)];
    GravityParams *gravity = componentArrays[COMPONENT_INDEX(Gravity, ARCHETYPE_PLAYER)];
    HoldOffset *holdOffset = componentArrays[COMPONENT_INDEX(Holder, ARCHETYPE_PLAYER)];
    PlayerState *state = (PlayerState *)arg;
    *model = &character_model;

    // Set up position
    (*pos)[0] = 0.0f;
    (*pos)[1] = 500.0f;
    (*pos)[2] = 0.0f;

    // Set up position
    (*rot)[0] = 0x0000;
    (*rot)[1] = 0x0000;
    (*rot)[2] = 0x0000;

    // Set up gravity
    gravity->accel = -PLAYER_GRAVITY;
    gravity->terminalVelocity = -30.0f;

    // Set up behavior code
    bhvParams->callback = playerCallback;
    bhvParams->data = arg;
    state->playerEntity = findEntityFromComponent(ARCHETYPE_PLAYER, Component_Position, pos);
    state->state = PSTATE_AIR;
    state->subState = PASUBSTATE_FALLING;
    state->stateArg = 0;
    state->heldEntity = NULL;

    // Set up collider
    collider->radius = PLAYER_RADIUS;
    collider->numHeights = PLAYER_WALL_RAYCAST_HEIGHT_COUNT;
    collider->startOffset = PLAYER_HEIGHT / PLAYER_WALL_RAYCAST_HEIGHT_COUNT;
    collider->ySpacing = PLAYER_HEIGHT / PLAYER_WALL_RAYCAST_HEIGHT_COUNT;
    collider->floor = NULL;

    // Set up hold offset
    holdOffset->holdOffset[0] = 0.0f;
    holdOffset->holdOffset[1] = 90.0f;
    holdOffset->holdOffset[2] = 100.0f;
}

extern Model logo_model;

void playerCallback(UNUSED void **components, void *data)
{
    // Components: Position, Velocity, Rotation, BehaviorParams, Model, AnimState, Gravity
    Vec3 *pos = components[COMPONENT_INDEX(Position, ARCHETYPE_PLAYER)];
    Vec3 *vel = components[COMPONENT_INDEX(Velocity, ARCHETYPE_PLAYER)];
    Vec3s *rot = components[COMPONENT_INDEX(Rotation, ARCHETYPE_PLAYER)];
    AnimState *animState = components[COMPONENT_INDEX(AnimState, ARCHETYPE_PLAYER)];
    ColliderParams *collider = components[COMPONENT_INDEX(Collider, ARCHETYPE_PLAYER)];
    UNUSED GravityParams *gravity = components[COMPONENT_INDEX(Gravity, ARCHETYPE_PLAYER)];
    PlayerState *state = (PlayerState *)data;

    if (g_PlayerInput.buttonsHeld & R_CBUTTONS)
    {
        g_Camera.yaw += PLAYER_CAMERA_TURN_SPEED;
    }
    if (g_PlayerInput.buttonsHeld & L_CBUTTONS)
    {
        g_Camera.yaw -= PLAYER_CAMERA_TURN_SPEED;
    }
    
    if (g_PlayerInput.buttonsHeld & D_CBUTTONS)
    {
        g_Camera.pitch = MIN(g_Camera.pitch + PLAYER_CAMERA_TURN_SPEED, 0x3000);
    }
    if (g_PlayerInput.buttonsHeld & U_CBUTTONS)
    {
        g_Camera.pitch = MAX(g_Camera.pitch - PLAYER_CAMERA_TURN_SPEED, -0x1000);
    }

    if (g_PlayerInput.buttonsPressed & Z_TRIG)
    {
        (*pos)[0] = 0.0f;
        (*pos)[1] = 500.0f;
        (*pos)[2] = 0.0f;
    }

    VEC3_COPY(g_Camera.target, *pos);

    // if(0)
    
    // test held entity
    if (g_PlayerInput.buttonsPressed & B_BUTTON)
    {
        #define ARCHETYPE_HOLDABLE (Bit_Position | Bit_Velocity | Bit_Rotation | Bit_Model | Bit_Holdable | Bit_Gravity | Bit_Collider)
        if (state->heldEntity == NULL)
        {
            Entity *heldEntity = createEntity(ARCHETYPE_HOLDABLE);
            void *heldComponents[NUM_COMPONENTS(ARCHETYPE_HOLDABLE)];
            HoldState *heldState;
            Model **heldModel;
            GravityParams *heldGravity;
            ColliderParams *heldCollider;

            getEntityComponents(heldEntity, heldComponents);

            heldState = heldComponents[COMPONENT_INDEX(Holdable, ARCHETYPE_HOLDABLE)];
            heldState->holder = state->playerEntity;
            state->heldEntity = heldEntity;

            heldModel = heldComponents[COMPONENT_INDEX(Model, ARCHETYPE_HOLDABLE)];
            *heldModel = &logo_model;

            heldGravity = heldComponents[COMPONENT_INDEX(Gravity, ARCHETYPE_HOLDABLE)];
            heldGravity->accel = -1.0f;
            heldGravity->terminalVelocity = -30.0f;

            heldCollider = heldComponents[COMPONENT_INDEX(Collider, ARCHETYPE_HOLDABLE)];
            heldCollider->numHeights = 1;
            heldCollider->radius = 58.0f;
            heldCollider->startOffset = 29.0f;
            heldCollider->ySpacing = 0.0f;
        }
        else
        {
            void *heldComponents[NUM_COMPONENTS(state->heldEntity->archetype)];
            Vec3 *heldVel;
            HoldState *heldState;
            getEntityComponents(state->heldEntity, heldComponents);

            heldVel = heldComponents[COMPONENT_INDEX(Velocity, state->heldEntity->archetype)];
            heldState = heldComponents[COMPONENT_INDEX(Holdable, state->heldEntity->archetype)];

            (*heldVel)[0] = (*vel)[0] + 5.0f * sinsf((*rot)[1]);
            (*heldVel)[1] = (*vel)[1] + 15.0f;
            (*heldVel)[2] = (*vel)[2] + 5.0f * cossf((*rot)[1]);

            heldState->holder = NULL;
            state->heldEntity = NULL;
        }
    }
    
    // Transition between states if applicable
    stateUpdateCallbacks[state->state](state, &g_PlayerInput, *pos, *vel, collider, *rot, animState);
    // Process the current state
    stateProcessCallbacks[state->state](state, &g_PlayerInput, *pos, *vel, collider, *rot, animState);
}
