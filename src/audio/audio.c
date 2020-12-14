#include <audio.h>
#include <ultra64.h>
#include <mem.h>
#include <stdint.h>

#define SINE_FREQ 440

s16 audioBuffers[NUM_AUDIO_BUFFERS][AUDIO_BUFFER_LEN] __attribute__((aligned (64)));

OSMesgQueue audioMsgQueue;
OSMesg audioMsg;

u16 curAudioBuffer = 0;
s32 realSampleRate;

OSMesgQueue audioDmaMesgQueue;

OSIoMesg audioDmaIoMessage;
OSMesg audioDmaMessage;

u8* song;

extern u8 _soundsSegmentRomStart[], _soundsSegmentRomEnd[];
extern s16 music_start[], music_end[];
extern s16 rockstep_1_start[], rockstep_1_end[];
extern s16 rockstep_2_start[], rockstep_2_end[];
extern s16 grassstep_1_start[], grassstep_1_end[];
extern s16 grassstep_2_start[], grassstep_2_end[];

typedef struct InstrumentData_t {
    s16 *curSamplePtr;
    s32 samplesRemaining;
    u8 loop;
    u8 reserved1;
    u8 reserved2;
    u8 reserved3;
} InstrumentData;

s16 *soundStarts[] = {
    NULL, // music_start,
    rockstep_1_start,
    rockstep_2_start,
};

s16 *soundEnds[] = {
    NULL, // music_end,
    rockstep_1_end,
    rockstep_2_end,
};

#define MAX_INSTRUMENTS 16

InstrumentData curInstruments[MAX_INSTRUMENTS];

u8 *audioSegAddr;

void audioInit(void)
{
    osCreateMesgQueue(&audioMsgQueue, &audioMsg, 1);
    osSetEventMesg(OS_EVENT_AI, &audioMsgQueue, NULL);

    // Set up a zero buffer to prevent any audio pop at startup
    bzero(audioBuffers[2], AUDIO_BUFFER_LEN * sizeof(u16));
    osAiSetNextBuffer(&audioBuffers[2], AUDIO_BUFFER_LEN * sizeof(u16));

    // Set up the audio frequency
    realSampleRate = osAiSetFrequency(SAMPLE_RATE);

    bzero(curInstruments, sizeof(curInstruments));

    // Allocate RAM for the sounds segment to be DMA'd to
    audioSegAddr = allocRegion((u32)_soundsSegmentRomEnd - (u32)_soundsSegmentRomStart, ALLOC_AUDIO);
    
    // Update the segment table
    setSegment(0x0A, audioSegAddr);

    // DMA the sounds segment and wait for the DMA to finish
    startDMA(audioSegAddr, _soundsSegmentRomStart, (u32)_soundsSegmentRomEnd - (u32)_soundsSegmentRomStart);
    waitForDMA();
}

void fillAudioBuffer(u32 bufferIndex)
{
    s16 *audioPtr = &audioBuffers[bufferIndex][0];
    s16 *endPtr = &audioBuffers[bufferIndex][AUDIO_BUFFER_LEN];

    do
    {
        InstrumentData *curInstrument = &curInstruments[0];
        InstrumentData *instrumentsEnd = &curInstruments[MAX_INSTRUMENTS];

        audioPtr[0] = 0;
        audioPtr[1] = 0;

        do
        {
            if (curInstrument->samplesRemaining > 0)
            {
                audioPtr[0] += curInstrument->curSamplePtr[0];
                audioPtr[1] += curInstrument->curSamplePtr[1];\
                curInstrument->curSamplePtr += 2;
                curInstrument->samplesRemaining--;
            }
            curInstrument++;
        } while (curInstrument != instrumentsEnd);

        audioPtr += 2;
    }
    while (audioPtr != endPtr);
}

void playSound(u32 soundIndex, u32 loop)
{
    int i;
    for (i = 0; i < NUM_INSTRUMENTS; i++)
    {
        if (curInstruments[i].samplesRemaining <= 0)
        {
            s16 *soundStart = soundStarts[soundIndex];
            s16 *soundEnd = soundEnds[soundIndex];
            // 2 s16 values per sample (stereo)
            curInstruments[i].curSamplePtr = segmentedToVirtual(soundStart);
            curInstruments[i].loop = loop;
            curInstruments[i].samplesRemaining = ((uintptr_t)soundEnd - (uintptr_t)soundStart) / (sizeof(s16) * 2);
            return;
        }
    }
}

void audioThreadFunc(UNUSED void *arg)
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
