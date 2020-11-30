#include <ultra64.h>

#include <input.h>
#include <mathutils.h>
#include <mem.h>

InputData g_PlayerInput;

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

#define numControllers 1

void readInput()
{
    OSContPad *curPad;
    osContGetReadData(contPads);
    for (curPad = &contPads[0]; curPad != &contPads[numControllers]; curPad++)
    {
        float x2raw = POW2(curPad->stick_x);
        float y2raw = POW2(curPad->stick_y);
        float curMagnitude = sqrtf(x2raw + y2raw);
        float magnitude;
        s32 angle;
        s32 octantAngle;
        
        angle = (s32)(u16)atan2s(curPad->stick_x, curPad->stick_y);

        if (angle & 0x2000) // Check if this is in an odd octant
        {
            octantAngle = 0x2000 - (angle & 0x1FFF);
        }
        else
        {
            octantAngle = angle & 0x1FFF;
        }

        magnitude = MIN(curMagnitude * sinsf(octantAngle + ALPHA) / (R0 * SIN_ALPHA), 1.0f);

        if (magnitude < INPUT_DEADZONE)
        {
            magnitude = 0.0f;
        }

        g_PlayerInput.magnitude = magnitude;
        g_PlayerInput.angle = angle;
        g_PlayerInput.x = (magnitude) * cossf(angle);
        g_PlayerInput.y = (magnitude) * sinsf(angle);
        g_PlayerInput.buttonsPressed = (curPad->button) & ~g_PlayerInput.buttonsHeld;
        g_PlayerInput.buttonsHeld = curPad->button;
    }
}
