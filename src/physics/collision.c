// libultra
#include <ultra64.h>

// game code
#include <types.h>
#include <collision.h>

#define CALC_TMIN_TMAX(coordIndex) {\
    t0 = (box->min[coordIndex] - rayStart[coordIndex]) * rayDirInv[coordIndex];\
    t1 = (box->max[coordIndex] - rayStart[coordIndex]) * rayDirInv[coordIndex];\
    \
    tmin = MAX(tmin, t0);\
    tmax = MIN(tmax, t1);\
    \
    if (tmin > tmax)\
        return FALSE;\
}

s32 rayVsAABB(Vec3 rayStart, Vec3 rayDirInv, AABB *box, float tmin, float tmax)
{
    float t0, t1;

    // x
    t0 = (box->min[0] - rayStart[0]) * rayDirInv[0];
    t1 = (box->max[0] - rayStart[0]) * rayDirInv[0];

    tmin = MAX(tmin, MIN(t0, t1));
    tmax = MIN(tmax, MAX(t0, t1));
    
    if (tmin > tmax)
        return FALSE;

    // y
    t0 = (box->min[1] - rayStart[1]) * rayDirInv[1];
    t1 = (box->max[1] - rayStart[1]) * rayDirInv[1];

    tmin = MAX(tmin, MIN(t0, t1));
    tmax = MIN(tmax, MAX(t0, t1));
    
    if (tmin > tmax)
        return FALSE;

    // z
    t0 = (box->min[2] - rayStart[2]) * rayDirInv[2];
    t1 = (box->max[2] - rayStart[2]) * rayDirInv[2];

    tmin = MAX(tmin, MIN(t0, t1));
    tmax = MIN(tmax, MAX(t0, t1));
    
    return tmax >= tmin;
}
