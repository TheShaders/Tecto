#ifndef __COLLISION_H__
#define __COLLISION_H__

#include <PR/ultratypes.h>
#include <types.h>

#define EPSILON 0.0001f

#define VEC3_DOT(a,b) ((a)[0] * (b)[0] + (a)[1] * (b)[1] + (a)[2] * (b)[2])
#define VEC3_COPY(out,a) \
    {(out)[0] = (a)[0];           (out)[1] = (a)[1];           (out)[2] = (a)[2];}
#define VEC3_SCALE(out,a,scale) \
    {(out)[0] = (a)[0] * (scale); (out)[1] = (a)[1] * (scale); (out)[2] = (a)[2] * (scale);}
#define VEC3_ADD(out,a,b)  \
    {(out)[0] = (a)[0] + (b)[0];  (out)[1] = (a)[1] + (b)[1];  (out)[2] = (a)[2] + (b)[2];}
#define VEC3_DIFF(out,a,b) \
    {(out)[0] = (a)[0] - (b)[0];  (out)[1] = (a)[1] - (b)[1];  (out)[2] = (a)[2] - (b)[2];}
#define ABSI(x) ((x) > 0 ? (x) : -(x))

typedef struct AABB_t {
    Vec3 min;
    Vec3 max;
} AABB;

// Singular collision tri, contains several pieces of redundant info that are used to accelerate calculations
typedef struct ColTri_t {
    // Plane parameters
    Vec3 normal;
    f32 originDist;
    // Tri parameters
    Vec3 vertex; // One of the tri's vertices (only one vertex is required for barycentric coordinates)
    Vec3 u; // Edge vectors
    Vec3 v;
    f32 uu; // Edge dot products
    f32 uv;
    f32 vv;
} ColTri;

// Common data for a node in a bounding volume hierarchy tree
typedef struct BVHNodeBase_t {
    u8 nodeType;
    u8 reserved[3];
    AABB aabb;
} BVHNodeBase;

// BVH node that has other child nodes
typedef struct BVHParentNode_t {
    BVHNodeBase base;
    u32 childCount;
    BVHNodeBase *children;
} BVHParentNode;

// BVH leaf node that points to actual collision data
typedef struct BVHLeafNode_t {
    BVHNodeBase base;
    ColTri *tris;
} BVHLeafNode;

f32 rayVsAABB(Vec3 rayStart, Vec3 rayDirInv, AABB *box, float tmin, float tmax);
f32 rayVsTri(Vec3 rayStart, Vec3 rayDir, ColTri *tri, float tmin, float tmax);

#endif
