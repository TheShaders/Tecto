#include <ultra64.h>
#include <PR/sched.h>
#include <PR/gs2dex.h>
#include <stdint.h>

#include <gfx.h>
#include <mem.h>
#include <audio.h>
#include <task_sched.h>
#include <model.h>
#include <collision.h>
#include <camera.h>
#include <mathutils.h>

u16 g_frameBuffers[NUM_FRAME_BUFFERS][SCREEN_WIDTH * SCREEN_HEIGHT] __attribute__((aligned (64)));
u16 g_depthBuffer[SCREEN_WIDTH * SCREEN_HEIGHT] __attribute__((aligned (64)));

struct GfxContext g_gfxContexts[NUM_FRAME_BUFFERS];
OSScTask gfxTasks[NUM_FRAME_BUFFERS];

u64 taskStack[SP_DRAM_STACK_SIZE64];
u64 taskOutputBuffer[OUTPUT_BUFF_LEN];
u64 taskYieldBuffer[OS_YIELD_DATA_SIZE / sizeof(u64)];

u8* introSegAddr;
u8 *curGfxPoolPtr;
u8 *curGfxPoolEnd;

Gfx *g_dlistHead;

MtxF *g_curMatFPtr;
// The index of the context for the task being constructed
u32 g_curGfxContext;
// The index of the framebuffer being displayed next
u32 g_curFramebuffer;
u16 g_perspNorm;

static Gfx drawLayerRenderModes1Cycle[NUM_LAYERS][2] = {
    { gsDPSetRenderMode(G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2), gsSPEndDisplayList() },
    { gsDPSetRenderMode(G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2), gsSPEndDisplayList() },
    { gsDPSetRenderMode(G_RM_ZB_OPA_DECAL, G_RM_ZB_OPA_DECAL2), gsSPEndDisplayList() },
    { gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2), gsSPEndDisplayList() },
    { gsDPSetRenderMode(G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF), gsSPEndDisplayList() },
    { gsDPSetRenderMode(G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF), gsSPEndDisplayList() },
    { gsDPSetRenderMode(G_RM_AA_ZB_XLU_DECAL, G_RM_AA_ZB_XLU_DECAL2), gsSPEndDisplayList() },
    { gsDPSetRenderMode(G_RM_SPRITE, G_RM_SPRITE2), gsSPEndDisplayList() },
    { gsDPSetRenderMode(G_RM_XLU_SPRITE, G_RM_XLU_SPRITE2), gsSPEndDisplayList() },
};

static Gfx* drawLayerStarts[NUM_LAYERS];
static Gfx* drawLayerHeads[NUM_LAYERS];
static u32 drawLayerSlotsLeft[NUM_LAYERS];

void initGfx(void)
{
    int i;

    // Set up the graphics tasks
    for (i = 0; i < NUM_FRAME_BUFFERS; i++)
    {
        // Set up OSScTask fields

        // Set up fifo task, configure it to automatically swap buffers after completion
        gfxTasks[i].flags = OS_SC_NEEDS_RSP | OS_SC_NEEDS_RDP | OS_SC_SWAPBUFFER | OS_SC_LAST_TASK;

        gfxTasks[i].framebuffer = &g_frameBuffers[i];
        gfxTasks[i].msgQ = &g_gfxContexts[i].taskDoneQueue;
        osCreateMesgQueue(&g_gfxContexts[i].taskDoneQueue, &g_gfxContexts[i].taskDoneMesg, 1);

        // Set up OSTask fields

        // Make this a graphics task
        gfxTasks[i].list.t.type = M_GFXTASK;
        gfxTasks[i].list.t.flags = OS_TASK_DP_WAIT;

        // Set up the gfx task boot microcode pointer and size
        gfxTasks[i].list.t.ucode_boot = (u64*) rspbootTextStart;
        gfxTasks[i].list.t.ucode_boot_size = (u32)rspbootTextEnd - (u32)rspbootTextStart;

        // // Set up the gfx task gfx microcode text pointer and size
        gfxTasks[i].list.t.ucode = (u64*) gspF3DEX2_fifoTextStart;
        gfxTasks[i].list.t.ucode_size = (u32)gspF3DEX2_fifoTextEnd - (u32)gspF3DEX2_fifoTextStart;

        // // Set up the gfx task gfx microcode data pointer and size
        gfxTasks[i].list.t.ucode_data = (u64*) gspF3DEX2_fifoDataStart;
        gfxTasks[i].list.t.ucode_data_size = (u32)gspF3DEX2_fifoDataEnd - (u32)gspF3DEX2_fifoDataStart;

        gfxTasks[i].list.t.dram_stack = &taskStack[0];
        gfxTasks[i].list.t.dram_stack_size = SP_DRAM_STACK_SIZE8;

        gfxTasks[i].list.t.output_buff = &taskOutputBuffer[0];
        gfxTasks[i].list.t.output_buff_size = &taskOutputBuffer[OUTPUT_BUFF_LEN];

        gfxTasks[i].list.t.data_ptr = (u64*)&g_gfxContexts[i].dlistBuffer[0];

        gfxTasks[i].list.t.yield_data_ptr = &taskYieldBuffer[0];
        gfxTasks[i].list.t.yield_data_size = OS_YIELD_DATA_SIZE;
    }

    // Send a dummy complete message to the last task, so the first one can run
    osSendMesg(gfxTasks[NUM_FRAME_BUFFERS - 1].msgQ, gfxTasks[NUM_FRAME_BUFFERS - 1].msg, OS_MESG_BLOCK);

    // Set the gfx context index to 0
    g_curGfxContext = 0;
}

void loadIntroSegment(void)
{
    // Allocate RAM for the intro segment to be DMA'd to
    introSegAddr = allocRegion((u32)_introSegmentRomEnd - (u32)_introSegmentRomStart, ALLOC_GFX);
    
    // Update the segment table
    setSegment(0x04, introSegAddr);

    // DMA the intro segment and wait for the DMA to finish
    startDMA(introSegAddr, _introSegmentRomStart, (u32)_introSegmentRomEnd - (u32)_introSegmentRomStart);
    // waitForDMA();
}

void freeIntroSegment(void)
{
    setSegment(0x04, NULL);
    freeAlloc(introSegAddr);
}

void loadCreditsSegment(void)
{
    // Allocate RAM for the intro segment to be DMA'd to
    introSegAddr = allocRegion((u32)_creditsSegmentRomEnd - (u32)_creditsSegmentRomStart, ALLOC_GFX);
    
    // Update the segment table
    setSegment(0x04, introSegAddr);

    // DMA the intro segment and wait for the DMA to finish
    startDMA(introSegAddr, _creditsSegmentRomStart, (u32)_creditsSegmentRomEnd - (u32)_creditsSegmentRomStart);
    // waitForDMA();
}

static LookAt *lookAt;
static Lights1 *light;

void setupDrawLayers(void)
{
    int i;
    for (i = 0; i < NUM_LAYERS; i++)
    {
        // Allocate the room for the draw layer's slots plus a gSPBranchList to the next buffer
        drawLayerHeads[i] = drawLayerStarts[i] = (Gfx*)allocGfx((DRAW_LAYER_BUFFER_LEN + 1) * sizeof(Gfx));
        drawLayerSlotsLeft[i] = DRAW_LAYER_BUFFER_LEN;
    }
}

void removeDrawLayerSlot(u32 drawLayer)
{
    // Remove a slot from the draw layer's current buffer
    // If there are no slots left, allocate a new buffer for this layer
    if (--drawLayerSlotsLeft[drawLayer] == 0)
    {
        // Allocate the draw layer's new buffer
        Gfx* newBuffer = (Gfx*)allocGfx((DRAW_LAYER_BUFFER_LEN + 1) * sizeof(Gfx));
        // Branch to the new buffer from the old one
        gSPBranchList(drawLayerHeads[drawLayer]++, newBuffer);
        // Update the draw layer's buffer pointer and remaining slot count
        drawLayerHeads[drawLayer] = newBuffer;
        drawLayerSlotsLeft[drawLayer] = DRAW_LAYER_BUFFER_LEN;
    }
}

void addGfxToDrawLayer(u32 drawLayer, Gfx* toAdd)
{
    // Add the displaylist to the current draw layer's buffer
    gSPDisplayList(drawLayerHeads[drawLayer]++, toAdd);

    // Remove a slot from the current draw layer
    removeDrawLayerSlot(drawLayer);
}

void addMtxToDrawLayer(u32 drawLayer, Mtx* mtx)
{
    // Add the matrix to the current draw layer's buffer
    gSPMatrix(drawLayerHeads[drawLayer]++, mtx, 
	       G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    // Remove a slot from the current draw layer
    removeDrawLayerSlot(drawLayer);
}

void resetGfxFrame(void)
{
    // Set up the master displaylist head
    g_dlistHead = &g_gfxContexts[g_curGfxContext].dlistBuffer[0];
    curGfxPoolPtr = (u8*)&g_gfxContexts[g_curGfxContext].pool[0];
    curGfxPoolEnd = (u8*)&g_gfxContexts[g_curGfxContext].pool[GFX_POOL_SIZE64];

    // Reset the matrix stack index
    g_curMatFPtr = &g_gfxContexts[g_curGfxContext].mtxFStack[0];

    // Allocate the lookAt and light
    lookAt = (LookAt*) allocGfx(sizeof(LookAt));
    light = (Lights1*) allocGfx(sizeof(Lights1));

    // Clear the modelview matrix
    gfxIdentity();
}

void sendGfxTask(void)
{
    gfxTasks[g_curGfxContext].list.t.data_size = (u32)g_dlistHead - (u32)&g_gfxContexts[g_curGfxContext].dlistBuffer[0];

    // Writeback cache for graphics task data
    osWritebackDCacheAll();

    // Wait for the previous RSP task to complete
    osRecvMesg(gfxTasks[(g_curGfxContext + (NUM_FRAME_BUFFERS - 1)) % NUM_FRAME_BUFFERS].msgQ, NULL, OS_MESG_BLOCK);

    // This may be required, but isn't preset in the demo, so if problems arise later on this may solve them
    // if (gfxTasks[(g_curGfxContext + (NUM_FRAME_BUFFERS - 1)) % NUM_FRAME_BUFFERS].state & OS_SC_NEEDS_RDP)
    // {
    //     // Wait for the task's RDP portion to complete as well
    //     osRecvMesg(gfxTasks[(g_curGfxContext + (NUM_FRAME_BUFFERS - 1)) % NUM_FRAME_BUFFERS].msgQ, NULL, OS_MESG_BLOCK);
    // }
    
    // Start the RSP task
    scheduleGfxTask(&gfxTasks[g_curGfxContext]);

    // while (1);
    
    // Switch to the next context
    g_curGfxContext = (g_curGfxContext + 1) % NUM_FRAME_BUFFERS;
}

Vp viewport = {{											
    { SCREEN_WIDTH << 1, SCREEN_HEIGHT << 1, G_MAXZ / 2, 0},
    { SCREEN_WIDTH << 1, SCREEN_HEIGHT << 1, G_MAXZ / 2, 0},
}};

const Gfx rdpInitDL[] = {
    gsDPSetOtherMode(
        G_PM_NPRIMITIVE | G_CYC_1CYCLE | G_TP_PERSP | G_TD_CLAMP | G_TL_TILE | G_TF_BILERP |
            G_TC_FILT | G_CK_NONE | G_CD_DISABLE | G_AD_DISABLE,
        G_AC_NONE | G_ZS_PIXEL | G_RM_OPA_SURF | G_RM_OPA_SURF2),
#ifndef INTERLACED
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT),
#endif
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetPrimColor(0, 0, 0x00, 0xFF, 0x00, 0xFF),
    gsSPEndDisplayList(),
};

const Gfx clearScreenDL[] = {
    gsDPFillRectangle(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    gsDPPipeSync(),

    // gsDPSetFillColor(GPACK_RGBA5551(0x3F, 0x3F, 0x3F, 1) << 16 | GPACK_RGBA5551(0x3F, 0x3F, 0x3F, 1)),
    // gsDPFillRectangle(10, 10, SCREEN_WIDTH - 10 - 1, SCREEN_HEIGHT - 10 - 1),
    // gsDPPipeSync(),
    gsSPEndDisplayList(),
};

const Gfx clearDepthBuffer[] = {
	gsDPSetCycleType(G_CYC_FILL),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, g_depthBuffer),

    gsDPSetFillColor(GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0)),
    gsDPFillRectangle(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    gsDPPipeSync(),
    gsDPSetDepthImage(g_depthBuffer),
    gsSPEndDisplayList(),
};

void rspUcodeLoadInit(void)
{
    gSPLoadGeometryMode(g_dlistHead++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH | G_CULL_BACK | G_LIGHTING);
    gSPTexture(g_dlistHead++, 0, 0, 0, 0, G_OFF);
    
    gSPSetLights1(g_dlistHead++, (*light));
    gSPLookAt(g_dlistHead++, lookAt);
}

u32 fillColor = GPACK_RGBA5551(0, 61, 8, 1) << 16 | GPACK_RGBA5551(0, 61, 8, 1);

void startFrame(void)
{
    int segIndex;
    resetGfxFrame();

    gSPSegment(g_dlistHead++, 0x00, 0x00000000);
    gSPSegment(g_dlistHead++, BUFFER_SEGMENT, &g_frameBuffers[g_curGfxContext]);

    for (segIndex = 2; segIndex < NUM_SEGMENTS; segIndex++)
    {
        uintptr_t segOffset = (uintptr_t) getSegment(segIndex);
        if (segOffset != 0)
        {
            gSPSegment(g_dlistHead++, segIndex, segOffset);
        }
    }

#ifdef INTERLACED
    if (osViGetCurrentField())
    {
        gDPSetScissor(g_dlistHead++, G_SC_EVEN_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    else
    {
        gDPSetScissor(g_dlistHead++, G_SC_ODD_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
#endif
    gSPDisplayList(g_dlistHead++, rdpInitDL);
    gSPDisplayList(g_dlistHead++, clearDepthBuffer);
    
    gDPSetCycleType(g_dlistHead++, G_CYC_FILL);
    gDPSetColorImage(g_dlistHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, BUFFER_SEGMENT << 24);
    gDPSetFillColor(g_dlistHead++, fillColor);
    gSPDisplayList(g_dlistHead++, clearScreenDL);
    
    gDPSetCycleType(g_dlistHead++, G_CYC_1CYCLE);
    
    rspUcodeLoadInit();

    setupDrawLayers();
}

// Draws a model (TODO add posing)
void drawModel(Model *toDraw, Animation *anim, u32 frame)
{
    int boneIndex, layerIndex;
    Bone *bones, *curBone;
    BoneLayer *curBoneLayer;
    BoneTable *curBoneTable = NULL;
    Gfx *callbackReturn;
    MtxF *boneMatrices;
    u32 numFrames = 0;

    if (toDraw == NULL) return;

    // Get the virtual address of the model
    toDraw = segmentedToVirtual(toDraw);
    // Allocate space for this model's bone matrices
    boneMatrices = allocRegion(toDraw->numBones * sizeof(MtxF), ALLOC_GFX);

    // Draw the model's bones
    curBone = bones = segmentedToVirtual(&toDraw->bones[0]);
    if (anim != NULL)
    {
        anim = segmentedToVirtual(anim);
        numFrames = anim->frameCount;
        curBoneTable = segmentedToVirtual(anim->boneTables);
    }
    for (boneIndex = 0; boneIndex < toDraw->numBones; boneIndex++)
    {
        // If the bone has a parent, load the parent's matrix before transforming
        if (curBone->parent != 0xFF)
        {
            gfxPushLoadMat(bones[curBone->parent].matrix);
        }
        // Otherwise, use the current matrix on the stack
        else
        {
            gfxPushMat();
        }

        gfxTranslate(curBone->posX, curBone->posY, curBone->posZ);

        if (anim != NULL)
        {
            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;
            u32 hasCurrentTransformComponent = 0;
            s16 *curBoneChannel = segmentedToVirtual(curBoneTable->channels);
            s16 rx = 0; s16 ry = 0; s16 rz = 0;
            curBoneChannel += frame;

            if (curBoneTable->flags & CHANNEL_POS_X)
            {
                x = *curBoneChannel;
                curBoneChannel += numFrames;
                hasCurrentTransformComponent = 1;
            }
            if (curBoneTable->flags & CHANNEL_POS_Y)
            {
                y = *curBoneChannel;
                curBoneChannel += numFrames;
                hasCurrentTransformComponent = 1;
            }
            if (curBoneTable->flags & CHANNEL_POS_Z)
            {
                z = *curBoneChannel;
                curBoneChannel += numFrames;
                hasCurrentTransformComponent = 1;
            }
            if (hasCurrentTransformComponent)
            {
                gfxTranslate(x, y, z);
            }
            
            hasCurrentTransformComponent = 0;

            if (curBoneTable->flags & CHANNEL_ROT_X)
            {
                rx = *curBoneChannel;
                curBoneChannel += numFrames;
                hasCurrentTransformComponent = 1;
            }
            if (curBoneTable->flags & CHANNEL_ROT_Y)
            {
                ry = *curBoneChannel;
                curBoneChannel += numFrames;
                hasCurrentTransformComponent = 1;
            }
            if (curBoneTable->flags & CHANNEL_ROT_Z)
            {
                rz = *curBoneChannel;
                curBoneChannel += numFrames;
                hasCurrentTransformComponent = 1;
            }

            if (hasCurrentTransformComponent)
            {
                gfxRotateEulerXYZ(rx, ry, rz);
            }

            hasCurrentTransformComponent = 0;

            x = y = z = 1.0f;

            if (curBoneTable->flags & CHANNEL_SCALE_X)
            {
                x = *(u16*)curBoneChannel / 256.0f;
                curBoneChannel += numFrames;
                hasCurrentTransformComponent = 1;
            }
            if (curBoneTable->flags & CHANNEL_SCALE_Y)
            {
                y = *(u16*)curBoneChannel / 256.0f;
                curBoneChannel += numFrames;
                hasCurrentTransformComponent = 1;
            }
            if (curBoneTable->flags & CHANNEL_SCALE_Z)
            {
                z = *(u16*)curBoneChannel / 256.0f;
                curBoneChannel += numFrames;
                hasCurrentTransformComponent = 1;
            }
            if (hasCurrentTransformComponent)
            {
                gfxScale(x, y, z);
            }
            
        }

        // Draw the bone's layers
        curBoneLayer = segmentedToVirtual(&curBone->layers[0]);
        for (layerIndex = 0; layerIndex < curBone->numLayers; layerIndex++)
        {
            // Check if this bone has a before drawn callback, and if so call it
            if (curBone->beforeCb)
            {
                callbackReturn = curBone->beforeCb(curBone, curBoneLayer);
                // If the callback returned a displaylist, draw it
                if (callbackReturn)
                {
                    gSPDisplayList(g_dlistHead++, callbackReturn);
                }
            }
            
            // Draw the layer
            drawGfx(curBoneLayer->layer, curBoneLayer->displaylist);

            // Check if this bone has an after drawn callback, and if so call it
            if (curBone->afterCb)
            {
                callbackReturn = curBone->afterCb(curBone, curBoneLayer);
                // If the callback returned a displaylist, draw it
                if (callbackReturn)
                {
                    gSPDisplayList(g_dlistHead++, callbackReturn);
                }
            }
            curBoneLayer++;
        }

        curBone->matrix = &boneMatrices[boneIndex];
        // Save this bone's matrix in case other bones are children of this one
        gfxSaveMat(&boneMatrices[boneIndex]);

        // Pop this bone's matrix off the stack
        gfxPopMat();

        curBone++;
        if (anim)
            curBoneTable++;
    }

    // Free the memory used for the bone matrices
    freeAlloc(boneMatrices);
}

Gfx* gfxSetEnvColor(Bone* bone, UNUSED BoneLayer *layer)
{
    if (bone->index == 0)
    {
        gDPSetEnvColor(g_dlistHead++, 255, 0, 0, 0);
    }
    else if (bone->index == 1)
    {
        gDPSetEnvColor(g_dlistHead++, 0, 255, 0, 0);
    }
    return NULL;
}

void drawGfx(u32 layer, Gfx* toDraw)
{
    Mtx* curMtx = (Mtx*)allocGfx(sizeof(Mtx));
    guMtxF2L(*g_curMatFPtr, curMtx);

    addMtxToDrawLayer(layer, curMtx);
    addGfxToDrawLayer(layer, toDraw);
}

#define USE_TRIS_FOR_AABB

void drawAABB(u32 layer, AABB *toDraw, u32 color)
{
    int i;
    Vtx *verts = (Vtx*)allocGfx(sizeof(Vtx) * 8);
    Mtx *curMtx = (Mtx*)allocGfx(sizeof(Mtx));
    
#ifdef USE_TRIS_FOR_AABB
    Gfx *dlist = (Gfx*)allocGfx(sizeof(Gfx) * 11);
#else
    Gfx *dlist = (Gfx*)allocGfx(sizeof(Gfx) * 20);
#endif

    addGfxToDrawLayer(layer, dlist);

    for (i = 0; i < 8; i++)
    {
        *(u32*)(&verts[i].v.cn[0]) = color;
    }
    verts[0].v.ob[0] = toDraw->min[0];
    verts[0].v.ob[1] = toDraw->min[1];
    verts[0].v.ob[2] = toDraw->min[2];
    
    verts[1].v.ob[0] = toDraw->min[0];
    verts[1].v.ob[1] = toDraw->min[1];
    verts[1].v.ob[2] = toDraw->max[2];
    
    verts[2].v.ob[0] = toDraw->min[0];
    verts[2].v.ob[1] = toDraw->max[1];
    verts[2].v.ob[2] = toDraw->min[2];
    
    verts[3].v.ob[0] = toDraw->min[0];
    verts[3].v.ob[1] = toDraw->max[1];
    verts[3].v.ob[2] = toDraw->max[2];
    
    verts[4].v.ob[0] = toDraw->max[0];
    verts[4].v.ob[1] = toDraw->min[1];
    verts[4].v.ob[2] = toDraw->min[2];
    
    verts[5].v.ob[0] = toDraw->max[0];
    verts[5].v.ob[1] = toDraw->min[1];
    verts[5].v.ob[2] = toDraw->max[2];
    
    verts[6].v.ob[0] = toDraw->max[0];
    verts[6].v.ob[1] = toDraw->max[1];
    verts[6].v.ob[2] = toDraw->min[2];
    
    verts[7].v.ob[0] = toDraw->max[0];
    verts[7].v.ob[1] = toDraw->max[1];
    verts[7].v.ob[2] = toDraw->max[2];

    gDPPipeSync(dlist++);
    gDPSetCombineMode(dlist++, G_CC_SHADE, G_CC_SHADE);

    guMtxF2L(*g_curMatFPtr, curMtx);
    gSPMatrix(dlist++, curMtx,
	       G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPTexture(dlist++, 0xFFFF, 0xFFFF, 0, 0, G_OFF);
    gSPClearGeometryMode(dlist++, G_LIGHTING);
    gSPVertex(dlist++, verts, 8, 0);
#ifdef USE_TRIS_FOR_AABB
    // Top and left
    gSP2Triangles(dlist++, 2, 3, 6, 0x00, 0, 1, 2, 0x00);
    // Front and right
    gSP2Triangles(dlist++, 1, 7, 3, 0x00, 5, 6, 7, 0x00);
    // Back and bottom
    gSP2Triangles(dlist++, 0, 6, 4, 0x00, 1, 4, 5, 0x00);
#else
    // Top
    gSPLine3D(dlist++, 2, 3, 0x00);
    gSPLine3D(dlist++, 2, 6, 0x00);
    gSPLine3D(dlist++, 3, 7, 0x00);
    gSPLine3D(dlist++, 6, 7, 0x00);
    // Bottom
    gSPLine3D(dlist++, 0, 1, 0x00);
    gSPLine3D(dlist++, 0, 4, 0x00);
    gSPLine3D(dlist++, 1, 5, 0x00);
    gSPLine3D(dlist++, 4, 5, 0x00);
    // Edges
    gSPLine3D(dlist++, 0, 2, 0x00);
    gSPLine3D(dlist++, 1, 3, 0x00);
    gSPLine3D(dlist++, 4, 6, 0x00);
    gSPLine3D(dlist++, 5, 7, 0x00);
#endif
    gSPSetGeometryMode(dlist++, G_LIGHTING);
    gSPEndDisplayList(dlist++);
}

void drawLine(u32 layer, Vec3 start, Vec3 end, u32 color)
{
    Vtx *verts = (Vtx*)allocGfx(sizeof(Vtx) * 2);
    Mtx *curMtx = (Mtx*)allocGfx(sizeof(Mtx));
    Gfx *dlist = (Gfx*)allocGfx(sizeof(Gfx) * 9);

    addGfxToDrawLayer(layer, dlist);
    
    verts[0].v.ob[0] = start[0];
    verts[0].v.ob[1] = start[1];
    verts[0].v.ob[2] = start[2];
    *(u32*)(&verts[0].v.cn[0]) = color;
    
    verts[1].v.ob[0] = end[0];
    verts[1].v.ob[1] = end[1];
    verts[1].v.ob[2] = end[2];
    *(u32*)(&verts[1].v.cn[0]) = color;

    gDPPipeSync(dlist++);
    gDPSetCombineMode(dlist++, G_CC_SHADE, G_CC_SHADE);

    guMtxF2L(*g_curMatFPtr, curMtx);
    gSPMatrix(dlist++, curMtx,
	       G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPTexture(dlist++, 0xFFFF, 0xFFFF, 0, 0, G_OFF);
    gSPClearGeometryMode(dlist++, G_LIGHTING);

    gSPVertex(dlist++, verts, 2, 0);
    gSPLine3D(dlist++, 0, 1, 0x00);    
    
    gSPSetGeometryMode(dlist++, G_LIGHTING);
    gSPEndDisplayList(dlist++);
}

void drawColTris(u32 layer, ColTri *tris, u32 count, u32 color)
{
    Mtx *curMtx = (Mtx*)allocGfx(sizeof(Mtx));
    Gfx *dlist = (Gfx*)allocGfx(sizeof(Gfx) * (8 + count * 2));
    u32 i;
    
    addGfxToDrawLayer(layer, dlist);
    
    gDPPipeSync(dlist++);
    gDPSetColor(dlist++, G_SETENVCOLOR, color);
    gDPSetCombineLERP(dlist++, ENVIRONMENT, 0, SHADE, 0, 0, 0, 0, 1, ENVIRONMENT, 0, SHADE, 0, 0, 0, 0, 1);

    guMtxF2L(*g_curMatFPtr, curMtx);
    gSPMatrix(dlist++, curMtx,
	       G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPTexture(dlist++, 0xFFFF, 0xFFFF, 0, 0, G_OFF);
    gSPClearGeometryMode(dlist++, G_SHADING_SMOOTH);

    for (i = 0; i < count; i++)
    {
        Vtx *verts = (Vtx*)allocGfx(sizeof(Vtx) * 3);

        verts[0].v.ob[0] = tris[i].vertex[0];
        verts[0].v.ob[1] = tris[i].vertex[1];
        verts[0].v.ob[2] = tris[i].vertex[2];
        
        verts[1].v.ob[0] = tris[i].vertex[0] + tris[i].u[0];
        verts[1].v.ob[1] = tris[i].vertex[1] + tris[i].u[1];
        verts[1].v.ob[2] = tris[i].vertex[2] + tris[i].u[2];
        
        verts[2].v.ob[0] = tris[i].vertex[0] + tris[i].v[0];
        verts[2].v.ob[1] = tris[i].vertex[1] + tris[i].v[1];
        verts[2].v.ob[2] = tris[i].vertex[2] + tris[i].v[2];

        verts[0].n.n[0] = verts[1].n.n[0] = verts[2].n.n[0] = 120.0f * tris[i].normal[0];
        verts[0].n.n[1] = verts[1].n.n[1] = verts[2].n.n[1] = 120.0f * tris[i].normal[1];
        verts[0].n.n[2] = verts[1].n.n[2] = verts[2].n.n[2] = 120.0f * tris[i].normal[2];

        gSPVertex(dlist++, verts, 3, 0);
        gSP1Triangle(dlist++, 0, 1, 2, 0x00);
    }
    
    gSPSetGeometryMode(dlist++, G_SHADING_SMOOTH);
    gSPEndDisplayList(dlist++);
}

u8* allocGfx(s32 size)
{
    u8* retVal = curGfxPoolPtr;
    curGfxPoolPtr += ROUND_UP(size, 8);
    if (curGfxPoolPtr >= curGfxPoolEnd)
        return NULL;
    return retVal;
}

void setLightDirection(Vec3 lightDir)
{
    light->a.l.col[0] = light->a.l.colc[0] = 0x3F;
    light->a.l.col[1] = light->a.l.colc[1] = 0x3F;
    light->a.l.col[2] = light->a.l.colc[2] = 0x3F;

    light->l->l.col[0] = light->l->l.colc[0] = 0x7F;
    light->l->l.col[1] = light->l->l.colc[1] = 0x7F;
    light->l->l.col[2] = light->l->l.colc[2] = 0x7F;

    light->l->l.dir[0] = (s8)(lightDir[0] * (*g_curMatFPtr)[0][0] + lightDir[1] * (*g_curMatFPtr)[1][0] + lightDir[2] * (*g_curMatFPtr)[2][0]);
    light->l->l.dir[1] = (s8)(lightDir[0] * (*g_curMatFPtr)[0][1] + lightDir[1] * (*g_curMatFPtr)[1][1] + lightDir[2] * (*g_curMatFPtr)[2][1]);
    light->l->l.dir[2] = (s8)(lightDir[0] * (*g_curMatFPtr)[0][2] + lightDir[1] * (*g_curMatFPtr)[1][2] + lightDir[2] * (*g_curMatFPtr)[2][2]);

    lookAt->l[0].l.dir[0] = -light->l->l.dir[0];
    lookAt->l[0].l.dir[1] = -light->l->l.dir[1];
    lookAt->l[0].l.dir[2] = -light->l->l.dir[2];

    lookAt->l[1].l.dir[0] = 0;
    lookAt->l[1].l.dir[1] = 127;
    lookAt->l[1].l.dir[2] = 0;
}

void setupCameraMatrices(Camera *camera)
{
    Mtx* projMtx;
    Vec3 eyePos;
    Vec3 targetPos;
    Vec3 eyeOffset = {
        camera->distance * sinsf(camera->yaw) * cossf(camera->pitch),
        camera->distance * sinsf(camera->pitch) + camera->yOffset,
        camera->distance * cossf(camera->yaw) * cossf(camera->pitch)
    };
    float cameraHitDist;
    ColTri *cameraHitTri;
    SurfaceType cameraHitSurface;

    VEC3_COPY(targetPos, camera->target);
    targetPos[1] += camera->yOffset;

    cameraHitDist = raycast(targetPos, eyeOffset, 0.0f, 1.1f, &cameraHitTri, &cameraHitSurface);

    if (cameraHitTri != NULL)
    {
        VEC3_SCALE(eyeOffset, eyeOffset, MIN(MAX(cameraHitDist - 0.1f, 0.1f), 1.0f));
    }
    VEC3_ADD(eyePos, eyeOffset, targetPos);


    // Set up view matrix
    gfxLookat(
        eyePos[0], eyePos[1], eyePos[2], // Eye pos
        camera->target[0], camera->target[1] + camera->yOffset, camera->target[2], // Look pos
        0.0f, 1.0f, 0.0f); // Up vector

    // Set up projection matrix
    projMtx = (Mtx*)allocGfx(sizeof(Mtx));
    guMtxF2L(g_gfxContexts[g_curGfxContext].projMtxF, projMtx);

    // Perpsective
    gfxPerspective(camera->fov, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 20000.0f, 1.0f);

    // Ortho
    // guOrthoF(g_gfxContexts[g_curGfxContext].projMtxF, -SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, 100.0f, 20000.0f, 1.0f);
    // g_perspNorm = 0xFFFF;
    
    gSPViewport(g_dlistHead++, &viewport);
    gSPPerspNormalize(g_dlistHead++, g_perspNorm);
    
    gSPMatrix(g_dlistHead++, projMtx,
	       G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);
}

void endFrame()
{
    int i;

    // Finalize the draw layer displaylists and link them to the main one
    for (i = 0; i < NUM_LAYERS; i++)
    {
        // Pipe sync before switching draw layers
        gDPPipeSync(g_dlistHead++);

        switch (i)
        {
            // Switch to l3dex2 for line layers
            case LAYER_OPA_LINE:
            case LAYER_XLU_LINE:
                gSPLoadUcodeL(g_dlistHead++, gspL3DEX2_fifo);
                rspUcodeLoadInit();
                break;
            // Switch back to f3dex2 for sprite layers
            case (LAYER_OPA_LINE + 1):
            case (LAYER_XLU_LINE + 1):
                gSPLoadUcodeL(g_dlistHead++, gspF3DEX2_fifo);
                rspUcodeLoadInit();
                break;
            // Switch to s2dex2 for the two sprite layers (only one switch needed because they are the last two layers)
            case LAYER_OPA_SPRITE:
                gSPLoadUcodeL(g_dlistHead++, gspS2DEX2_fifo);
                break;
        }

        // Set up the render mode for this draw layer
        gSPDisplayList(g_dlistHead++, drawLayerRenderModes1Cycle[i]);

        // Link this layer's displaylist to the main displaylist
        gSPDisplayList(g_dlistHead++, drawLayerStarts[i]);

        // Terminate this draw layer's displaylist
        gSPEndDisplayList(drawLayerHeads[i]);
    }

    gDPFullSync(g_dlistHead++);
    gSPEndDisplayList(g_dlistHead++);

    sendGfxTask();
}
