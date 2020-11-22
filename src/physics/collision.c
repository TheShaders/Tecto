// libultra
#include <ultra64.h>

// game code
#include <types.h>
#include <collision.h>

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

f32 verticalRayVsAABB(Vec3 rayStart, float lengthInv, AABB *box, float tmin, float tmax)
{
    float t0, t1;

    if (rayStart[0] > box->max[0] || rayStart[0] < box->min[0] || rayStart[2] > box->max[2] || rayStart[2] < box->min[2])
        return -1;

    // y
    t0 = (box->min[1] - rayStart[1]) * lengthInv;
    t1 = (box->max[1] - rayStart[1]) * lengthInv;

    tmin = MAX(tmin, MIN(t0, t1));
    tmax = MIN(tmax, MAX(t0, t1));
    
    if (tmin > tmax)
        return -1;
    
    return tmin;
}

f32 rayVsAABB(Vec3 rayStart, Vec3 rayDirInv, AABB *box, float tmin, float tmax)
{
    float t0, t1;

    // x
    t0 = (box->min[0] - rayStart[0]) * rayDirInv[0];
    t1 = (box->max[0] - rayStart[0]) * rayDirInv[0];

    tmin = MAX(tmin, MIN(t0, t1));
    tmax = MIN(tmax, MAX(t0, t1));
    
    if (tmin > tmax)
        return -1;

    // y
    t0 = (box->min[1] - rayStart[1]) * rayDirInv[1];
    t1 = (box->max[1] - rayStart[1]) * rayDirInv[1];

    tmin = MAX(tmin, MIN(t0, t1));
    tmax = MIN(tmax, MAX(t0, t1));
    
    if (tmin > tmax)
        return -1;

    // z
    t0 = (box->min[2] - rayStart[2]) * rayDirInv[2];
    t1 = (box->max[2] - rayStart[2]) * rayDirInv[2];

    tmin = MAX(tmin, MIN(t0, t1));
    tmax = MIN(tmax, MAX(t0, t1));
    
    if (tmin > tmax)
        return -1;
    
    return tmin;
}

f32 verticalRayVsTri(Vec3 rayStart, float length, ColTri *tri, float tmin, float tmax)
{
    f32 denom; // Denominator for calculating ray intersection distance
    f32 distOnRay; // Intersection point distance on ray
    Vec3 intersection; // Ray/plane intersection point
    Vec3 w; // Intersection point - vertex1
    f32 uu, uv, vv, wu, wv; // Dot products
    f32 s, t; // Barycentric coordinates

    // Intersect the ray with the plane that the surface lies in
    denom = tri->normal[1] * length;

    // Prevent division by zero and throw out collision with backfaces (negative denominator)
    if (denom > -EPSILON)
    {
        return -1;
    }

    // Calculate distance of intersection point along ray (scaled to ray's length)
    distOnRay = -((tri->originDist) + VEC3_DOT(tri->normal, rayStart)) / denom;
    if (distOnRay > tmax)
    {
        return -1;
    }
    if (distOnRay < tmin)
    {
        return -1;
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
        return -1;
    }
    t = (uv * wu - uu * wv) / denom;
    if (t < 0 || (s + t) > 1)
    {
        return -1;
    }
    return distOnRay;
}

f32 rayVsTri(Vec3 rayStart, Vec3 rayDir, ColTri *tri, float tmin, float tmax)
{
    f32 denom; // Denominator for calculating ray intersection distance
    f32 distOnRay; // Intersection point distance on ray
    Vec3 intersection; // Ray/plane intersection point
    Vec3 w; // Intersection point - vertex1
    f32 uu, uv, vv, wu, wv; // Dot products
    f32 s, t; // Barycentric coordinates

    // Intersect the ray with the plane that the surface lies in
    denom = VEC3_DOT(tri->normal, rayDir);

    // Prevent division by zero and throw out collision with backfaces (negative denominator)
    if (denom > -EPSILON)
    {
        return -1;
    }

    // Calculate distance of intersection point along ray (scaled to ray's length)
    distOnRay = -((tri->originDist) + VEC3_DOT(tri->normal, rayStart)) / denom;
    if (distOnRay > tmax)
    {
        return -1;
    }
    if (distOnRay < tmin)
    {
        return -1;
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
    if (s < 0 || s > 1)
    {
        return -1;
    }
    t = (uv * wu - uu * wv) / denom;
    if (t < 0 || (s + t) > 1)
    {
        return -1;
    }
    return distOnRay;
}
