#ifndef __MATHUTILS_H__
#define __MATHUTILS_H__

#include <types.h>

// TODO these can be vectorized with gcc for modern platforms
#define VEC3_DOT(a,b) ((a)[0] * (b)[0] + (a)[1] * (b)[1] + (a)[2] * (b)[2])
#define VEC3_COPY(out,a) \
    {(out)[0] = (a)[0];           (out)[1] = (a)[1];           (out)[2] = (a)[2];}
#define VEC3_SCALE(out,a,scale) \
    {(out)[0] = (a)[0] * (scale); (out)[1] = (a)[1] * (scale); (out)[2] = (a)[2] * (scale);}
#define VEC3_ADD(out,a,b)  \
    {(out)[0] = (a)[0] + (b)[0];  (out)[1] = (a)[1] + (b)[1];  (out)[2] = (a)[2] + (b)[2];}
#define VEC3_DIFF(out,a,b) \
    {(out)[0] = (a)[0] - (b)[0];  (out)[1] = (a)[1] - (b)[1];  (out)[2] = (a)[2] - (b)[2];}
#define ABS(x) ((x) > 0 ? (x) : -(x))

#define POW2(x) ((x) * (x))

#define M_PIf (3.14159265358979323846f)
#define M_PIf_2 (1.57079632679489661923f)

#define M_PI_4_P_0273	(1.05839816339744830962f) //M_PI/4 + 0.273
#define M_PI_4 (M_PIf / 4)

float fastAtanf(float x);
float fastAtan2f(float y, float x);
s16 atan2s(f32 y, f32 x);

#endif
