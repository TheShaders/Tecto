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

#define IS_NOT_LEAF_NODE(bvhNode) ((bvhNode).triCount != 0)
#define IS_LEAF_NODE(bvhNode) ((bvhNode).triCount == 0)

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

// A node in a bounding volume hierarchy tree
typedef struct BVHNode_t {
    u16 triCount; // 0 if this is not a leaf node, otherwise the number of triangles in this node
    u16 firstTriIndex; // Index of the first triangle for this node
    s16 missNodeIndex; // Index of the node to move to if this AABB test is a miss
    u16 reserved;
    AABB aabb;
} BVHNode;

// Bounding volume hierarchy tree
typedef struct BVHTree_t {
    u16 triCount;
    u16 nodeCount;
    ColTri* tris;
    BVHNode* nodes;
} BVHTree;

u32 testVerticalRayVsAABB(Vec3 rayStart, float lengthInv, AABB *box, float tmin, float tmax);
f32 verticalRayVsAABB(Vec3 rayStart, float lengthInv, AABB *box, float tmin, float tmax);
u32 testRayVsAABB(Vec3 rayStart, Vec3 rayDirInv, AABB *box, float tmin, float tmax);
f32 rayVsAABB(Vec3 rayStart, Vec3 rayDirInv, AABB *box, float tmin, float tmax);
f32 verticalRayVsTri(Vec3 rayStart, float length, ColTri *tri, float tmin, float tmax);
f32 rayVsTri(Vec3 rayStart, Vec3 rayDir, ColTri *tri, float tmin, float tmax);

f32 rayVsBvh(Vec3 rayStart, Vec3 rayDirInv, BVHTree *bvh, float tmin, float tmax, ColTri **hitOut);
f32 verticalRayVsBvh(Vec3 rayStart, float length, BVHTree *bvh, float tmin, float tmax, ColTri **hitOut);

#endif
