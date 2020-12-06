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

static const Vec3 wallRayDirs[PLAYER_WALL_RAYCAST_RADIAL_COUNT] = {
    {  1.0000f * PLAYER_RADIUS, 0.0f,  0.0000f * PLAYER_RADIUS },
    {  0.9239f * PLAYER_RADIUS, 0.0f,  0.3827f * PLAYER_RADIUS },
    {  0.7071f * PLAYER_RADIUS, 0.0f,  0.7071f * PLAYER_RADIUS },
    {  0.3827f * PLAYER_RADIUS, 0.0f,  0.9239f * PLAYER_RADIUS },
    {  0.0000f * PLAYER_RADIUS, 0.0f,  1.0000f * PLAYER_RADIUS },
    { -0.3827f * PLAYER_RADIUS, 0.0f,  0.9239f * PLAYER_RADIUS },
    { -0.7071f * PLAYER_RADIUS, 0.0f,  0.7071f * PLAYER_RADIUS },
    { -0.9239f * PLAYER_RADIUS, 0.0f,  0.3827f * PLAYER_RADIUS },
    { -1.0000f * PLAYER_RADIUS, 0.0f,  0.0000f * PLAYER_RADIUS },
    { -0.9239f * PLAYER_RADIUS, 0.0f, -0.3827f * PLAYER_RADIUS },
    { -0.7071f * PLAYER_RADIUS, 0.0f, -0.7071f * PLAYER_RADIUS },
    { -0.3827f * PLAYER_RADIUS, 0.0f, -0.9239f * PLAYER_RADIUS },
    {  0.0000f * PLAYER_RADIUS, 0.0f, -1.0000f * PLAYER_RADIUS },
    {  0.3827f * PLAYER_RADIUS, 0.0f, -0.9239f * PLAYER_RADIUS },
    {  0.7071f * PLAYER_RADIUS, 0.0f, -0.7071f * PLAYER_RADIUS },
    {  0.9239f * PLAYER_RADIUS, 0.0f, -0.3827f * PLAYER_RADIUS },
};

void handleWalls(Vec3 pos, Vec3 vel);
ColTri *handleFloorOnGround(Vec3 pos, Vec3 vel);
ColTri *handleFloorInAir(Vec3 pos, Vec3 vel);

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


void updateGround(PlayerState *state, InputData *input, Vec3 pos, Vec3 vel, UNUSED Vec3s rot, UNUSED AnimState *animState)
{
    ColTri* floor = handleFloorOnGround(pos, vel);
    if (floor)
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

    state->floorTri = floor;
}

void processGround(PlayerState *state, InputData *input, UNUSED Vec3 pos, Vec3 vel, UNUSED Vec3s rot, AnimState *animState)
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

void updateAir(PlayerState *state, InputData *input, Vec3 pos, Vec3 vel, UNUSED Vec3s rot, UNUSED AnimState *animState)
{
    
    if (state->subState == PASUBSTATE_JUMPING)
    {
        vel[1] = 25.0f;
        state->subState = PASUBSTATE_FALLING;
    }
    else
    {
        ColTri *floor = handleFloorInAir(pos, vel);
        if (floor)
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
        state->floorTri = floor;
    }
}

void processAir(PlayerState *state, InputData *input, UNUSED Vec3 pos, Vec3 vel, UNUSED Vec3s rot, AnimState *animState)
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

void (*stateUpdateCallbacks[])(PlayerState *state, InputData *input, Vec3 pos, Vec3 vel, Vec3s rot, AnimState *anim) = {
    updateGround, // Ground
    updateAir, // Air
};

void (*stateProcessCallbacks[])(PlayerState *state, InputData *input, Vec3 pos, Vec3 vel, Vec3s rot, AnimState *anim) = {
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
    BehaviorParams *bhvParams = componentArrays[COMPONENT_INDEX(Behavior, ARCHETYPE_PLAYER)];
    Model **model = componentArrays[COMPONENT_INDEX(Model, ARCHETYPE_PLAYER)];
    GravityParams *gravity = componentArrays[COMPONENT_INDEX(Gravity, ARCHETYPE_PLAYER)];
    PlayerState *state = (PlayerState *)arg;
    *model = &character_model;
    bhvParams->callback = playerCallback;
    bhvParams->data = arg;
    (*pos)[0] = 0.0f;
    (*pos)[1] = 500.0f;
    (*pos)[2] = 0.0f;
    gravity->accel = -PLAYER_GRAVITY;
    gravity->terminalVelocity = -30.0f;
    state->state = PSTATE_AIR;
    state->subState = PASUBSTATE_FALLING;
    state->stateArg = 0;
    state->heldEntity = NULL;
}

ColTri *handleFloorOnGround(Vec3 pos, Vec3 vel)
{
    ColTri *floor;
    float downdist = raycastVertical(pos, -1.0f, -PLAYER_MAX_STEP_UP, PLAYER_MAX_STEP_DOWN, &floor);
    if (floor)
    {
        pos[1] -= downdist;
        vel[1] = 0.0f;
        return floor;
    }
    return NULL;
}

ColTri *handleFloorInAir(Vec3 pos, Vec3 vel)
{
    float groundRayLength = PLAYER_GROUND_RAYCAST_MIN_LENGTH - vel[1];
    ColTri *hitTri;
    float hitDist;
    hitDist = raycastVertical(pos, -groundRayLength, -1.0f, EPSILON, &hitTri);
    if (hitTri)
    {
        pos[1] -= hitDist * groundRayLength;
        vel[1] = 0.0f;

        return hitTri;
    }
    return NULL;
}

void handleWalls(Vec3 pos, Vec3 vel)
{
    int heightIndex, radialIndex;
    Vec3 rayStart = { pos[0], pos[1] + (PLAYER_HEIGHT - PLAYER_MAX_STEP_UP) / PLAYER_WALL_RAYCAST_HEIGHT_COUNT, pos[2] };
    VEC3_DIFF(rayStart, rayStart, vel);
    for (heightIndex = 0; heightIndex < PLAYER_WALL_RAYCAST_HEIGHT_COUNT; heightIndex++)
    {
        for (radialIndex = 0; radialIndex < PLAYER_WALL_RAYCAST_RADIAL_COUNT; radialIndex++)
        {
            ColTri *curWall;
            Vec3 rayDir;
            VEC3_ADD(rayDir, wallRayDirs[radialIndex], vel);
            float hitDist = raycast(rayStart, rayDir, 0.0f, 1.0f, &curWall);
            if (curWall)
            {
                float pushDist = hitDist - 1.0f;
                Vec3 pushVec;
                VEC3_SCALE(pushVec, wallRayDirs[radialIndex], pushDist);
                VEC3_ADD(pos, pos, pushVec);
                rayStart[0] = pos[0];
                rayStart[2] = pos[2];
            }
        }
        rayStart[1] += ((PLAYER_HEIGHT - PLAYER_MAX_STEP_UP) / PLAYER_WALL_RAYCAST_HEIGHT_COUNT);
    }
}

void playerCallback(UNUSED void **components, void *data)
{
    // Components: Position, Velocity, Rotation, BehaviorParams, Model, AnimState, Gravity
    Vec3 *pos = components[COMPONENT_INDEX(Position, ARCHETYPE_PLAYER)];
    Vec3 *vel = components[COMPONENT_INDEX(Velocity, ARCHETYPE_PLAYER)];
    Vec3s *rot = components[COMPONENT_INDEX(Rotation, ARCHETYPE_PLAYER)];
    AnimState *animState = components[COMPONENT_INDEX(AnimState, ARCHETYPE_PLAYER)];
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
    
    // Handle wall collision (since it's universal across states currently)
    handleWalls(*pos, *vel);
    // Transition between states if applicable
    stateUpdateCallbacks[state->state](state, &g_PlayerInput, *pos, *vel, *rot, animState);
    // Process the current state
    stateProcessCallbacks[state->state](state, &g_PlayerInput, *pos, *vel, *rot, animState);
}
