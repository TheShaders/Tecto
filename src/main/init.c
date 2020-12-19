// libultra
#include <ultra64.h>

// game code
#include <main.h>
#include <init.h>
#include <mem.h>
#include <gfx.h>
#include <audio.h>
#include <task_sched.h>
#include <debug.h>

u8 idleThreadStack[IDLE_THREAD_STACKSIZE] __attribute__((aligned (16)));
u8 mainThreadStack[MAIN_THREAD_STACKSIZE] __attribute__((aligned (16)));
u8 audioThreadStack[AUDIO_THREAD_STACKSIZE] __attribute__((aligned (16)));

static OSMesgQueue piMesgQueue;
static OSMesg piMessages[NUM_PI_MESSAGES];

OSMesgQueue siMesgQueue;
static OSMesg siMessages[NUM_SI_MESSAGES];

OSThread g_threads[NUM_THREADS];
OSPiHandle *g_romHandle;

void init(void)
{
    osInitialize();
    
    bzero(_mainSegmentBssStart, (u32)_mainSegmentBssEnd - (u32)_mainSegmentBssStart);

    initMemAllocator(memPoolStart, (void*) MEM_END);
    g_romHandle = osCartRomInit();

    osCreateThread(&g_threads[IDLE_THREAD_INDEX], IDLE_THREAD, idle, NULL, idleThreadStack + IDLE_THREAD_STACKSIZE, 10);
    osStartThread(&g_threads[IDLE_THREAD_INDEX]);
}

void idle(__attribute__ ((unused)) void *arg)
{
    bzero(g_frameBuffers, NUM_FRAME_BUFFERS * SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(u16));

    initScheduler();
    
    // Set up PI
    osCreatePiManager(OS_PRIORITY_PIMGR, &piMesgQueue, &piMessages[0], NUM_PI_MESSAGES);

    // Set up SI
    osCreateMesgQueue(&siMesgQueue, siMessages, NUM_SI_MESSAGES);
    osSetEventMesg(OS_EVENT_SI, &siMesgQueue, NULL);

#ifdef DEBUG_MODE
    debug_initialize();
#endif

    // Create the audio thread
    osCreateThread(&g_threads[AUDIO_THREAD_INDEX], AUDIO_THREAD, audioThreadFunc, NULL, audioThreadStack + AUDIO_THREAD_STACKSIZE, AUDIO_THREAD_PRI);
    // Start the audio thread
    osStartThread(&g_threads[AUDIO_THREAD_INDEX]);

    // Create the main thread
    osCreateThread(&g_threads[MAIN_THREAD_INDEX], MAIN_THREAD, mainThreadFunc, NULL, mainThreadStack + MAIN_THREAD_STACKSIZE, MAIN_THREAD_PRI);
    // Start the main thread
    osStartThread(&g_threads[MAIN_THREAD_INDEX]);

    // Set this thread's priority to 0, making it the idle thread
    osSetThreadPri(NULL, 0);

    // idle
    while (1);
}
