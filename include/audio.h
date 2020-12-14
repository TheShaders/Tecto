#ifndef __AUDIO_H__
#define __AUDIO_H__

#define SAMPLE_RATE 44100
#define AUDIO_BUFFER_LEN (2 * SAMPLE_RATE / 30)

#define NUM_AUDIO_BUFFERS 3
#define NUM_INSTRUMENTS 4

#include <ultra64.h>

extern OSMesgQueue audioMsgQueue;
extern OSMesg audioMsg;

void audioThreadFunc(void *arg);

void playSound(u32 soundIndex, u32 loop);

#endif
