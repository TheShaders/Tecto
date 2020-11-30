#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <types.h>

typedef struct Camera_t {
    Vec3 target;
    float yOffset;
    float fov;
    float distance;
    s16 pitch;
    s16 yaw;
    s16 roll;
} Camera;

extern Camera g_Camera;

#endif
