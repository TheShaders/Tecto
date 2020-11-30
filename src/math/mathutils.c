#include <mathutils.h>

float sintable[] = {
#include "sintable.h"
};

s16 atan2sTable[0x401] = {
#include "atan2table.h"
};

// http://nghiaho.com/?p=997
float fastAtanf(float x)
{
    return M_PI_4*x - x*(ABS(x) - 1)*(0.2447 + 0.0663*ABS(x));
}
// atan2approx from https://github.com/ducha-aiki/fast_atan2/blob/master/fast_atan.cpp
float fastAtan2f(float y, float x)
{
  double absx, absy;
  absy = ABS(y);
  absx = ABS(x);
  short octant = ((x<0) << 2) + ((y<0) << 1 ) + (absx <= absy);
  switch (octant) {
    case 0: {
        if (x == 0 && y == 0)
          return 0;
        double val = absy/absx;
        return (M_PI_4_P_0273 - 0.273*val)*val; //1st octant
        break;
      }
    case 1:{
        if (x == 0 && y == 0)
          return 0.0;
        double val = absx/absy;
        return M_PIf_2 - (M_PI_4_P_0273 - 0.273*val)*val; //2nd octant
        break;
      }
    case 2: {
        double val =absy/absx;
        return -(M_PI_4_P_0273 - 0.273*val)*val; //8th octant
        break;
      }
    case 3: {
        double val =absx/absy;
        return -M_PIf_2 + (M_PI_4_P_0273 - 0.273*val)*val;//7th octant
        break;
      }
    case 4: {
        double val =absy/absx;
        return  M_PIf - (M_PI_4_P_0273 - 0.273*val)*val;  //4th octant
      }
    case 5: {
        double val =absx/absy;
        return  M_PIf_2 + (M_PI_4_P_0273 - 0.273*val)*val;//3rd octant
        break;
      }
    case 6: {
        double val =absy/absx;
        return -M_PIf + (M_PI_4_P_0273 - 0.273*val)*val; //5th octant
        break;
      }
    case 7: {
        double val =absx/absy;
        return -M_PIf_2 - (M_PI_4_P_0273 - 0.273*val)*val; //6th octant
        break;
      }
    default:
      return 0.0;
    }
}

u16 atan2_lookup(f32 y, f32 x) {
    u16 ret;

    if (x == 0) {
        ret = atan2sTable[0];
    } else {
        ret = atan2sTable[(s32)(y / x * 1024 + 0.5f)];
    }
    return ret;
}

s16 atan2s(f32 y, f32 x) {
    u16 ret;

    if (x >= 0) {
        if (y >= 0) {
            if (y >= x) {
                ret = atan2_lookup(x, y);
            } else {
                ret = 0x4000 - atan2_lookup(y, x);
            }
        } else {
            y = -y;
            if (y < x) {
                ret = 0x4000 + atan2_lookup(y, x);
            } else {
                ret = 0x8000 - atan2_lookup(x, y);
            }
        }
    } else {
        x = -x;
        if (y < 0) {
            y = -y;
            if (y >= x) {
                ret = 0x8000 + atan2_lookup(x, y);
            } else {
                ret = 0xC000 - atan2_lookup(y, x);
            }
        } else {
            if (y < x) {
                ret = 0xC000 + atan2_lookup(y, x);
            } else {
                ret = -atan2_lookup(x, y);
            }
        }
    }
    return ret;
}

float sinsf(s16 x)
{
    int index = ((u16)x & 0x3FFF) >> 4;
    if (x & 0x4000) // Check if x is in quadrant 2 or 4
    {
        index = 0x400 - index;
    }
    if (x & 0x8000)
    {
        return -sintable[index];
    }
    return sintable[index];
}
