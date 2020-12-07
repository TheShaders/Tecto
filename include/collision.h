#ifndef __COLLISION_H__
#define __COLLISION_H__

#include <types.h>

#define EPSILON 0.0001f

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
    float originDist;
    // Tri parameters
    Vec3 vertex; // One of the tri's vertices (only one vertex is required for barycentric coordinates)
    Vec3 u; // Edge vectors
    Vec3 v;
    float uu; // Edge dot products
    float uv;
    float vv;
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
    SurfaceType* surfaceTypes;
} BVHTree;

u32 testVerticalRayVsAABB(Vec3 rayStart, float lengthInv, AABB *box, float tmin, float tmax);
float verticalRayVsAABB(Vec3 rayStart, float lengthInv, AABB *box, float tmin, float tmax);
u32 testRayVsAABB(Vec3 rayStart, Vec3 rayDirInv, AABB *box, float tmin, float tmax);
float rayVsAABB(Vec3 rayStart, Vec3 rayDirInv, AABB *box, float tmin, float tmax);
float verticalRayVsTri(Vec3 rayStart, float length, ColTri *tri, float tmin, float tmax);
float rayVsTri(Vec3 rayStart, Vec3 rayDir, ColTri *tri, float tmin, float tmax);

float rayVsBvh(Vec3 rayStart, Vec3 rayDirInv, BVHTree *bvh, float tmin, float tmax, ColTri **hitOut);
float verticalRayVsBvh(Vec3 rayStart, float length, BVHTree *bvh, float tmin, float tmax, ColTri **hitOut);

float raycastVertical(Vec3 rayOrigin, float rayLength, float tmin, float tmax, ColTri **hitOut);
float raycast(Vec3 rayOrigin, Vec3 rayDir, float tmin, float tmax, ColTri **hitOut);

typedef struct ColliderParams_t {
    float radius; // Radius of the cylindrical rays to cast
    int numHeights; // Number of sets of cylindrical rays to cast, offset in a vertical pattern
    float startOffset; // The y offset for the first set of rays
    float ySpacing; // The y spacing between sets of rays
    ColTri *floor; // The floor this object is on (NULL if it's in the air)
} ColliderParams;

void handleWalls(Vec3 pos, Vec3 vel, ColliderParams *collider);
ColTri *handleFloorOnGround(Vec3 pos, Vec3 vel, float stepUp, float stepDown);
ColTri *handleFloorInAir(Vec3 pos, Vec3 vel);

#endif
