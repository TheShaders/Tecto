#include <ultra64.h>

#include <input.h>
#include <mathutils.h>
#include <mem.h>

static OSContStatus controllerStatuses[MAXCONTROLLERS];
static OSContPad contPads[MAXCONTROLLERS];

void initInput()
{
    u8 bitPattern; // TODO use this to repoll
    osContInit(&siMesgQueue, &bitPattern, controllerStatuses);

}

void beginInputPolling()
{
    osContStartReadData(&siMesgQueue);
}

// Based on N64 controller values
// Maximum x axis value from controller (scaled down a bit to account for controller variation)
#define R0 (72)
// Angle between x axis and the first octant line segment of the controller bounds octagon (as an s16 angle)
#define ALPHA (14541)
// Sin of the above alpha value
#define SIN_ALPHA (0.98443781700784162202923616551396f)

void readInput(InputData *inputBuffer, int numControllers)
{
    OSContPad *curPad;
    osContGetReadData(contPads);
    for (curPad = &contPads[0]; curPad != &contPads[numControllers]; curPad++)
    {
        float x2raw = POW2(curPad->stick_x);
        float y2raw = POW2(curPad->stick_y);
        float curMagnitude = sqrtf(x2raw + y2raw);
        s32 angle;
        
        angle = (s32)(u16)atan2s(curPad->stick_x, curPad->stick_y);
        inputBuffer->angle = angle;

        if (angle & 0x2000) // Check if this is in an odd octant
        {
            angle = 0x2000 - (angle & 0x1FFF);
        }
        else
        {
            angle &= 0x1FFF;
        }

        inputBuffer->magnitude = MIN(curMagnitude * sins(angle + ALPHA) / (R0 * SIN_ALPHA * 32768.0f), 1.0f);
        inputBuffer->x = (inputBuffer->magnitude / 32768.0f) * coss(inputBuffer->angle);
        inputBuffer->y = (inputBuffer->magnitude / 32768.0f) * sins(inputBuffer->angle);
        inputBuffer++;
    }
}
