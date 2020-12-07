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
                else if (input->magnitude > INPUT_DEADZONE)
                    state->subState = PGSUBSTATE_WALKING;
                break;
            case PGSUBSTATE_WALKING:
                if (input->buttonsPressed & A_BUTTON)
                    state->subState = PGSUBSTATE_JUMPING;
                else if (input->magnitude <= INPUT_DEADZONE)
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
            targetSpeed = MAX_PLAYER_SPEED * 2 * g_PlayerInput.magnitude;
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
            animState->speed = (s16)(sqrtf(newSpeed) * (ANIM_COUNTER_FACTOR / MAX_PLAYER_SPEED));
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
        state->subState = PASUBSTATE_FALLING;
    }
    else
    {
        if (collider->floor)
        {
            state->state = PSTATE_GROUND;
            if (input->magnitude > INPUT_DEADZONE)
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
            targetSpeed = MAX_PLAYER_SPEED * 2 * g_PlayerInput.magnitude;
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
    ColliderParams *collider = componentArrays[COMPONENT_INDEX(Collider, ARCHETYPE_PLAYER)];
    BehaviorParams *bhvParams = componentArrays[COMPONENT_INDEX(Behavior, ARCHETYPE_PLAYER)];
    Model **model = componentArrays[COMPONENT_INDEX(Model, ARCHETYPE_PLAYER)];
    GravityParams *gravity = componentArrays[COMPONENT_INDEX(Gravity, ARCHETYPE_PLAYER)];
    PlayerState *state = (PlayerState *)arg;
    *model = &character_model;

    // Set up position
    (*pos)[0] = 0.0f;
    (*pos)[1] = 500.0f;
    (*pos)[2] = 0.0f;

    // Set up gravity
    gravity->accel = -PLAYER_GRAVITY;
    gravity->terminalVelocity = -30.0f;

    // Set up behavior code
    bhvParams->callback = playerCallback;
    bhvParams->data = arg;
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
}

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
    
    // Transition between states if applicable
    stateUpdateCallbacks[state->state](state, &g_PlayerInput, *pos, *vel, collider, *rot, animState);
    // Process the current state
    stateProcessCallbacks[state->state](state, &g_PlayerInput, *pos, *vel, collider, *rot, animState);
}
