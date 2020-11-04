#include <ultra64.h>
#include <main.h>
#include <init.h>
#include <mem.h>
#include <gfx.h>
#include <audio.h>
#include <malloc.h>

u8 idleThreadStack[IDLE_THREAD_STACKSIZE] __attribute__((aligned (16)));
static u8 mainThreadStack[MAIN_THREAD_STACKSIZE] __attribute__((aligned (16)));
static u8 audioThreadStack[AUDIO_THREAD_STACKSIZE] __attribute__((aligned (16)));
static u8 viThreadStack[VI_THREAD_STACKSIZE] __attribute__((aligned (16)));

static OSMesgQueue piMesgQueue;
static OSMesg piMessages[NUM_PI_MESSAGES];

OSThread g_threads[NUM_THREADS];
OSPiHandle *g_romHandle;

void init(void)
{
    osInitialize();
    // Are these needed?
    // bzero(_mainSegmentBssStart, (u32)_mainSegmentBssEnd - (u32)_mainSegmentBssStart);
    // bzero(_gfxSegmentBssStart, (u32)_gfxSegmentBssEnd - (u32)_gfxSegmentBssStart);
    // bzero(_libultraSegmentBssStart, (u32)_libultraSegmentBssEnd - (u32)_libultraSegmentBssStart);

    InitHeap(memPoolStart, 0x10000);//(u32) 0x80400000 - (u32) memPoolStart);
    g_romHandle = osCartRomInit();

    osCreateThread(&g_threads[IDLE_THREAD_INDEX], IDLE_THREAD, idle, NULL, idleThreadStack + IDLE_THREAD_STACKSIZE, 10);
    osStartThread(&g_threads[IDLE_THREAD_INDEX]);
}

void idle(__attribute__ ((unused)) void *arg)
{
    int i;

    // Set up VI
    osCreateViManager(OS_PRIORITY_VIMGR);
#ifdef HIGH_RES
  #ifdef INTERLACED
    osViSetMode(&osViModeNtscHan1);
  #else
    osViSetMode(&osViModeNtscHaf1);
  #endif
#else
  #ifdef INTERLACED
    osViSetMode(&osViModeNtscLaf1);
  #else
    osViSetMode(&osViModeNtscLan1);
  #endif
#endif

    // Make the screen black until content is ready
    osViBlack(TRUE);
    bzero(g_frameBuffers, NUM_FRAME_BUFFERS * SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(u16));
    
    // Initialize gfx context message queues
    for (i = 0; i < NUM_FRAME_BUFFERS; i++)
    {
        // Set up framebuffer swapped message queue
        osCreateMesgQueue(&g_gfxContexts[i].gfxQueue, &g_gfxContexts[i].gfxMesg, 1);
        // Set up task done message queue
        osCreateMesgQueue(&g_gfxContexts[i].taskDoneQueue, &g_gfxContexts[i].taskDoneMesg, 1);
    }
    
    // Set up PI
    osCreatePiManager(OS_PRIORITY_PIMGR, &piMesgQueue, &piMessages[0], NUM_PI_MESSAGES);

    // Create the audio thread
    osCreateThread(&g_threads[AUDIO_THREAD_INDEX], AUDIO_THREAD, audioThreadFunc, NULL, audioThreadStack + AUDIO_THREAD_STACKSIZE, AUDIO_THREAD_PRI);
    // Start the audio thread
    osStartThread(&g_threads[AUDIO_THREAD_INDEX]);

    // Create the VI buffer swap thread
    osCreateThread(&g_threads[VI_THREAD_INDEX], VI_THREAD, viThreadFunc, NULL, viThreadStack + VI_THREAD_STACKSIZE, VI_THREAD_PRI);
    // Start the VI thread
    osStartThread(&g_threads[VI_THREAD_INDEX]);

    // Create the main thread
    osCreateThread(&g_threads[MAIN_THREAD_INDEX], MAIN_THREAD, mainThreadFunc, NULL, mainThreadStack + MAIN_THREAD_STACKSIZE, MAIN_THREAD_PRI);
    // Start the main thread
    osStartThread(&g_threads[MAIN_THREAD_INDEX]);

    // Set this thread's priority to 0, making it the idle thread
    osSetThreadPri(NULL, 0);

    // idle
    while (1);
}
