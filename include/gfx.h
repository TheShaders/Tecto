#ifndef __GFX_H__
#define __GFX_H__

#include <config.h>
#include <types.h>
#include <mathutils.h>
#include <PR/gbi.h>
#include <PR/os_thread.h>
#include <PR/os_message.h>

// Draw layers
#define LAYER_OPA_SURF   0
#define LAYER_OPA_LINE   1
#define LAYER_OPA_DECAL  2
#define LAYER_TEX_EDGE   3
#define LAYER_XLU_SURF   4
#define LAYER_XLU_LINE   5
#define LAYER_XLU_DECAL  6
#define LAYER_OPA_SPRITE 7
#define LAYER_XLU_SPRITE 8

#define NUM_LAYERS       9

#define DRAW_LAYER_BUFFER_LEN 32

// Fix for gSPLoadUcodeL on gcc
#ifdef gSPLoadUcodeL
#undef gSPLoadUcodeL
#endif

#define	gSPLoadUcodeL(pkt, ucode)					\
        gSPLoadUcode((pkt), OS_K0_TO_PHYSICAL(&ucode##TextStart),	\
		            OS_K0_TO_PHYSICAL(&ucode##DataStart))

#ifdef HIGH_RES
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#else
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240
#endif

#define OUTPUT_BUFF_LEN 1024

#define DISPLAY_LIST_LEN 1024
#define GFX_POOL_SIZE 65536
#define GFX_POOL_SIZE64 (GFX_POOL_SIZE / 8)

#define MATF_STACK_LEN 16
#define MAT_BUFFER_LEN 128
#define NUM_FRAME_BUFFERS 2

#define BUFFER_SEGMENT 0x01

#ifdef OS_K0_TO_PHYSICAL
 #undef OS_K0_TO_PHYSICAL
#endif

// Gets rid of warnings with -Warray-bounds
#define OS_K0_TO_PHYSICAL(x) ((u32)(x)-0x80000000)

struct GfxContext {
    // Master displaylist
    Gfx dlistBuffer[DISPLAY_LIST_LEN];
    // Floating point modelview matrix stack
    MtxF mtxFStack[MATF_STACK_LEN];
    // Floating point projection matrix
    MtxF projMtxF;
    // Graphics tasks done message
    OSMesg taskDoneMesg;
    // Graphics tasks done message queue
    OSMesgQueue taskDoneQueue;
    // Graphics pool
    u64 pool[GFX_POOL_SIZE64];
};

extern struct GfxContext g_gfxContexts[NUM_FRAME_BUFFERS];

extern u16 g_frameBuffers[NUM_FRAME_BUFFERS][SCREEN_WIDTH * SCREEN_HEIGHT];
extern u16 g_depthBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

extern MtxF *g_curMatFPtr;
extern Mtx *g_curMatPtr;
extern u32 g_curGfxContext;
extern u16 g_perspNorm;
extern Gfx *g_dlistHead;

void initGfx(void);

void startFrame(void);
void setupCameraMatrices(Camera *camera);
void setLightDirection(Vec3 lightDir);
void endFrame(void);

u8* allocGfx(s32 size);
void addGfxToDrawLayer(u32 drawLayer, Gfx* toAdd);
void addMtxToDrawLayer(u32 drawLayer, Mtx* mtx);

void drawGfx(u32 layer, Gfx *toDraw);
void drawModel(Model *toDraw, Animation* anim, u32 frame);
void drawAABB(u32 layer, AABB *toDraw, u32 color);
void drawLine(u32 layer, Vec3 start, Vec3 end, u32 color);
void drawColTris(u32 layer, ColTri *tris, u32 count, u32 color);

#define copyMat(dst, src) \
{ \
    float* srcPtr = (float*)(&(*src)[0][0]); \
    float* dstPtr = (float*)(&(*dst)[0][0]); \
    \
    dstPtr[ 0] = srcPtr[ 0]; \
    dstPtr[ 1] = srcPtr[ 1]; \
    dstPtr[ 2] = srcPtr[ 2]; \
    dstPtr[ 3] = srcPtr[ 3]; \
    dstPtr[ 4] = srcPtr[ 4]; \
    dstPtr[ 5] = srcPtr[ 5]; \
    dstPtr[ 6] = srcPtr[ 6]; \
    dstPtr[ 7] = srcPtr[ 7]; \
    dstPtr[ 8] = srcPtr[ 8]; \
    dstPtr[ 9] = srcPtr[ 9]; \
    dstPtr[10] = srcPtr[10]; \
    dstPtr[11] = srcPtr[11]; \
    dstPtr[12] = srcPtr[12]; \
    dstPtr[13] = srcPtr[13]; \
    dstPtr[14] = srcPtr[14]; \
    dstPtr[15] = srcPtr[15]; \
}

#define gfxPushMat() \
{ \
    MtxF *nextMat = g_curMatFPtr + 1; \
    copyMat(nextMat, g_curMatFPtr); \
    g_curMatFPtr++; \
}

#define gfxPushLoadMat(src) \
{ \
    g_curMatFPtr++; \
    copyMat(g_curMatFPtr, src); \
}
    
#define gfxPopMat() \
    g_curMatFPtr--

#define gfxSaveMat(dst) \
    copyMat(dst, g_curMatFPtr);

#define gfxIdentity() \
    guMtxIdentF(*g_curMatFPtr)

#define gfxPerspective(fov, aspect, near, far, scale) \
    guPerspectiveF(g_gfxContexts[g_curGfxContext].projMtxF, &g_perspNorm, fov, aspect, near, far, scale)

#define gfxLookat(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ) \
{ \
    MtxF tmp; \
    guLookAtF(tmp, \
        eyeX, eyeY, eyeZ, \
        lookX, lookY, lookZ, \
        upX, upY, upZ); \
    mtxfMul(*g_curMatFPtr, *g_curMatFPtr, tmp); \
}

#define gfxRotateAxisAngle(angle, axisX, axisY, axisZ) \
{ \
    MtxF tmp; \
    guRotateF(tmp, angle, axisX, axisY, axisZ); \
    mtxfMul(*g_curMatFPtr, *g_curMatFPtr, tmp); \
}

#define gfxRotateEulerXYZ(rx, ry, rz) \
{ \
    MtxF tmp; \
    mtxfEulerXYZ(tmp, rx, ry, rz); \
    mtxfMul(*g_curMatFPtr, *g_curMatFPtr, tmp); \
}

#define gfxTranslate(x, y, z) \
{ \
    MtxF tmp; \
    guTranslateF(tmp, x, y, z); \
    mtxfMul(*g_curMatFPtr, *g_curMatFPtr, tmp); \
}

#define gfxScale(sx, sy, sz) \
{ \
    MtxF tmp; \
    guScaleF(tmp, sx, sy, sz); \
    mtxfMul(*g_curMatFPtr, *g_curMatFPtr, tmp); \
}

#define gfxPosition(pitch, rx, ry, rz, x, y, z) \
{ \
    MtxF tmp; \
    guPositionF(tmp, pitch, rx, ry, rz, x, y, z); \
    mtxfMul(*g_curMatFPtr, *g_curMatFPtr, tmp); \
}

#endif