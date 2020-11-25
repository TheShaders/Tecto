#include <main.h>
#include <init.h>
#include <gfx.h>
#include <model.h>
#include <mem.h>
#include <collision.h>
#include <ecs.h>
#include <multiarraylist.h>

#include <segments/intro.h>

#define NUM_LOGOS 10

extern u8 *introSegAddr;

extern u8 _introSegmentStart[];

extern Model testmodel;
extern Model character_model;
extern Animation testmodelAnim;
extern Animation character_anim_Walking;
extern BVHTree test_collision_tree;

LookAt lookAt = gdSPDefLookAt(127, 0, 0, 0, 127, 0);
Vec3 g_lightDir = {127.0f, -127.0f, 0.0f};

MultiArrayList arr;
size_t posOffset;
size_t velOffset;


void mainThreadFunc(__attribute__ ((unused)) void *arg)
{
    u32 frame = 0;
    u32 i;
    float angle = 0.0f;
    float tmpAngle;
    initGfx();

    multiarraylist_init(&arr, Bit_Position | Bit_Velocity);
    multiarraylist_alloccount(&arr, 10000);

    posOffset = multiarraylist_get_component_offset(&arr, Component_Position);
    velOffset = multiarraylist_get_component_offset(&arr, Component_Velocity);

    while (1)
    {
        startFrame();

        gSPLookAt(g_dlistHead++, &lookAt);
        gfxLookat(
            1000.0f * sinf((M_PI / 180.0f) * angle * 0), 300.0f, 1000.0f * cosf((M_PI / 180.0f) * angle * 0), // Eye pos
            0.0f, 300.0f, 0.0f, // Look pos
            0.0f, 1.0f, 0.0f);

        // g_lightDir[0] = -127.0f * cosf((M_PI / 180.0f) * angle);
        // g_lightDir[2] = 127.0f * sinf((M_PI / 180.0f) * angle);

        lookAt.l[0].l.dir[0] = (s8)(g_lightDir[0] * (*g_curMatFPtr)[0][0] + g_lightDir[1] * (*g_curMatFPtr)[1][0] + g_lightDir[2] * (*g_curMatFPtr)[2][0]);
        lookAt.l[0].l.dir[1] = (s8)(g_lightDir[0] * (*g_curMatFPtr)[0][1] + g_lightDir[1] * (*g_curMatFPtr)[1][1] + g_lightDir[2] * (*g_curMatFPtr)[2][1]);
        lookAt.l[0].l.dir[2] = (s8)(g_lightDir[0] * (*g_curMatFPtr)[0][2] + g_lightDir[1] * (*g_curMatFPtr)[1][2] + g_lightDir[2] * (*g_curMatFPtr)[2][2]);

        lookAt.l[1].l.dir[0] = (s8)(*g_curMatFPtr)[1][0];
        lookAt.l[1].l.dir[1] = -(s8)(*g_curMatFPtr)[1][1];
        lookAt.l[1].l.dir[2] = (s8)(*g_curMatFPtr)[1][2];


        // gfxPushMat();
        //  gfxRotateAxisAngle(angle, 0.0f, 1.0f, 0.0f);
        //  drawGfx(logo_logo_mesh);
        // gfxPopMat();

        gfxPushMat();
         gfxScale(0.5f, 0.5f, 0.5f);
        //  gfxRotateAxisAngle(angle, 0.0f, 1.0f, 0.0f);
        //  drawModel(&character_model, &character_anim_Walking, frame);
        gfxPopMat();

        tmpAngle = -angle * (M_PI / 180) / 4.0f;

        for (i = 0; i < NUM_LOGOS; i++)
        {
            // f32 tmpAngle2 = angle - i * (360.0f / NUM_LOGOS);
            gfxPushMat();
             gfxPosition(0.0f, angle - i * (360.0f / NUM_LOGOS), 0.0f, 1.0f, sinf(tmpAngle) * 200.0f, cosf(tmpAngle) * 200.0f, 0.0f);
            //  drawGfx(LAYER_OPA_SURF, logo_logo_mesh);
                // drawModel(&testmodel, &testmodelAnim, 0);
            gfxPopMat();
            tmpAngle += (2 * M_PI) / NUM_LOGOS;
        }


        gfxPushMat();
         gfxTranslate(0.0f, 0.0f, 0.0f);
         gfxScale(10.0f, 10.0f, 10.0f);
        {
            int index;
            BVHTree *test_collision_virtual = (BVHTree*)segmentedToVirtual(&test_collision_tree);
            ColTri *tris = segmentedToVirtual(test_collision_virtual->tris);
            BVHNode *nodes = segmentedToVirtual(test_collision_virtual->nodes);
            drawColTris(LAYER_OPA_SURF, tris, test_collision_virtual->triCount, 0xFF0000FF);
            for (index = 0; index < test_collision_virtual->nodeCount; index++)
            {
                if (nodes[index].triCount == 0 && nodes[nodes[index].childIndex].triCount == 0 && nodes[nodes[nodes[index].childIndex].childIndex].triCount)
                {
                    drawAABB(LAYER_OPA_LINE, &nodes[index].aabb, 0x00FF00FF);
                }
            }
        }
        if (0) {
            AABB aabb = {
                .min = {-100.0f, -100.0f, -100.0f},
                .max = { 100.0f,  100.0f,  100.0f},
            };
            ColTri tri = {
                .normal = {-0.7071f, 0.7071f, 0.0f},
                .originDist = 0.0f,
                .vertex = {-100.0f, -100.0f, -100.0f},
                .u = {0.0f, 0.0f, 200.0f},
                .v = {200.0f, 200.0f, 0.0f},
                .uu = 40000.0f,
                .uv = 0.0f,
                .vv = 80000.0f,
            };
            Vec3 rayOrigin = { 200.0f * sinf((M_PI / 180.0f) * angle), 80.0f, 0.0f };
            Vec3 rayDir = { 0.0f, -1000.0f, 0.0f };
            Vec3 rayDirInv = { 1/rayDir[0], 1/rayDir[1], 1/rayDir[2] };
            Vec3 rayEnd;
            // s32 hitAABB = (rayVsAABB(rayOrigin, rayDirInv, &aabb, 0.0f, 1.0f) >= 0.0f);
            s32 hitAABB = (verticalRayVsAABB(rayOrigin, rayDirInv[1], &aabb, 0.0f, 1.0f) >= 0.0f);
            // f32 rayDist = rayVsTri(rayOrigin, rayDir, &tri, 0.0f, 1.0f);
            f32 rayDist = verticalRayVsTri(rayOrigin, rayDir[1], &tri, 0.0f, 1.0f);

            if (hitAABB)
            {
                drawAABB(LAYER_OPA_LINE, &aabb, 0x00FF00FF);
            }
            else
            {
                drawAABB(LAYER_OPA_LINE, &aabb, 0xFF0000FF);                
            }

            if (rayDist >= 0)
            {
                drawColTris(LAYER_OPA_SURF, &tri, 1, 0x00FF00FF);
                VEC3_SCALE(rayDir, rayDir, rayDist);
            }
            else
            {
                drawColTris(LAYER_OPA_SURF, &tri, 1, 0xFF0000FF);
            }

            VEC3_ADD(rayEnd, rayOrigin, rayDir);
            drawLine(LAYER_OPA_LINE, rayOrigin, rayEnd, 0x0000FFFF);
        }
        gfxPopMat();
    
        endFrame();

        angle += 360.0f / (5 * 60.0f);
        frame++;
        if (frame >= ((Animation*)segmentedToVirtual(&character_anim_Walking))->frameCount)
            frame = 0;
    }
}