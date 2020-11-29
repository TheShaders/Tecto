#ifndef __INPUT_H__
#define __INPUT_H__

#include <types.h>

#define INPUT_DEADZONE 0.05f

typedef struct InputData_t {
    float x;
    float y;
    float magnitude;
    s16 angle;
} InputData;

void initInput();
void beginInputPolling();
void readInput(InputData *inputBuffer, int numControllers);


#endif
