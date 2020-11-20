#include <main.h>
#include <init.h>
#include <gfx.h>
#include <model.h>
#include <mem.h>
#include <collision.h>

#include <segments/intro.h>

#define NUM_LOGOS 10

extern u8 *introSegAddr;

extern u8 _introSegmentStart[];

extern Model testmodel;
extern Model character_model;
extern Animation testmodelAnim;
extern Animation character_anim_Walking;


LookAt lookAt = gdSPDefLookAt(127, 0, 0, 0, 127, 0);
Vec3 g_lightDir = {0.0f, -127.0f, -127.0f};

void mainThreadFunc(__attribute__ ((unused)) void *arg)
{
    u32 frame = 0;
    u32 i;
    float angle = 0.0f;
    float tmpAngle;
    initGfx();

    while (1)
    {
        startFrame();

        gSPSetGeometryMode(g_dlistHead++, G_LIGHTING | G_ZBUFFER);

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
            //  gSPModifyVertex(g_dlistHead++, 0, G_MWO_POINT_XYSCREEN, ((sins(i * 2048       ) + SCREEN_WIDTH / 2) << (16 + 2)) | ((coss(i * 2048       ) + SCREEN_HEIGHT / 2) << 2));
            //  gSPModifyVertex(g_dlistHead++, 1, G_MWO_POINT_XYSCREEN, ((sins(i * 2048 + 2048) + SCREEN_WIDTH / 2) << (16 + 2)) | ((coss(i * 2048 + 2048) + SCREEN_HEIGHT / 2) << 2));
            //  gSPLine3D(g_dlistHead++, 0, 1, 0x0);
            //  drawGfx(logo_logo_mesh);
                // drawModel(&testmodel, &testmodelAnim, 0);
            gfxPopMat();
            tmpAngle += (2 * M_PI) / NUM_LOGOS;
        }


        gfxPushMat();
         gfxTranslate(0.0f, 0.0f, 0.0f);
        {
            AABB aabb = {
                .min = {-100.0f, -100.0f, -100.0f},
                .max = { 100.0f,  100.0f,  100.0f},
            };
            ColTri tri = {
                .normal = {0.0f, 1.0f, 0.0f},
                .originDist = 100.0f,
                .vertex = {-100.0f, -100.0f, -100.0f},
                .u = {0.0f, 0.0f, 200.0f},
                .v = {200.0f, 0.0f, 0.0f},
                .uu = 40000.0f,
                .uv = 0.0f,
                .vv = 40000.0f,
            };
            Vec3 rayOrigin = { 200.0f * sinf((M_PI / 180.0f) * angle), 150.0f, 0.0f };
            Vec3 rayDir = { 0.0f, -1000.0f, 0.0f };
            Vec3 rayDirInv = { 1/rayDir[0], 1/rayDir[1], 1/rayDir[2] };
            Vec3 rayEnd;
            // f32 rayDist = rayVsAABB(rayOrigin, rayDirInv, &aabb, 0.0f, 1.0f);
            f32 rayDist = rayVsTri(rayOrigin, rayDir, &tri, 0.0f, 1.0f);
            gSPClearGeometryMode(g_dlistHead++, G_CULL_BACK);
            if (rayDist >= 0)
            {
                // drawAABB(&aabb, 0x00FF00FF);
                drawColTri(&tri, 0x00FF00FF);
                VEC3_SCALE(rayDir, rayDir, rayDist);
            }
            else
            {
                // drawAABB(&aabb, 0xFF0000FF);
                drawColTri(&tri, 0xFF0000FF);
            }
                
            gSPLoadUcodeL(g_dlistHead++, gspL3DEX2_fifo);
            gSPLoadGeometryMode(g_dlistHead++, G_ZBUFFER | G_SHADE | G_CULL_BACK);
            gDPPipeSync(g_dlistHead++);
            gDPSetRenderMode(g_dlistHead++, G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2);

            VEC3_ADD(rayEnd, rayOrigin, rayDir);
            drawLine(rayOrigin, rayEnd, 0x0000FFFF);
        }
        gfxPopMat();
    
        endFrame();

        angle += 360.0f / (5 * 60.0f);
        frame++;
        if (frame >= ((Animation*)segmentedToVirtual(&character_anim_Walking))->frameCount)
            frame = 0;
    }
}