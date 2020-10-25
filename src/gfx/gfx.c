#include <ultra64.h>
#include <gfx.h>
#include <mem.h>
#include <audio.h>

u16 g_frameBuffers[NUM_FRAME_BUFFERS][SCREEN_WIDTH * SCREEN_HEIGHT] __attribute__((aligned (64)));
u16 g_depthBuffer[SCREEN_WIDTH * SCREEN_HEIGHT] __attribute__((aligned (64)));

struct GfxContext g_gfxContexts[NUM_FRAME_BUFFERS];

u64 taskStack[SP_DRAM_STACK_SIZE64];
u64 taskOutputBuffer[OUTPUT_BUFF_LEN];

Gfx *g_dlistHead;

MtxF *g_curMatFPtr;
Mtx *g_curMatPtr;
// The index of the context for the task being constructed
u32 g_curGfxContext;
// The index of the framebuffer being displayed next
u32 g_curFramebuffer;
u16 g_perspNorm;

OSTask gfxtask = {{
    M_GFXTASK,            // Type
    OS_TASK_DP_WAIT,      // Flags

    NULL,                 // Boot ucode
    0,                    // Boot ucode size 

    NULL,                 // Task ucode
    SP_UCODE_SIZE,        // Task ucode size (4kB)

    NULL,                 // Task ucode data
    SP_UCODE_DATA_SIZE,   // Task ucode data size (2kB)

    &taskStack[0],        // Task ucode dmem stack
    SP_DRAM_STACK_SIZE8,  // Task ucode dmem stack size (1kB)

    &taskOutputBuffer[0],               // Task buffer
    &taskOutputBuffer[OUTPUT_BUFF_LEN], // Task buffer end

    NULL,                 // Task data pointer
    0,                    // Task data size

    NULL,                 // Task yield buffer pointer (not used)
    0                     // Task yield buffer size (not used)
}};

OSMesgQueue dmaMesgQueue;
OSMesgQueue rdpMesgQueue;
OSMesgQueue rspMesgQueue;
OSMesgQueue viMesgQueue;

OSMesg dmaMessage;
OSMesg rdpMessage;
OSMesg rspMessage;
OSMesg viMessage;

OSIoMesg dmaIoMessage;

void initGfx(void)
{
    // Set up the gfx task boot microcode pointer and size
    gfxtask.t.ucode_boot = (u64*) rspbootTextStart;
    gfxtask.t.ucode_boot_size = (u32)rspbootTextEnd - (u32)rspbootTextStart;

    // // Set up the gfx task gfx microcode text pointer and size
    gfxtask.t.ucode = (u64*) gspF3DEX2_fifoTextStart;
    gfxtask.t.ucode_size = (u32)gspF3DEX2_fifoTextEnd - (u32)gspF3DEX2_fifoTextStart;

    // // Set up the gfx task gfx microcode data pointer and size
    gfxtask.t.ucode_data = (u64*) gspF3DEX2_fifoDataStart;
    gfxtask.t.ucode_data_size = (u32)gspF3DEX2_fifoDataEnd - (u32)gspF3DEX2_fifoDataStart;

    // Set up the gfx task gfx microcode text pointer and size
    // gfxtask.t.ucode = (u64*) gspL3DEX2_fifoTextStart;
    // gfxtask.t.ucode_size = (u32)gspL3DEX2_fifoTextEnd - (u32)gspL3DEX2_fifoTextStart;

    // Set up the gfx task gfx microcode data pointer and size
    // gfxtask.t.ucode_data = (u64*) gspL3DEX2_fifoDataStart;
    // gfxtask.t.ucode_data_size = (u32)gspL3DEX2_fifoDataEnd - (u32)gspL3DEX2_fifoDataStart;

    // Set the gfx context index to 0
    g_curGfxContext = 0;

    // Set up the message queues

    // Create message queue for RDP completion
    osCreateMesgQueue(&rdpMesgQueue, &rdpMessage, 1);
    // Hook up the RDP completion message
    osSetEventMesg(OS_EVENT_DP, &rdpMesgQueue, NULL);
    
    // Create message queue for RSP completion
    osCreateMesgQueue(&rspMesgQueue, &rspMessage, 1);
    // Hook up the RSP completion message
    osSetEventMesg(OS_EVENT_SP, &rspMesgQueue, NULL);

    // Send dummy messages to the RSP and RDP queues to allow the first frame to be drawn
    osSendMesg(&rdpMesgQueue, NULL, OS_MESG_NOBLOCK);
    osSendMesg(&rspMesgQueue, NULL, OS_MESG_NOBLOCK);

    // Create message queue for DMA reads/writes
    osCreateMesgQueue(&dmaMesgQueue, &dmaMessage, 1);
    
    // Invalidate the data cache for the region being DMA'd to
    osInvalDCache(memPoolStart, (u32)_introSegmentRomEnd - (u32)_introSegmentRomStart); 

    // DMA the intro segment
    dmaIoMessage.hdr.pri = OS_MESG_PRI_NORMAL;
    dmaIoMessage.hdr.retQueue = &dmaMesgQueue;
    dmaIoMessage.dramAddr = memPoolStart;
    dmaIoMessage.devAddr = (u32)_introSegmentRomStart;
    dmaIoMessage.size = (u32)_introSegmentRomEnd - (u32)_introSegmentRomStart;

    // Start the DMA
    osEPiStartDma(g_romHandle, &dmaIoMessage, OS_READ);

    // Wait for the DMA to complete
    osRecvMesg(&dmaMesgQueue, NULL, OS_MESG_BLOCK);
}

void resetGfxFrame(void)
{
    // Set up the master displaylist head and gfx task data to point to the current context's displaylist
    g_dlistHead = &g_gfxContexts[g_curGfxContext].dlistBuffer[0];
    gfxtask.t.data_ptr = (u64*) g_dlistHead;

    // Reset the matrix stack index
    g_curMatFPtr = &g_gfxContexts[g_curGfxContext].mtxFStack[0];
    g_curMatPtr = &g_gfxContexts[g_curGfxContext].mtxStack[0];

    // Clear the modelview matrix
    gfxIdentity();

    // Set up projection matrix

    // Perpsective matrix
    gfxPerspective(60.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 1.0f, 1000.0f, 1.0f);

    // Ortho matrix
    // guOrthoF(g_projMtxF, -SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, -SCREEN_HEIGHT / 2, -10.0f, 10.0f, 1.0f);
    // g_perspNorm = 0xFFFF;
}

void sendGfxTask(void)
{
    gfxtask.t.data_size = (u32)g_dlistHead - (u32)&g_gfxContexts[g_curGfxContext].dlistBuffer[0];

    // Writeback cache for graphics task data
    // osWritebackDCache(&g_dlistBuffer[0], sizeof(g_dlistBuffer));
    osWritebackDCacheAll();

    // Wait for both RSP and RDP to finish
    // TODO this won't work if other RSP tasks are used
    osRecvMesg(&rdpMesgQueue, NULL, OS_MESG_BLOCK);
    osRecvMesg(&rspMesgQueue, NULL, OS_MESG_BLOCK);
    
    // Send the task complete message for the previous context
    osSendMesg(&g_gfxContexts[g_curGfxContext ^ 1].taskDoneQueue, NULL, OS_MESG_NOBLOCK);

    // Wait for the current graphics context's previous framebuffer to be displayed
    // This prevents the task from overwriting a framebuffer before/while it is being drawn
    osRecvMesg(&g_gfxContexts[g_curGfxContext].gfxQueue, NULL, OS_MESG_BLOCK);
    
    // Start the RSP task
    osSpTaskStart(&gfxtask);
    
    // Switch to the next context
    g_curGfxContext ^= 1;
}

Vp viewport = {{											
    { SCREEN_WIDTH << 1, SCREEN_HEIGHT << 1, G_MAXZ, 0},
    { SCREEN_WIDTH << 1, SCREEN_HEIGHT << 1, 0, 0},
}};

const Gfx rdpInitDL[] = {
    gsDPSetOtherMode(
        G_PM_1PRIMITIVE | G_CYC_1CYCLE | G_TP_PERSP | G_TD_CLAMP | G_TL_TILE | G_TF_BILERP |
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
    gsDPSetFillColor(GPACK_RGBA5551(0x7F, 0x7F, 0x7F, 1) << 16 | GPACK_RGBA5551(0x7F, 0x7F, 0x7F, 1)),
    gsDPFillRectangle(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    gsDPPipeSync(),

    // gsDPSetFillColor(GPACK_RGBA5551(0x3F, 0x3F, 0x3F, 1) << 16 | GPACK_RGBA5551(0x3F, 0x3F, 0x3F, 1)),
    // gsDPFillRectangle(10, 10, SCREEN_WIDTH - 10 - 1, SCREEN_HEIGHT - 10 - 1),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

const Gfx clearDepthBuffer[] = {
	gsDPSetCycleType(G_CYC_FILL),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetDepthImage(OS_K0_TO_PHYSICAL(g_depthBuffer)),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, OS_K0_TO_PHYSICAL(g_depthBuffer)),

    gsDPSetFillColor(GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0)),
    gsDPFillRectangle(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    gsDPPipeSync(),
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
    resetGfxFrame();

    gSPSegment(g_dlistHead++, 0x00, 0x00000000);
    gSPSegment(g_dlistHead++, 0x04, OS_K0_TO_PHYSICAL(memPoolStart));
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

    guMtxF2L(g_gfxContexts[g_curGfxContext].projMtxF, &g_gfxContexts[g_curGfxContext].projMtx);
    
    gSPMatrix(g_dlistHead++, OS_K0_TO_PHYSICAL(&g_gfxContexts[g_curGfxContext].projMtx),
	       G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPSetLights1(g_dlistHead++, whiteLight);
    gDPSetRenderMode(g_dlistHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    // gDPSetBlendColor(g_dlistHead++, 255, 0, 0, 255);
    // gDPSetRenderMode(g_dlistHead++, AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP |
        // ZMODE_OPA | ALPHA_CVG_SEL |
        // GBL_c1(G_BL_CLR_BL, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM), GBL_c1(G_BL_CLR_BL, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM));
}

void drawGfx(Gfx* toDraw)
{
    guMtxF2L(*g_curMatFPtr, g_curMatPtr);

    gSPMatrix(g_dlistHead++, OS_K0_TO_PHYSICAL(g_curMatPtr++),
	       G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);

    gSPDisplayList(g_dlistHead++, toDraw);
}

void endFrame()
{
    gDPFullSync(g_dlistHead++);
    gSPEndDisplayList(g_dlistHead++);

    sendGfxTask();
}

void viThreadFunc(__attribute__((unused)) void *arg)
{
    // Create message queue for VI retrace
    osCreateMesgQueue(&viMesgQueue, &viMessage, 1);

    // Hook up the VI retrace message
    osViSetEvent(&viMesgQueue, NULL, 1);

    // Send a dummy framebuffer
    osViSwapBuffer(&g_frameBuffers[1]);
    
    // Send dummy messages to the framebuffer swapped queue to allow the first gfx task for that buffer to run
    osSendMesg(&g_gfxContexts[0].gfxQueue, NULL, OS_MESG_NOBLOCK);

    // Turn off black screen
	osViBlack(FALSE);

    // Set the frame buffer index to 0
    g_curFramebuffer = 0;

    // Clear any VI messages
    while (!MQ_IS_EMPTY(&viMesgQueue))
    {
        osRecvMesg(&viMesgQueue, NULL, OS_MESG_BLOCK);
    }

    while (1)
    {
        // Wait until the graphics task for this frame is done
        osRecvMesg(&g_gfxContexts[g_curFramebuffer].taskDoneQueue, NULL, OS_MESG_BLOCK);

        // Clear any pending VI messages
        while (!MQ_IS_EMPTY(&viMesgQueue))
        {
            osRecvMesg(&viMesgQueue, NULL, OS_MESG_BLOCK);
        }

        // Wait for the next VI event before displaying the completed framebuffer
        osRecvMesg(&viMesgQueue, NULL, OS_MESG_BLOCK);

        // Send the current framebuffer
        osViSwapBuffer(&g_frameBuffers[g_curFramebuffer]);

        // Send the message to indicate the previous framebuffer was displayed
        osSendMesg(&g_gfxContexts[g_curFramebuffer].gfxQueue, NULL, OS_MESG_NOBLOCK);
        
        // Repeat for the next framebuffer
        g_curFramebuffer ^= 1;
    }
}
