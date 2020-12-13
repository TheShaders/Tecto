#ifndef __RESIZE_H__
#define __RESIZE_H__

#include <types.h>

#define RESIZE_TIMER_START 60

typedef enum
{
    Size_Grown,
    Size_Shrunk
} SizeState;

typedef enum
{
    Resize_Starting,
    Resize_Ending
} ResizeTrigger;

enum
{
    ResizeType_Shrink_While_Held,
    ResizeType_Grow_While_Held,
    ResizeType_Interactable
};

typedef u8 ResizeType;

typedef void (*ResizeCallback)(ResizeParams *newState, ResizeTrigger trigger);

typedef struct ResizeParams_t {
    SizeState curSize : 1;
    int growTemporary : 1;
    int growAllowed : 1;
    int shrinkAllowed : 1;
    int horizontalIndicator : 1;
    int reserved : 3;

    u8 grownTime;
    u8 resizeTimer;
    ResizeType type;
    u8 restoreTimer;
    float smallScale;
    float largeScale;
    ResizeCallback callback;
} ResizeParams;

void tickResizables(void);

#endif
