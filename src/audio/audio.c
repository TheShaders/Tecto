#include <audio.h>
#include <ultra64.h>

#define SINE_FREQ 440

s16 audioBuffers[NUM_AUDIO_BUFFERS][AUDIO_BUFFER_LEN + 100] __attribute__((aligned (64)));

OSMesgQueue audioMsgQueue;
OSMesg audioMsg;

u16 curAudioBuffer = 0;
u32 audioPhaseAngle = 0;
s32 realSampleRate;

void audioInit(void)
{
    osCreateMesgQueue(&audioMsgQueue, &audioMsg, 1);
    osSetEventMesg(OS_EVENT_AI, &audioMsgQueue, NULL);
    realSampleRate = osAiSetFrequency(SAMPLE_RATE);
}

void fillAudioBuffer(u32 bufferIndex)
{
    s16 *audioPtr = &audioBuffers[bufferIndex][0];
    s16 *endPtr = &audioBuffers[bufferIndex][AUDIO_BUFFER_LEN];

    do
    {
        audioPtr[0] = audioPtr[1] = sins(audioPhaseAngle) / 4; // Left
        audioPtr += 2;
        // *audioPtr++ = sins(2 * audioPhaseAngle) / 4; // Right
        audioPhaseAngle += (0x10000L * SINE_FREQ / SAMPLE_RATE);
    }
    while (audioPtr != endPtr);
}

void audioThreadFunc(__attribute__((unused)) void *arg)
{
    audioInit();

    // Set up the first audio buffer
    fillAudioBuffer(curAudioBuffer);
    // Clear any pending messages from the queue
    while (!MQ_IS_EMPTY(&audioMsgQueue))
    {
        osRecvMesg(&audioMsgQueue, NULL, OS_MESG_BLOCK);
    }
    while (1)
    {
        // Initiate the current buffer's DMA
        osAiSetNextBuffer(&audioBuffers[curAudioBuffer], AUDIO_BUFFER_LEN * sizeof(u16));

        // Set up the next buffer
        curAudioBuffer = (curAudioBuffer + 1) % NUM_AUDIO_BUFFERS;
        fillAudioBuffer(curAudioBuffer);
        
        // Wait for the current buffer to run out
        osRecvMesg(&audioMsgQueue, NULL, OS_MESG_BLOCK);
    }
}