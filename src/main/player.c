#include <PR/gu.h>

#include <player.h>
#include <main.h>
#include <input.h>
#include <gfx.h>
#include <ecs.h>
#include <mathutils.h>
#include <collision.h>
#include <debug.h>

extern Model character_model;

void createPlayer(void)
{
    debug_printf("Creating player entity\n");
    createEntitiesCallback(ARCHETYPE_PLAYER, NULL, 1, createPlayerCallback);
}

void createPlayerCallback(__attribute__((unused)) size_t count, __attribute__((unused)) void *arg, void **componentArrays)
{
    // Components: Position, Velocity, Rotation, BehaviorParams, Model
    Vec3 *pos = componentArrays[0];
    BehaviorParams *bhvParams = componentArrays[3];
    Model **model = componentArrays[4];
    *model = &character_model;
    bhvParams->callback = playerCallback;
    bhvParams->data = arg;
    (*pos)[0] = 0.0f;
    (*pos)[1] = 100.0f;
    (*pos)[2] = 0.0f;
}

void playerCallback(__attribute__((unused)) void **components, __attribute__((unused)) void *data)
{
    // Components: Position, Velocity, Rotation, BehaviorParams
    Vec3 *pos = components[0];
    Vec3 *vel = components[1];
    Vec3 rayDir = {0.0f, -1000.0f, 0.0f};
    float targetSpeed;
    ColTri *hitTri;
    float hitDist;
    Vec3 rayEnd;

    targetSpeed = MAX_PLAYER_SPEED * g_PlayerInput.magnitude;

    (*vel)[0] = (*vel)[0] * (1.0f - PLAYER_ACCEL_TIME_CONST) + targetSpeed * (PLAYER_ACCEL_TIME_CONST / 65536.0f) * coss(g_PlayerInput.angle);
    (*vel)[2] = (*vel)[2] * (1.0f - PLAYER_ACCEL_TIME_CONST) - targetSpeed * (PLAYER_ACCEL_TIME_CONST / 65536.0f) * sins(g_PlayerInput.angle);

    (*pos)[0] += (*vel)[0];
    (*pos)[2] += (*vel)[2];

    hitDist = raycast(*pos, rayDir, 0.0f, 1.0f, &hitTri);
    if (hitTri)
    {
        drawColTris(LAYER_OPA_DECAL, hitTri, 1, 0x00FF00FF); //8000786c
        VEC3_SCALE(rayDir, rayDir, hitDist);
    }
    VEC3_ADD(rayEnd, *pos, rayDir);

    drawLine(LAYER_OPA_LINE, *pos, rayEnd, 0x0000FF00);
}
