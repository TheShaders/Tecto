#ifndef __MATHUTILS_H__
#define __MATHUTILS_H__

#include <types.h>
#include <math.h>

#define POW2(x) ((x) * (x))

#define M_PIf (3.14159265358979323846f)
#define M_PIf_2 (1.57079632679489661923f)

#define M_PI_4_P_0273	(1.05839816339744830962f) //M_PI/4 + 0.273
#define M_PI_4 (M_PIf / 4)

float fastAtanf(float x);
float fastAtan2f(float y, float x);
s16 atan2s(f32 y, f32 x);

#endif
