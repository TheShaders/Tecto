#ifndef __INIT_H__
#define __INIT_H__

#include <ultra64.h>
#include <config.h>

#define NUM_THREADS 4

#define IDLE_THREAD 1
#define IDLE_THREAD_INDEX (IDLE_THREAD - 1)
#define IDLE_THREAD_STACKSIZE 0x100

#define AUDIO_THREAD 2
#define AUDIO_THREAD_INDEX (AUDIO_THREAD - 1)
#define AUDIO_THREAD_STACKSIZE 0x4000
#define AUDIO_THREAD_PRI 12

#define MAIN_THREAD 3
#define MAIN_THREAD_INDEX (MAIN_THREAD - 1)
#define MAIN_THREAD_STACKSIZE 0x4000
#define MAIN_THREAD_PRI 10

#define SCHEDULER_PRI 13

#define NUM_PI_MESSAGES 8
#define NUM_SI_MESSAGES 8

extern OSThread g_threads[];

void init(void);
void idle(void*);

#endif