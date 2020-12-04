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

void createPlayer(void)
{
    debug_printf("Creating player entity\n");
    createEntitiesCallback(ARCHETYPE_PLAYER, NULL, 1, createPlayerCallback);
}

void createPlayerCallback(__attribute__((unused)) size_t count, __attribute__((unused)) void *arg, void **componentArrays)
{
    // Components: Position, Velocity, Rotation, BehaviorParams, Model, AnimState, Gravity
    Vec3 *pos = componentArrays[COMPONENT_INDEX(Position, ARCHETYPE_PLAYER)];
    BehaviorParams *bhvParams = componentArrays[COMPONENT_INDEX(Behavior, ARCHETYPE_PLAYER)];
    Model **model = componentArrays[COMPONENT_INDEX(Model, ARCHETYPE_PLAYER)];
    GravityParams *gravity = componentArrays[COMPONENT_INDEX(Gravity, ARCHETYPE_PLAYER)];
    *model = &character_model;
    bhvParams->callback = playerCallback;
    bhvParams->data = arg;
    (*pos)[0] = 0.0f;
    (*pos)[1] = 500.0f;
    (*pos)[2] = 0.0f;
    gravity->accel = -PLAYER_GRAVITY;
    gravity->terminalVelocity = -30.0f;
}

ColTri* resolvePlayerCollisions(Vec3 pos, Vec3 vel, Vec3s rot)
{
    // If the player has approximately 0 vertical velocity (accounting for 1 frame of gravity)
    if (vel[1] <= EPSILON && vel[1] >= -PLAYER_GRAVITY - EPSILON)
    {
        ColTri *floor;
        Vec3 downRay = {0.0f, -1.0f, 0.0f};
        float downdist = raycast(pos, downRay, -PLAYER_MAX_STEP_UP, PLAYER_MAX_STEP_DOWN, &floor);
        if (floor)
        {
            pos[1] -= downdist;
            vel[1] = 0.0f;
            return floor;
        }
    }
    // If the player is falling, check for ground below them
    if (vel[1] <= 0.0f)
    {
        float groundRayLength = PLAYER_GROUND_RAYCAST_MIN_LENGTH - vel[1];
        Vec3 groundRayDir = {0.0f, -groundRayLength, 0.0f};
        ColTri *hitTri;
        float hitDist = raycast(pos, groundRayDir, -1.0f, EPSILON, &hitTri);
        if (hitTri)
        {
            float velProjFloor;
            pos[1] -= hitDist * groundRayLength;
            vel[1] = 0.0f;

            return hitTri;
        }
    }
    return NULL;
}

void playerCallback(__attribute__((unused)) void **components, __attribute__((unused)) void *data)
{
    // Components: Position, Velocity, Rotation, BehaviorParams, Model, AnimState, Gravity
    Vec3 *pos = components[COMPONENT_INDEX(Position, ARCHETYPE_PLAYER)];
    Vec3 *vel = components[COMPONENT_INDEX(Velocity, ARCHETYPE_PLAYER)];
    Vec3s *rot = components[COMPONENT_INDEX(Rotation, ARCHETYPE_PLAYER)];
    AnimState *animState = components[COMPONENT_INDEX(AnimState, ARCHETYPE_PLAYER)];
    GravityParams *gravity = components[COMPONENT_INDEX(Gravity, ARCHETYPE_PLAYER)];
    ColTri *floor;
    float targetSpeed;
    float newSpeed;
    // Vec3 rayDir = {0.0f, -1000.0f, 0.0f};
    // ColTri *hitTri;
    // float hitDist;
    // Vec3 rayEnd;

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

    VEC3_COPY(g_Camera.target, *pos);

    targetSpeed = MAX_PLAYER_SPEED * 2 * g_PlayerInput.magnitude;

    floor = resolvePlayerCollisions(*pos, *vel, *rot);

    if (floor)
    {
        if (g_PlayerInput.buttonsPressed & A_BUTTON)
        {
            (*vel)[1] = 25.0f;
        }
        (*vel)[0] = (*vel)[0] * (1.0f - PLAYER_GROUND_ACCEL_TIME_CONST) + targetSpeed * (PLAYER_GROUND_ACCEL_TIME_CONST) * cossf(g_PlayerInput.angle + g_Camera.yaw);
        (*vel)[2] = (*vel)[2] * (1.0f - PLAYER_GROUND_ACCEL_TIME_CONST) - targetSpeed * (PLAYER_GROUND_ACCEL_TIME_CONST) * sinsf(g_PlayerInput.angle + g_Camera.yaw);

        newSpeed = POW2((*vel)[0]) + POW2((*vel)[2]);

        if (newSpeed >= POW2(0.1f))
        {
            (*rot)[1] = atan2s((*vel)[2], (*vel)[0]);
            if (animState->anim != (Animation*) segmentedToVirtual(&character_anim_Walk))
            {
                animState->anim = (Animation*) segmentedToVirtual(&character_anim_Walk);
                animState->counter = 0;
            }
            animState->speed = (s16)(sqrtf(newSpeed) * (ANIM_COUNTER_FACTOR / MAX_PLAYER_SPEED));
        }
        else
        {
            if (animState->anim != (Animation*) segmentedToVirtual(&character_anim_Idle_Long))
            {
                animState->anim = (Animation*) segmentedToVirtual(&character_anim_Idle_Long);
                animState->counter = 0;
            }
            animState->speed = (s16)(1.0f * ANIM_COUNTER_FACTOR);
        }
    }
    else
    {
        (*vel)[0] = (*vel)[0] * (1.0f - PLAYER_AIR_ACCEL_TIME_CONST) + targetSpeed * (PLAYER_AIR_ACCEL_TIME_CONST) * cossf(g_PlayerInput.angle + g_Camera.yaw);
        (*vel)[2] = (*vel)[2] * (1.0f - PLAYER_AIR_ACCEL_TIME_CONST) - targetSpeed * (PLAYER_AIR_ACCEL_TIME_CONST) * sinsf(g_PlayerInput.angle + g_Camera.yaw);

        if (animState->anim != (Animation*) segmentedToVirtual(&character_anim_Jump_Start))
        {
            animState->anim = (Animation*) segmentedToVirtual(&character_anim_Jump_Start);
            animState->counter = 0;
            animState->speed = (s16)(1.0f * ANIM_COUNTER_FACTOR);
        }
        // Prevent the jump start animation from looping
        else if ((animState->counter >> 4) >= animState->anim->frameCount - 2)
        {
            animState->counter -= 1 << 4;
        }
    }

    // hitDist = raycast(*pos, rayDir, 0.0f, 1.0f, &hitTri);
    // if (hitTri)
    // {
    //     drawColTris(LAYER_OPA_DECAL, hitTri, 1, 0x00FF00FF); //8000786c
    //     VEC3_SCALE(rayDir, rayDir, hitDist);
    // }
    // VEC3_ADD(rayEnd, *pos, rayDir);

    // drawLine(LAYER_OPA_LINE, *pos, rayEnd, 0x0000FF00);
}
