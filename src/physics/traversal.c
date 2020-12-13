#include <float.h>
#include <collision.h>
#include <mem.h>
#include <ecs.h>
#include <surface_types.h>

#include <PR/gbi.h>
#include <gfx.h>

#define ARCHETYPE_COLLISION (Bit_Collision)
#define ARCHETYPE_POS_COLLISION (Bit_Position | Bit_Collision)
#define ARCHETYPE_ROT_COLLISION (Bit_Collision | Bit_Rotation)
#define ARCHETYPE_POSROT_COLLISION (Bit_Position | Bit_Collision | Bit_Rotation)

float verticalRayVsBvh(Vec3 rayStart, float length, BVHTree *bvh, float tmin, float tmax, ColTri **hitOut, SurfaceType *floorSurface)
{
    float hitDist = FLT_MAX;
    ColTri *hitTri = NULL;
    SurfaceType hitSurfaceType = SURFACE_NONE;
    BVHNode *nodes = (BVHNode*) segmentedToVirtual(bvh->nodes);
    BVHNode *curNode = nodes;
    ColTri *tris = (ColTri*) segmentedToVirtual(bvh->tris);
    SurfaceType *surfaceTypes = (SurfaceType*) segmentedToVirtual(bvh->surfaceTypes);
    float lengthInv = 1.0f / length;

    // The exit case is a -1 next node index, so we can compare the "-1st" node address to terminate the loop
    // The other exit case is every node being checked, which would end up at the end of the array
    while (curNode >= nodes && curNode != &nodes[bvh->nodeCount])
    {
        if (testVerticalRayVsAABB(rayStart, lengthInv, &curNode->aabb, tmin, tmax))
        {
            if (curNode->triCount)
            {
                ColTri *curTri;
                SurfaceType *curSurfaceType = &surfaceTypes[curNode->firstTriIndex];
                for (curTri = &tris[curNode->firstTriIndex]; curTri != &tris[curNode->firstTriIndex + curNode->triCount]; curTri++)
                {
                    float curHitDist = verticalRayVsTri(rayStart, length, curTri, tmin, tmax);
                    if (curHitDist < hitDist)
                    {
                        hitDist = curHitDist;
                        hitTri = curTri;
                        hitSurfaceType = *curSurfaceType;
                    }
                    curSurfaceType++;
                }
            }
            curNode++;
        }
        else
        {
            curNode = &nodes[curNode->missNodeIndex];
        }
    }

    if (hitTri)
    {
        *hitOut = hitTri;
        *floorSurface = hitSurfaceType;
    }
    return hitDist;
}

float rayVsBvh(Vec3 rayStart, Vec3 rayDir, BVHTree *bvh, float tmin, float tmax, ColTri **hitOut, SurfaceType *floorSurface)
{
    float hitDist = FLT_MAX;
    ColTri *hitTri = NULL;
    SurfaceType hitSurfaceType = SURFACE_NONE;
    BVHNode *nodes = (BVHNode*) segmentedToVirtual(bvh->nodes);
    BVHNode *curNode = nodes;
    ColTri *tris = (ColTri*) segmentedToVirtual(bvh->tris);
    SurfaceType *surfaceTypes = (SurfaceType*) segmentedToVirtual(bvh->surfaceTypes);
    Vec3 rayDirInv = { 1.0f / rayDir[0], 1.0f / rayDir[1], 1.0f / rayDir[2] };

    // The exit case is a -1 next node index, so we can compare the "-1st" node address to terminate the loop
    // The other exit case is every node being checked, which would end up at the end of the array
    while (curNode >= nodes && curNode != &nodes[bvh->nodeCount])
    {
        if (testRayVsAABB(rayStart, rayDirInv, &curNode->aabb, tmin, tmax))
        {
            if (curNode->triCount)
            {
                ColTri* curTri;
                SurfaceType *curSurfaceType = &surfaceTypes[curNode->firstTriIndex];
                for (curTri = &tris[curNode->firstTriIndex]; curTri != &tris[curNode->firstTriIndex + curNode->triCount]; curTri++)
                {
                    float curHitDist = rayVsTri(rayStart, rayDir, curTri, tmin, tmax);
                    if (curHitDist < hitDist)
                    {
                        hitDist = curHitDist;
                        hitTri = curTri;
                        hitSurfaceType = *curSurfaceType;
                    }
                    curSurfaceType++;
                }
            }
            curNode++;
        }
        else
        {
            curNode = &nodes[curNode->missNodeIndex];
        }
    }

    if (hitTri)
    {
        *hitOut = hitTri;
        *floorSurface = hitSurfaceType;
    }
    return hitDist;
}

typedef struct RaycastVerticalData_t {
    float *origin;
    float len;
    float tmin;
    float tmax;
    ColTri *hitTri; // Triangle hit by the ray, if any
    SurfaceType hitSurfaceType; // Type of the triangle hit by the ray, if any
    float hitDist; // Distance of hit point along ray (scaled by the ray's length)
} RaycastVerticalData;

typedef struct RaycastData_t {
    float *origin;
    float *rayDir;
    float tmin;
    float tmax;
    ColTri *hitTri; // Triangle hit by the ray, if any
    SurfaceType hitSurfaceType; // Type of the triangle hit by the ray, if any
    float hitDist; // Distance of hit point along ray (scaled by the ray's length)
} RaycastData;

void raycastVerticalIterator(size_t count, void *data, void **componentArrays)
{
    BVHTree **curTree = componentArrays[COMPONENT_INDEX(Collision, ARCHETYPE_COLLISION)];
    RaycastVerticalData *rayData = (RaycastVerticalData *)data;
    ColTri *curTri;
    SurfaceType curSurfaceType;
    Vec3 origin = { rayData->origin[0], rayData->origin[1], rayData->origin[2] };
    float rayLen = rayData->len;
    float tmin = rayData->tmin;
    float tmax = rayData->tmax;

    while (count)
    {
        if (*curTree)
        {
            float curDist = verticalRayVsBvh(origin, rayLen, segmentedToVirtual(*curTree), tmin, tmax, &curTri, &curSurfaceType);
            if (curDist < rayData->hitDist)
            {
                rayData->hitDist = curDist;
                rayData->hitTri = curTri;
                rayData->hitSurfaceType = curSurfaceType;
            }
        }
        curTree++;
        count--;
    }
}

void raycastPositionVerticalIterator(size_t count, void *data, void **componentArrays)
{
    BVHTree **curTree = componentArrays[COMPONENT_INDEX(Collision, ARCHETYPE_POS_COLLISION)];
    Vec3 *curPos = componentArrays[COMPONENT_INDEX(Position, ARCHETYPE_POS_COLLISION)];
    RaycastVerticalData *rayData = (RaycastVerticalData *)data;
    ColTri *curTri;
    SurfaceType curSurfaceType;
    Vec3 origin = { rayData->origin[0], rayData->origin[1], rayData->origin[2] };
    float rayLen = rayData->len;
    float tmin = rayData->tmin;
    float tmax = rayData->tmax;

    while (count)
    {
        if (*curTree)
        {
            Vec3 curOrigin;
            float curDist;
            VEC3_DIFF(curOrigin, origin, *curPos);
            curDist = verticalRayVsBvh(curOrigin, rayLen, segmentedToVirtual(*curTree), tmin, tmax, &curTri, &curSurfaceType);
            if (curDist < rayData->hitDist)
            {
                rayData->hitDist = curDist;
                rayData->hitTri = curTri;
                rayData->hitSurfaceType = curSurfaceType;
            }
        }
        curTree++;
        curPos++;
        count--;
    }
}

void raycastPositionRotationVerticalIterator(size_t count, void *data, void **componentArrays)
{
    BVHTree **curTree = componentArrays[COMPONENT_INDEX(Collision, ARCHETYPE_POSROT_COLLISION)];
    Vec3 *curPos = componentArrays[COMPONENT_INDEX(Position, ARCHETYPE_POSROT_COLLISION)];
    Vec3s *curRot = componentArrays[COMPONENT_INDEX(Rotation, ARCHETYPE_POSROT_COLLISION)];
    RaycastVerticalData *rayData = (RaycastVerticalData *)data;
    ColTri *curTri;
    SurfaceType curSurfaceType;
    Vec3 origin = { rayData->origin[0], rayData->origin[1], rayData->origin[2] };
    Vec3 rayDir = { 0, rayData->len, 0 };
    float tmin = rayData->tmin;
    float tmax = rayData->tmax;

    while (count)
    {
        if (*curTree)
        {
            Vec3 curOrigin;
            Vec3 curOriginRot;
            Vec3 curDir;
            MtxF invMat;
            float curDist;
            VEC3_DIFF(curOrigin, origin, *curPos);
            mtxfEulerXYZInverse(invMat, (*curRot)[0], (*curRot)[1], (*curRot)[2]);
            mtxfRotateVec(invMat, rayDir, curDir);
            mtxfRotateVec(invMat, curOrigin, curOriginRot);
            // Can't use a vertical collision, since the ray is rotated now
            curDist = rayVsBvh(curOriginRot, curDir, segmentedToVirtual(*curTree), tmin, tmax, &curTri, &curSurfaceType);
            if (curDist < rayData->hitDist)
            {
                rayData->hitDist = curDist;
                rayData->hitTri = curTri;
                rayData->hitSurfaceType = curSurfaceType;
            }
        }
        curTree++;
        curPos++;
        curRot++;
        count--;
    }
}

void raycastIterator(size_t count, void *data, void **componentArrays)
{
    BVHTree **curTree = componentArrays[COMPONENT_INDEX(Collision, ARCHETYPE_COLLISION)];
    RaycastData *rayData = (RaycastData *)data;
    ColTri *curTri;
    SurfaceType curSurfaceType;
    Vec3 origin = { rayData->origin[0], rayData->origin[1], rayData->origin[2] };
    Vec3 rayDir = { rayData->rayDir[0], rayData->rayDir[1], rayData->rayDir[2] };
    float tmin = rayData->tmin;
    float tmax = rayData->tmax;

    while (count)
    {
        if (*curTree)
        {
            float curDist = rayVsBvh(origin, rayDir, segmentedToVirtual(*curTree), tmin, tmax, &curTri, &curSurfaceType);
            if (curDist < rayData->hitDist)
            {
                rayData->hitDist = curDist;
                rayData->hitTri = curTri;
                rayData->hitSurfaceType = curSurfaceType;
            }
        }
        curTree++;
        count--;
    }
}

void raycastPositionIterator(size_t count, void *data, void **componentArrays)
{
    BVHTree **curTree = componentArrays[COMPONENT_INDEX(Collision, ARCHETYPE_POS_COLLISION)];
    Vec3 *curPos = componentArrays[COMPONENT_INDEX(Position, ARCHETYPE_POS_COLLISION)];
    RaycastData *rayData = (RaycastData *)data;
    ColTri *curTri;
    SurfaceType curSurfaceType;
    Vec3 origin = { rayData->origin[0], rayData->origin[1], rayData->origin[2] };
    Vec3 rayDir = { rayData->rayDir[0], rayData->rayDir[1], rayData->rayDir[2] };
    float tmin = rayData->tmin;
    float tmax = rayData->tmax;

    while (count)
    {
        if (*curTree)
        {
            Vec3 curOrigin;
            float curDist;
            VEC3_DIFF(curOrigin, origin, *curPos);
            curDist = rayVsBvh(curOrigin, rayDir, segmentedToVirtual(*curTree), tmin, tmax, &curTri, &curSurfaceType);
            if (curDist < rayData->hitDist)
            {
                rayData->hitDist = curDist;
                rayData->hitTri = curTri;
                rayData->hitSurfaceType = curSurfaceType;
            }
        }
        curTree++;
        curPos++;
        count--;
    }
}

void raycastPositionRotationIterator(size_t count, void *data, void **componentArrays)
{
    BVHTree **curTree = componentArrays[COMPONENT_INDEX(Collision, ARCHETYPE_POSROT_COLLISION)];
    Vec3 *curPos = componentArrays[COMPONENT_INDEX(Position, ARCHETYPE_POSROT_COLLISION)];
    Vec3s *curRot = componentArrays[COMPONENT_INDEX(Rotation, ARCHETYPE_POSROT_COLLISION)];
    RaycastData *rayData = (RaycastData *)data;
    ColTri *curTri;
    SurfaceType curSurfaceType;
    Vec3 origin = { rayData->origin[0], rayData->origin[1], rayData->origin[2] };
    Vec3 rayDir = { rayData->rayDir[0], rayData->rayDir[1], rayData->rayDir[2] };
    float tmin = rayData->tmin;
    float tmax = rayData->tmax;

    while (count)
    {
        if (*curTree)
        {
            Vec3 curOrigin;
            Vec3 curOriginRot;
            Vec3 curDir;
            MtxF invMat;
            float curDist;
            VEC3_DIFF(curOrigin, origin, *curPos);
            mtxfEulerXYZInverse(invMat, (*curRot)[0], (*curRot)[1], (*curRot)[2]);
            mtxfRotateVec(invMat, rayDir, curDir);
            mtxfRotateVec(invMat, curOrigin, curOriginRot);
            curDist = rayVsBvh(curOriginRot, curDir, segmentedToVirtual(*curTree), tmin, tmax, &curTri, &curSurfaceType);
            if (curDist < rayData->hitDist)
            {
                rayData->hitDist = curDist;
                rayData->hitTri = curTri;
                rayData->hitSurfaceType = curSurfaceType;
            }
        }
        curTree++;
        curPos++;
        curRot++;
        count--;
    }
}

float raycastVertical(Vec3 rayOrigin, float rayLength, float tmin, float tmax, ColTri **hitOut, SurfaceType *floorSurface)
{
    RaycastVerticalData data = {rayOrigin, rayLength, tmin, tmax, NULL, SURFACE_NONE, FLT_MAX};

    iterateOverEntities(raycastVerticalIterator, &data, ARCHETYPE_COLLISION, Bit_Position | Bit_Rotation);
    iterateOverEntities(raycastPositionVerticalIterator, &data, ARCHETYPE_POS_COLLISION, Bit_Rotation);
    // TODO rotation only
    iterateOverEntities(raycastPositionRotationVerticalIterator, &data, ARCHETYPE_POSROT_COLLISION, 0);

    *hitOut = data.hitTri;
    *floorSurface = data.hitSurfaceType;
    return data.hitDist;
}

float raycast(Vec3 rayOrigin, Vec3 rayDir, float tmin, float tmax, ColTri **hitOut, SurfaceType *floorSurface)
{
    RaycastData data = {rayOrigin, rayDir, tmin, tmax, NULL, SURFACE_NONE, FLT_MAX};

    iterateOverEntities(raycastIterator, &data, ARCHETYPE_COLLISION, Bit_Position | Bit_Rotation);
    iterateOverEntities(raycastPositionIterator, &data, ARCHETYPE_POS_COLLISION, Bit_Rotation);
    // TODO rotation only
    iterateOverEntities(raycastPositionRotationIterator, &data, ARCHETYPE_POSROT_COLLISION, 0);

    *hitOut = data.hitTri;
    *floorSurface = data.hitSurfaceType;
    return data.hitDist;
}
