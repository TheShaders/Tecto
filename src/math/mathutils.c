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

void mtxfMul(MtxF out, MtxF a, MtxF b)
{
    float a00=a[0][0];
    float a01=a[0][1];
    float a02=a[0][2];
    float a03=a[0][3];

    float a10=a[1][0];
    float a11=a[1][1];
    float a12=a[1][2];
    float a13=a[1][3];

    float a20=a[2][0];
    float a21=a[2][1];
    float a22=a[2][2];
    float a23=a[2][3];

    float a30=a[3][0];
    float a31=a[3][1];
    float a32=a[3][2];
    float a33=a[3][3];

    float b00=b[0][0];
    float b01=b[0][1];
    float b02=b[0][2];
    float b03=b[0][3];

    float b10=b[1][0];
    float b11=b[1][1];
    float b12=b[1][2];
    float b13=b[1][3];

    float b20=b[2][0];
    float b21=b[2][1];
    float b22=b[2][2];
    float b23=b[2][3];

    float b30=b[3][0];
    float b31=b[3][1];
    float b32=b[3][2];
    float b33=b[3][3];

    out[0][0] = a00*b00+a10*b01+a20*b02+a30*b03;
    out[0][1] = a01*b00+a11*b01+a21*b02+a31*b03;
    out[0][2] = a02*b00+a12*b01+a22*b02+a32*b03;
    out[0][3] = a03*b00+a13*b01+a23*b02+a33*b03;

    out[1][0] = a00*b10+a10*b11+a20*b12+a30*b13;
    out[1][1] = a01*b10+a11*b11+a21*b12+a31*b13;
    out[1][2] = a02*b10+a12*b11+a22*b12+a32*b13;
    out[1][3] = a03*b10+a13*b11+a23*b12+a33*b13;

    out[2][0] = a00*b20+a10*b21+a20*b22+a30*b23;
    out[2][1] = a01*b20+a11*b21+a21*b22+a31*b23;
    out[2][2] = a02*b20+a12*b21+a22*b22+a32*b23;
    out[2][3] = a03*b20+a13*b21+a23*b22+a33*b23;

    out[3][0] = a00*b30+a10*b31+a20*b32+a30*b33;
    out[3][1] = a01*b30+a11*b31+a21*b32+a31*b33;
    out[3][2] = a02*b30+a12*b31+a22*b32+a32*b33;
    out[3][3] = a03*b30+a13*b31+a23*b32+a33*b33;
}

void mtxfEulerXYZ(MtxF out, s16 rx, s16 ry, s16 rz)
{
    float s1 = sinsf(rx);
    float c1 = cossf(rx);
    float s2 = sinsf(ry);
    float c2 = cossf(ry);
    float s3 = sinsf(rz);
    float c3 = cossf(rz);

    out[0][0] = c2 * c3;
    out[0][1] = c2 * s3;
    out[0][2] = -s2;
    out[0][3] = 0.0f;

    out[1][0] = s1 * s2 * c3 - c1 * s3;
    out[1][1] = s1 * s2 * s3 + c1 * c3;
    out[1][2] = s1 * c2;
    out[1][3] = 0.0f;

    out[2][0] = c1 * s2 * c3 + s1 * s3;
    out[2][1] = c1 * s2 * s3 - s1 * c3;
    out[2][2] = c1 * c2;
    out[2][3] = 0.0f;

    out[3][0] = 0.0f;
    out[3][1] = 0.0f;
    out[3][2] = 0.0f;
    out[3][3] = 1.0f;
}

// Transforms a given vector by the given matrix, ignoring any translation in the matrix
void mtxfRotateVec(MtxF mat, Vec3 vecIn, Vec3 vecOut)
{
    vecOut[0] = vecIn[0] * mat[0][0] + vecIn[1] * mat[1][0] + vecIn[2] * mat[2][0];
    vecOut[1] = vecIn[0] * mat[0][1] + vecIn[1] * mat[1][1] + vecIn[2] * mat[2][1];
    vecOut[2] = vecIn[0] * mat[0][2] + vecIn[1] * mat[1][2] + vecIn[2] * mat[2][2];
}
