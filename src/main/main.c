#include <main.h>
#include <init.h>
#include <gfx.h>
#include <model.h>
#include <mem.h>

#include <segments/intro.h>

#define NUM_LOGOS 10

extern u8 *introSegAddr;

extern u8 _introSegmentStart[];

extern Model testmodel;
extern Model character_model;
extern Animation testmodelAnim;
extern Animation character_anim_Walking;


LookAt lookAt = gdSPDefLookAt(127, 0, 0, 0, 127, 0);
Vec3 g_lightDir = {127.0f, -32.0f, 0.0f};

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
            0.0f, 300.0f, -1000.0f, // Eye pos
            0.0f, 300.0f, 0.0f, // Look pos
            0.0f, 1.0f, 0.0f);

        g_lightDir[0] = -127.0f * cosf((M_PI / 180.0f) * angle);
        g_lightDir[2] = 127.0f * sinf((M_PI / 180.0f) * angle);

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
         gfxRotateAxisAngle(angle, 0.0f, 1.0f, 0.0f);
         drawModel(&character_model, &character_anim_Walking, frame);
        gfxPopMat();

        tmpAngle = -angle * (M_PI / 180) / 4.0f;

        // gSPLoadUcode(g_dlistHead++, gspL3DEX2_fifoTextStart, gspL3DEX2_fifoDataStart);
        // gDPSetRenderMode(g_dlistHead++, G_RM_AA_ZB_XLU_LINE, G_RM_AA_ZB_XLU_LINE2);

        // gDPSetCombineMode(g_dlistHead++, G_CC_SHADE, G_CC_SHADE);
        // gSPModifyVertex(g_dlistHead++, 0, G_MWO_POINT_RGBA, GPACK_RGBA5551(255, 255, 255, 1));
        // gSPModifyVertex(g_dlistHead++, 1, G_MWO_POINT_RGBA, GPACK_RGBA5551(255, 255, 255, 1));
        // gSPModifyVertex(g_dlistHead++, 0, G_MWO_POINT_ZSCREEN, 0);
        // gSPModifyVertex(g_dlistHead++, 1, G_MWO_POINT_ZSCREEN, 0);
        // gDPSetCombineLERP(g_dlistHead++, 0, 0, 0, ENVIRONMENT, 0, 0, 0, 1, 0, 0, 0, ENVIRONMENT, 0, 0, 0, 1);
        // gDPSetEnvColor(g_dlistHead++, 255, 255, 255, 255);

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
    
        endFrame();

        angle += 360.0f / (5 * 60.0f);
        frame++;
        if (frame >= ((Animation*)segmentedToVirtual(&character_anim_Walking))->frameCount)
            frame = 0;
    }
}