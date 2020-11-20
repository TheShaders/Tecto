#include <ultra64.h>
#include <PR/sched.h>
#include <malloc.h>

#include <gfx.h>
#include <mem.h>
#include <audio.h>
#include <task_sched.h>
#include <model.h>
#include <collision.h>

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

OSMesgQueue dmaMesgQueue;

OSMesg dmaMessage;

OSIoMesg dmaIoMessage;

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

    // Create message queue for DMA reads/writes
    osCreateMesgQueue(&dmaMesgQueue, &dmaMessage, 1);

    // Allocate RAM for the intro segment to be DMA'd to
    introSegAddr = mt_malloc((u32)_introSegmentRomEnd - (u32)_introSegmentRomStart);
    
    // Invalidate the data cache for the region being DMA'd to
    osInvalDCache(introSegAddr, (u32)_introSegmentRomEnd - (u32)_introSegmentRomStart); 

    // Set up the intro segment DMA
    dmaIoMessage.hdr.pri = OS_MESG_PRI_NORMAL;
    dmaIoMessage.hdr.retQueue = &dmaMesgQueue;
    dmaIoMessage.dramAddr = introSegAddr;
    dmaIoMessage.devAddr = (u32)_introSegmentRomStart;
    dmaIoMessage.size = (u32)_introSegmentRomEnd - (u32)_introSegmentRomStart;

    // Start the DMA
    osEPiStartDma(g_romHandle, &dmaIoMessage, OS_READ);

    // Wait for the DMA to complete
    osRecvMesg(&dmaMesgQueue, NULL, OS_MESG_BLOCK);
}

void resetGfxFrame(void)
{
    // Set up the master displaylist head
    g_dlistHead = &g_gfxContexts[g_curGfxContext].dlistBuffer[0];
    curGfxPoolPtr = (u8*)&g_gfxContexts[g_curGfxContext].pool[0];
    curGfxPoolEnd = (u8*)&g_gfxContexts[g_curGfxContext].pool[GFX_POOL_SIZE64];

    // Reset the matrix stack index
    g_curMatFPtr = &g_gfxContexts[g_curGfxContext].mtxFStack[0];

    // Clear the modelview matrix
    gfxIdentity();

    // Set up projection matrix

    // Perpsective matrix
    gfxPerspective(60.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 100.0f, 20000.0f, 1.0f);

    // Ortho matrix
    // guOrthoF(g_gfxContexts[g_curGfxContext].projMtxF, -SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, 100.0f, 20000.0f, 1.0f);
    // g_perspNorm = 0xFFFF;
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
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, BUFFER_SEGMENT << 24),
    gsDPSetFillColor(GPACK_RGBA5551(0, 61, 8, 1) << 16 | GPACK_RGBA5551(0, 61, 8, 1)),
    gsDPFillRectangle(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    gsDPPipeSync(),

    // gsDPSetFillColor(GPACK_RGBA5551(0x3F, 0x3F, 0x3F, 1) << 16 | GPACK_RGBA5551(0x3F, 0x3F, 0x3F, 1)),
    // gsDPFillRectangle(10, 10, SCREEN_WIDTH - 10 - 1, SCREEN_HEIGHT - 10 - 1),
    // gsDPPipeSync(),
    gsSPEndDisplayList(),
};

const Gfx clearDepthBuffer[] = {
	gsDPSetCycleType(G_CYC_FILL),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, OS_K0_TO_PHYSICAL(g_depthBuffer)),

    gsDPSetFillColor(GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0)),
    gsDPFillRectangle(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    gsDPPipeSync(),
    gsDPSetDepthImage(OS_K0_TO_PHYSICAL(g_depthBuffer)),
    gsSPEndDisplayList(),
};

const Lights1 whiteLight = gdSPDefLights1(
    0x7F, 0x7F, 0x7F, // Ambient
    0x7F, 0x7F, 0x7F, // diffuse
    50, 0, 50 // Light direction forward from camera
);

void mtxfMul(MtxF out, MtxF a, MtxF b)
{
    float a00=a[0][0];
    float a01=a[0][1];
    float a02=a[0][2];
    float a03=a[0][3];

    float a10=a[1][0];
    float a11=a[1][1];
    float a12=a[1][2];
    float a13=a[1][3];

    float a20=a[2][0];
    float a21=a[2][1];
    float a22=a[2][2];
    float a23=a[2][3];

    float a30=a[3][0];
    float a31=a[3][1];
    float a32=a[3][2];
    float a33=a[3][3];

    float b00=b[0][0];
    float b01=b[0][1];
    float b02=b[0][2];
    float b03=b[0][3];

    float b10=b[1][0];
    float b11=b[1][1];
    float b12=b[1][2];
    float b13=b[1][3];

    float b20=b[2][0];
    float b21=b[2][1];
    float b22=b[2][2];
    float b23=b[2][3];

    float b30=b[3][0];
    float b31=b[3][1];
    float b32=b[3][2];
    float b33=b[3][3];

    out[0][0] = a00*b00+a10*b01+a20*b02+a30*b03;
    out[0][1] = a01*b00+a11*b01+a21*b02+a31*b03;
    out[0][2] = a02*b00+a12*b01+a22*b02+a32*b03;
    out[0][3] = a03*b00+a13*b01+a23*b02+a33*b03;

    out[1][0] = a00*b10+a10*b11+a20*b12+a30*b13;
    out[1][1] = a01*b10+a11*b11+a21*b12+a31*b13;
    out[1][2] = a02*b10+a12*b11+a22*b12+a32*b13;
    out[1][3] = a03*b10+a13*b11+a23*b12+a33*b13;

    out[2][0] = a00*b20+a10*b21+a20*b22+a30*b23;
    out[2][1] = a01*b20+a11*b21+a21*b22+a31*b23;
    out[2][2] = a02*b20+a12*b21+a22*b22+a32*b23;
    out[2][3] = a03*b20+a13*b21+a23*b22+a33*b23;

    out[3][0] = a00*b30+a10*b31+a20*b32+a30*b33;
    out[3][1] = a01*b30+a11*b31+a21*b32+a31*b33;
    out[3][2] = a02*b30+a12*b31+a22*b32+a32*b33;
    out[3][3] = a03*b30+a13*b31+a23*b32+a33*b33;
}

void startFrame(void)
{
    Mtx* projMtx;
    resetGfxFrame();

    gSPSegment(g_dlistHead++, 0x00, 0x00000000);
    setSegment(0x04, introSegAddr);
    gSPSegment(g_dlistHead++, 0x04, OS_K0_TO_PHYSICAL(introSegAddr));
    gSPSegment(g_dlistHead++, BUFFER_SEGMENT, OS_K0_TO_PHYSICAL(&g_frameBuffers[g_curGfxContext]));

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
    gSPDisplayList(g_dlistHead++, OS_K0_TO_PHYSICAL(rdpInitDL));
    gSPDisplayList(g_dlistHead++, OS_K0_TO_PHYSICAL(clearDepthBuffer));
    gSPDisplayList(g_dlistHead++, OS_K0_TO_PHYSICAL(clearScreenDL));
    
    gDPSetCycleType(g_dlistHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(g_dlistHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    
    gSPLoadGeometryMode(g_dlistHead++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH | G_CULL_BACK);
    gSPTexture(g_dlistHead++, 0, 0, 0, 0, G_OFF);
    gSPViewport(g_dlistHead++, OS_K0_TO_PHYSICAL(&viewport));
    gSPPerspNormalize(g_dlistHead++, g_perspNorm);

    projMtx = (Mtx*)allocGfx(sizeof(Mtx));
    guMtxF2L(g_gfxContexts[g_curGfxContext].projMtxF, projMtx);
    
    gSPMatrix(g_dlistHead++, OS_K0_TO_PHYSICAL(projMtx),
	       G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPSetLights1(g_dlistHead++, whiteLight);
    gDPSetRenderMode(g_dlistHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    // gDPSetBlendColor(g_dlistHead++, 255, 0, 0, 255);
    // gDPSetRenderMode(g_dlistHead++, AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |
        // ZMODE_OPA | ALPHA_CVG_SEL |
        // GBL_c1(G_BL_CLR_BL, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM), GBL_c1(G_BL_CLR_BL, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM));
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

    // Get the virtual address of the model
    toDraw = segmentedToVirtual(toDraw);
    // Allocate space for this model's bone matrices
    boneMatrices = calloc(toDraw->numBones, sizeof(MtxF));

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

            if (curBoneTable->flags & CHANNEL_ROT_X)
            {
                gfxRotateAxisAngle(*curBoneChannel * (180.0f / 32768.0f), 1.0f, 0.0f, 0.0f);
                curBoneChannel += numFrames;
            }
            if (curBoneTable->flags & CHANNEL_ROT_Y)
            {
                gfxRotateAxisAngle(*curBoneChannel * (180.0f / 32768.0f), 0.0f, 1.0f, 0.0f);
                curBoneChannel += numFrames;
            }
            if (curBoneTable->flags & CHANNEL_ROT_Z)
            {
                gfxRotateAxisAngle(*curBoneChannel * (180.0f / 32768.0f), 0.0f, 0.0f, 1.0f);
                curBoneChannel += numFrames;
            }

            hasCurrentTransformComponent = 0;

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
            drawGfx(curBoneLayer->displaylist);

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
    free(boneMatrices);
}

Gfx* gfxSetEnvColor(Bone* bone, __attribute__((unused)) BoneLayer *layer)
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

void drawGfx(Gfx* toDraw)
{
    Mtx* curMtx = (Mtx*)allocGfx(sizeof(Mtx));
    guMtxF2L(*g_curMatFPtr, curMtx);

    gSPMatrix(g_dlistHead++, OS_K0_TO_PHYSICAL(curMtx),
	       G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPDisplayList(g_dlistHead++, toDraw);
}

void drawAABB(AABB *toDraw, u32 color)
{
    int i;
    Vtx *verts = (Vtx*)allocGfx(sizeof(Vtx) * 8);
    Mtx *curMtx = (Mtx*)allocGfx(sizeof(Mtx));

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

    gDPPipeSync(g_dlistHead++);
    gDPSetCombineMode(g_dlistHead++, G_CC_SHADE, G_CC_SHADE);

    guMtxF2L(*g_curMatFPtr, curMtx);
    gSPMatrix(g_dlistHead++, OS_K0_TO_PHYSICAL(curMtx),
	       G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPTexture(g_dlistHead++, 0xFFFF, 0xFFFF, 0, 0, G_OFF);
    gSPClearGeometryMode(g_dlistHead++, G_LIGHTING);
    gSPVertex(g_dlistHead++, OS_K0_TO_PHYSICAL(verts), 8, 0);
    // Top
    gSPLine3D(g_dlistHead++, 2, 3, 0x00);
    gSPLine3D(g_dlistHead++, 2, 6, 0x00);
    gSPLine3D(g_dlistHead++, 3, 7, 0x00);
    gSPLine3D(g_dlistHead++, 6, 7, 0x00);
    // Bottom
    gSPLine3D(g_dlistHead++, 0, 1, 0x00);
    gSPLine3D(g_dlistHead++, 0, 4, 0x00);
    gSPLine3D(g_dlistHead++, 1, 5, 0x00);
    gSPLine3D(g_dlistHead++, 4, 5, 0x00);
    // Edges
    gSPLine3D(g_dlistHead++, 0, 2, 0x00);
    gSPLine3D(g_dlistHead++, 1, 3, 0x00);
    gSPLine3D(g_dlistHead++, 4, 6, 0x00);
    gSPLine3D(g_dlistHead++, 5, 7, 0x00);
    gSPSetGeometryMode(g_dlistHead++, G_LIGHTING);
}

void drawLine(Vec3 start, Vec3 end, u32 color)
{
    Vtx *verts = (Vtx*)allocGfx(sizeof(Vtx) * 2);
    Mtx *curMtx = (Mtx*)allocGfx(sizeof(Mtx));
    
    verts[0].v.ob[0] = start[0];
    verts[0].v.ob[1] = start[1];
    verts[0].v.ob[2] = start[2];
    *(u32*)(&verts[0].v.cn[0]) = color;
    
    verts[1].v.ob[0] = end[0];
    verts[1].v.ob[1] = end[1];
    verts[1].v.ob[2] = end[2];
    *(u32*)(&verts[1].v.cn[0]) = color;

    gDPPipeSync(g_dlistHead++);
    gDPSetCombineMode(g_dlistHead++, G_CC_SHADE, G_CC_SHADE);

    guMtxF2L(*g_curMatFPtr, curMtx);
    gSPMatrix(g_dlistHead++, OS_K0_TO_PHYSICAL(curMtx),
	       G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPTexture(g_dlistHead++, 0xFFFF, 0xFFFF, 0, 0, G_OFF);
    gSPClearGeometryMode(g_dlistHead++, G_LIGHTING);

    gSPVertex(g_dlistHead++, OS_K0_TO_PHYSICAL(verts), 2, 0);
    gSPLine3D(g_dlistHead++, 0, 1, 0x00);    
    
    gSPSetGeometryMode(g_dlistHead++, G_LIGHTING);
}

void drawColTri(ColTri *tri, u32 color)
{
    Vtx *verts = (Vtx*)allocGfx(sizeof(Vtx) * 3);
    Mtx *curMtx = (Mtx*)allocGfx(sizeof(Mtx));

    verts[0].v.ob[0] = tri->vertex[0];
    verts[0].v.ob[1] = tri->vertex[1];
    verts[0].v.ob[2] = tri->vertex[2];
    *(u32*)(&verts[0].v.cn[0]) = color;
    
    verts[1].v.ob[0] = tri->vertex[0] + tri->u[0];
    verts[1].v.ob[1] = tri->vertex[1] + tri->u[1];
    verts[1].v.ob[2] = tri->vertex[2] + tri->u[2];
    *(u32*)(&verts[1].v.cn[0]) = color;
    
    verts[2].v.ob[0] = tri->vertex[0] + tri->v[0];
    verts[2].v.ob[1] = tri->vertex[1] + tri->v[1];
    verts[2].v.ob[2] = tri->vertex[2] + tri->v[2];
    *(u32*)(&verts[2].v.cn[0]) = color;

    gDPPipeSync(g_dlistHead++);
    gDPSetCombineMode(g_dlistHead++, G_CC_SHADE, G_CC_SHADE);

    guMtxF2L(*g_curMatFPtr, curMtx);
    gSPMatrix(g_dlistHead++, OS_K0_TO_PHYSICAL(curMtx),
	       G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPTexture(g_dlistHead++, 0xFFFF, 0xFFFF, 0, 0, G_OFF);
    gSPClearGeometryMode(g_dlistHead++, G_LIGHTING);

    gSPVertex(g_dlistHead++, OS_K0_TO_PHYSICAL(verts), 3, 0);
    gSP1Triangle(g_dlistHead++, 0, 1, 2, 0x00);
    
    gSPSetGeometryMode(g_dlistHead++, G_LIGHTING);
}

u8* allocGfx(s32 size)
{
    u8* retVal = curGfxPoolPtr;
    curGfxPoolPtr += ROUND_UP(size, 8);
    if (curGfxPoolPtr >= curGfxPoolEnd)
        return NULL;
    return retVal;
}

void endFrame()
{
    gDPFullSync(g_dlistHead++);
    gSPEndDisplayList(g_dlistHead++);

    sendGfxTask();
}
