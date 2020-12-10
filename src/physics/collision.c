#include <float.h>

// libultra
#include <ultra64.h>

// game code
#include <types.h>
#include <physics.h>
#include <collision.h>
#include <mathutils.h>

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

u32 testVerticalRayVsAABB(Vec3 rayStart, float lengthInv, AABB *box, float tmin, float tmax)
{
    float t0, t1;

    if (rayStart[0] > box->max[0] || rayStart[0] < box->min[0] || rayStart[2] > box->max[2] || rayStart[2] < box->min[2])
        return 0;

    // y
    t0 = (box->min[1] - rayStart[1]) * lengthInv;
    t1 = (box->max[1] - rayStart[1]) * lengthInv;

    tmin = MAX(tmin, MIN(t0, t1));
    tmax = MIN(tmax, MAX(t0, t1));
    
    if (tmin > tmax)
        return 0;
    
    return 1;
}

float verticalRayVsAABB(Vec3 rayStart, float lengthInv, AABB *box, float tmin, float tmax)
{
    float t0, t1;

    if (rayStart[0] > box->max[0] || rayStart[0] < box->min[0] || rayStart[2] > box->max[2] || rayStart[2] < box->min[2])
        return FLT_MAX;

    // y
    t0 = (box->min[1] - rayStart[1]) * lengthInv;
    t1 = (box->max[1] - rayStart[1]) * lengthInv;

    tmin = MAX(tmin, MIN(t0, t1));
    tmax = MIN(tmax, MAX(t0, t1));
    
    if (tmin > tmax)
        return FLT_MAX;
    
    return tmin;
}

u32 testRayVsAABB(Vec3 rayStart, Vec3 rayDirInv, AABB *box, float tmin, float tmax)
{
    float t0, t1;

    // x
    t0 = (box->min[0] - rayStart[0]) * rayDirInv[0];
    t1 = (box->max[0] - rayStart[0]) * rayDirInv[0];

    tmin = MAX(tmin, MIN(t0, t1));
    tmax = MIN(tmax, MAX(t0, t1));
    
    if (tmin > tmax)
        return 0;

    // y
    t0 = (box->min[1] - rayStart[1]) * rayDirInv[1];
    t1 = (box->max[1] - rayStart[1]) * rayDirInv[1];

    tmin = MAX(tmin, MIN(t0, t1));
    tmax = MIN(tmax, MAX(t0, t1));
    
    if (tmin > tmax)
        return 0;

    // z
    t0 = (box->min[2] - rayStart[2]) * rayDirInv[2];
    t1 = (box->max[2] - rayStart[2]) * rayDirInv[2];

    tmin = MAX(tmin, MIN(t0, t1));
    tmax = MIN(tmax, MAX(t0, t1));
    
    if (tmin > tmax)
        return 0;
    
    return 1;
}

float rayVsAABB(Vec3 rayStart, Vec3 rayDirInv, AABB *box, float tmin, float tmax)
{
    float t0, t1;

    // x
    t0 = (box->min[0] - rayStart[0]) * rayDirInv[0];
    t1 = (box->max[0] - rayStart[0]) * rayDirInv[0];

    tmin = MAX(tmin, MIN(t0, t1));
    tmax = MIN(tmax, MAX(t0, t1));
    
    if (tmin > tmax)
        return FLT_MAX;

    // y
    t0 = (box->min[1] - rayStart[1]) * rayDirInv[1];
    t1 = (box->max[1] - rayStart[1]) * rayDirInv[1];

    tmin = MAX(tmin, MIN(t0, t1));
    tmax = MIN(tmax, MAX(t0, t1));
    
    if (tmin > tmax)
        return FLT_MAX;

    // z
    t0 = (box->min[2] - rayStart[2]) * rayDirInv[2];
    t1 = (box->max[2] - rayStart[2]) * rayDirInv[2];

    tmin = MAX(tmin, MIN(t0, t1));
    tmax = MIN(tmax, MAX(t0, t1));
    
    if (tmin > tmax)
        return FLT_MAX;
    
    return tmin;
}

float verticalRayVsTri(Vec3 rayStart, float length, ColTri *tri, float tmin, float tmax)
{
    float denom; // Denominator for calculating ray intersection distance
    float distOnRay; // Intersection point distance on ray
    Vec3 intersection; // Ray/plane intersection point
    Vec3 w; // Intersection point - vertex1
    float uu, uv, vv, wu, wv; // Dot products
    float s, t; // Barycentric coordinates

    // Intersect the ray with the plane that the surface lies in
    denom = tri->normal[1] * length;

    // Prevent division by zero and throw out collision with backfaces (negative denominator)
    if (denom > -EPSILON)
    {
        return FLT_MAX;
    }

    // Calculate distance of intersection point along ray (scaled to ray's length)
    distOnRay = -((tri->originDist) + VEC3_DOT(tri->normal, rayStart)) / denom;
    if (distOnRay > tmax)
    {
        return FLT_MAX;
    }
    if (distOnRay < tmin)
    {
        return FLT_MAX;
    }

    // Calculate the intersection point from the calculated distance
    VEC3_COPY(intersection, rayStart);
    intersection[1] += length * distOnRay;

    // Calculate the barycentric coordinates of the triangle vertices and intersection point
    VEC3_DIFF(w, intersection, tri->vertex);

    uu = tri->uu;
    uv = tri->uv;
    vv = tri->vv;
    
    wu = VEC3_DOT(w, tri->u);
    wv = VEC3_DOT(w, tri->v);

    // Calculate and check the barycentric coordinates
    denom = (uv * uv - uu * vv); // Doesn't need to be checked for 0 (assuming non-degenerate triangles)
    s = (uv * wv - vv * wu) / denom;
    if (s < 0 || s > 1)
    {
        return FLT_MAX;
    }
    t = (uv * wu - uu * wv) / denom;
    if (t < 0 || (s + t) > 1)
    {
        return FLT_MAX;
    }
    return distOnRay;
}

float rayVsTri(Vec3 rayStart, Vec3 rayDir, ColTri *tri, float tmin, float tmax)
{
    float denom; // Denominator for calculating ray intersection distance
    float distOnRay; // Intersection point distance on ray
    Vec3 intersection; // Ray/plane intersection point
    Vec3 w; // Intersection point - vertex1
    float uu, uv, vv, wu, wv; // Dot products
    float s, t; // Barycentric coordinates

    // Intersect the ray with the plane that the surface lies in
    denom = VEC3_DOT(tri->normal, rayDir);

    // Prevent division by zero and throw out collision with backfaces (negative denominator)
    if (denom > -EPSILON)
    {
        return FLT_MAX;
    }

    // Calculate distance of intersection point along ray (scaled to ray's length)
    distOnRay = -((tri->originDist) + VEC3_DOT(tri->normal, rayStart)) / denom;
    if (distOnRay > tmax)
    {
        return FLT_MAX;
    }
    if (distOnRay < tmin)
    {
        return FLT_MAX;
    }

    // Calculate the intersection point from the calculated distance
    VEC3_SCALE(intersection, rayDir, distOnRay);
    VEC3_ADD(intersection, rayStart, intersection);

    // Calculate the barycentric coordinates of the triangle vertices and intersection point
    VEC3_DIFF(w, intersection, tri->vertex);

    uu = tri->uu;
    uv = tri->uv;
    vv = tri->vv;
    
    wu = VEC3_DOT(w, tri->u);
    wv = VEC3_DOT(w, tri->v);

    // Calculate and check the barycentric coordinates
    denom = (uv * uv - uu * vv); // Doesn't need to be checked for 0 (assuming non-degenerate triangles)
    s = (uv * wv - vv * wu) / denom;
    if (s < -EPSILON || s > (1 + EPSILON))
    {
        return FLT_MAX;
    }
    t = (uv * wu - uu * wv) / denom;
    if (t < -EPSILON || (s + t) > (1 + EPSILON))
    {
        return FLT_MAX;
    }
    return distOnRay;
}

// Number of radial rays to cast to find walls
// #define COLLIDER_RAYCAST_RADIAL_COUNT 16
#define COLLIDER_RAYCAST_RADIAL_COUNT 8

static const Vec3 wallRayDirs[COLLIDER_RAYCAST_RADIAL_COUNT] = {
    {  1.0000f, 0.0f,  0.0000f },
    // {  0.9239f, 0.0f,  0.3827f },
    {  0.7071f, 0.0f,  0.7071f },
    // {  0.3827f, 0.0f,  0.9239f },
    {  0.0000f, 0.0f,  1.0000f },
    // { -0.3827f, 0.0f,  0.9239f },
    { -0.7071f, 0.0f,  0.7071f },
    // { -0.9239f, 0.0f,  0.3827f },
    { -1.0000f, 0.0f,  0.0000f },
    // { -0.9239f, 0.0f, -0.3827f },
    { -0.7071f, 0.0f, -0.7071f },
    // { -0.3827f, 0.0f, -0.9239f },
    {  0.0000f, 0.0f, -1.0000f },
    // {  0.3827f, 0.0f, -0.9239f },
    {  0.7071f, 0.0f, -0.7071f },
    // {  0.9239f, 0.0f, -0.3827f },
};

#define VEL_THRESHOLD 0.1f

void handleWalls(Vec3 pos, Vec3 vel, ColliderParams *collider)
{
    if (ABS(vel[0]) >= VEL_THRESHOLD || ABS(vel[2]) >= VEL_THRESHOLD || collider->floor == NULL)
    {
        int heightIndex, radialIndex;
        Vec3 rayStart = { pos[0], pos[1] + collider->startOffset, pos[2] };
        Vec3 scaledVel;
        VEC3_DIFF(rayStart, rayStart, vel);
        VEC3_SCALE(scaledVel, vel, 1.0f / collider->radius);
        for (heightIndex = 0; heightIndex < collider->numHeights; heightIndex++)
        {
            for (radialIndex = 0; radialIndex < COLLIDER_RAYCAST_RADIAL_COUNT; radialIndex++)
            {
                ColTri *curWall;
                SurfaceType curWallSurfaceType;
                Vec3 rayDir;
                VEC3_ADD(rayDir, wallRayDirs[radialIndex], scaledVel);
                float hitDist = raycast(rayStart, rayDir, 0.0f, collider->radius, &curWall, &curWallSurfaceType);
                if (curWall)
                {
                    float pushDist = hitDist - collider->radius;
                    Vec3 pushVec;
                    VEC3_SCALE(pushVec, wallRayDirs[radialIndex], pushDist);
                    VEC3_ADD(pos, pos, pushVec);
                    rayStart[0] = pos[0];
                    rayStart[2] = pos[2];
                }
            }
            rayStart[1] += collider->ySpacing;
        }
    }
}

ColTri *handleFloorOnGround(Vec3 pos, Vec3 vel, float stepUp, float stepDown, SurfaceType *surfaceTypeHit)
{
    ColTri *floor;
    SurfaceType floorSurfaceType;
    float downdist = raycastVertical(pos, -1.0f, -stepUp, stepDown, &floor, &floorSurfaceType);
    if (floor)
    {
        pos[1] -= downdist;
        vel[1] = 0.0f;

        *surfaceTypeHit = floorSurfaceType;

        return floor;
    }
    return NULL;
}

ColTri *handleFloorInAir(Vec3 pos, Vec3 vel, SurfaceType *surfaceTypeHit)
{
    float groundRayLength = vel[1] - 10.0f;
    ColTri *hitTri;
    SurfaceType floorSurfaceType;
    float hitDist;
    hitDist = raycastVertical(pos, groundRayLength, -1.0f, EPSILON, &hitTri, &floorSurfaceType);
    if (hitTri)
    {
        pos[1] += hitDist * groundRayLength;
        vel[1] = 0.0f;

        *surfaceTypeHit = floorSurfaceType;

        return hitTri;
    }
    return NULL;
}
