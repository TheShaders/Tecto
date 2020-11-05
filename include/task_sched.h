#ifndef __SCHED_H__
#define __SCHED_H__

#include <PR/sched.h>

void initScheduler(void);
void scheduleGfxTask(OSScTask* task);
void waitForGfxTaskComplete();

#endif