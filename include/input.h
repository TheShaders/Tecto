#ifndef __INPUT_H__
#define __INPUT_H__

#include <types.h>

#define INPUT_DEADZONE 0.1f

typedef struct InputData_t {
    float x;
    float y;
    float magnitude;
    s16 angle;
    u16 buttonsHeld;
    u16 buttonsPressed;
} InputData;

extern InputData g_PlayerInput;

void initInput();
void beginInputPolling();
void readInput();


#endif
