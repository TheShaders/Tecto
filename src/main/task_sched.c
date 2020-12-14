#include <stdint.h>

// libultra
#include <PR/sched.h>

// game code
#include <task_sched.h>
#include <init.h>

static OSSched scheduler;
static OSScClient gfxClient;
static OSMesgQueue schedQueue;
static OSMesg schedMesg;

static u64 schedStack[OS_SC_STACKSIZE / sizeof(u64)];

void initScheduler(void)
{
    u8 mode;
    switch (osTvType)
    {
        case OS_TV_PAL:
            #ifdef HIGH_RES
            #ifdef INTERLACED
                mode = OS_VI_FPAL_HAN1;
            #else
                mode = OS_VI_FPAL_HAF1;
            #endif
            #else
            #ifdef INTERLACED
                mode = OS_VI_FPAL_LAF1;
            #else
                mode = OS_VI_FPAL_LAN1;
            #endif
            #endif
            break;
        case OS_TV_MPAL:
            #ifdef HIGH_RES
            #ifdef INTERLACED
                mode = OS_VI_MPAL_HAN1;
            #else
                mode = OS_VI_MPAL_HAF1;
            #endif
            #else
            #ifdef INTERLACED
                mode = OS_VI_MPAL_LAF1;
            #else
                mode = OS_VI_MPAL_LAN1;
            #endif
            #endif
            break;
        case OS_TV_NTSC:
        default:
            #ifdef HIGH_RES
            #ifdef INTERLACED
                mode = OS_VI_NTSC_HAN1;
            #else
                mode = OS_VI_NTSC_HAF1;
            #endif
            #else
            #ifdef INTERLACED
                mode = OS_VI_NTSC_LAF1;
            #else
                mode = OS_VI_NTSC_LAN1;
            #endif
            #endif
            break;
    }
    #ifdef FPS30
    osCreateScheduler(&scheduler, &schedStack[OS_SC_STACKSIZE / sizeof(u64)], SCHEDULER_PRI, mode, 2);
    #else
    osCreateScheduler(&scheduler, &schedStack[OS_SC_STACKSIZE / sizeof(u64)], SCHEDULER_PRI, mode, 1);
    #endif
    osCreateMesgQueue(&schedQueue, &schedMesg, 1);
    osScAddClient(&scheduler, &gfxClient, &schedQueue);
    osViSetSpecialFeatures(OS_VI_GAMMA_OFF);
}

void scheduleGfxTask(OSScTask *task)
{
    osSendMesg(&scheduler.cmdQ, (OSMesg)task, OS_MESG_NOBLOCK);
}
