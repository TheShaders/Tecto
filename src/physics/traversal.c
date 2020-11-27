#include <float.h>
#include <collision.h>
#include <mem.h>

#include <PR/gbi.h>
#include <gfx.h>

f32 verticalRayVsBvh(Vec3 rayStart, float length, BVHTree *bvh, float tmin, float tmax, ColTri **hitOut)
{
    f32 hitDist = FLT_MAX;
    ColTri *hitTri = NULL;
    BVHNode *nodes = (BVHNode*) segmentedToVirtual(bvh->nodes);
    BVHNode *curNode = nodes;
    ColTri *tris = (ColTri*) segmentedToVirtual(bvh->tris);
    f32 lengthInv = 1.0f / length;

    // The exit case is a -1 next node index, so we can compare the "-1st" node address to terminate the loop
    // The other exit case is every node being checked, which would end up at the end of the array
    while (curNode >= nodes && curNode != &nodes[bvh->nodeCount])
    {
        if (testVerticalRayVsAABB(rayStart, lengthInv, &curNode->aabb, tmin, tmax))
        {
            if (curNode->triCount)
            {
                ColTri* curTri;
                for (curTri = &tris[curNode->firstTriIndex]; curTri != &tris[curNode->firstTriIndex + curNode->triCount]; curTri++)
                {
                    f32 curHitDist = verticalRayVsTri(rayStart, length, curTri, tmin, tmax);
                    if (curHitDist < hitDist)
                    {
                        hitDist = curHitDist;
                        hitTri = curTri;
                    }
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
    }
    return hitDist;
}

f32 rayVsBvh(Vec3 rayStart, Vec3 rayDir, BVHTree *bvh, float tmin, float tmax, ColTri **hitOut)
{
    f32 hitDist = FLT_MAX;
    ColTri *hitTri = NULL;
    BVHNode *nodes = (BVHNode*) segmentedToVirtual(bvh->nodes);
    BVHNode *curNode = nodes;
    ColTri *tris = (ColTri*) segmentedToVirtual(bvh->tris);
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
                for (curTri = &tris[curNode->firstTriIndex]; curTri != &tris[curNode->firstTriIndex + curNode->triCount]; curTri++)
                {
                    f32 curHitDist = rayVsTri(rayStart, rayDir, curTri, tmin, tmax);
                    if (curHitDist < hitDist)
                    {
                        hitDist = curHitDist;
                        hitTri = curTri;
                    }
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
    }
    return hitDist;
}