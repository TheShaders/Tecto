#ifndef __COLLISION_H__
#define __COLLISION_H__

#include <PR/ultratypes.h>
#include <types.h>

typedef struct AABB_t {
    Vec3 min;
    Vec3 max;
} AABB;

s32 rayVsAABB(Vec3 rayStart, Vec3 rayDirInv, AABB *box, float tmin, float tmax);

#endif
