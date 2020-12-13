#include <interaction.h>
#include <ecs.h>
#include <mathutils.h>

#include <float.h>

float sqrtf(float value);

typedef struct FindClosestData_t
{
    float *nearPos;
    float maxDistSq;
    float closestDistSq;
    Vec3 *closestPos;
    archetype_t closestArchetype;

} FindClosestData;

void debug_printf(const char*, ...);

void findClosestCallback(size_t count, void *arg, UNUSED int numComponents, archetype_t archetype, void **componentArrays, UNUSED size_t *componentSizes)
{
    FindClosestData *findData = (FindClosestData *)arg;
    
    float maxDistSq = findData->maxDistSq;
    float closestDistSq = findData->closestDistSq;
    archetype_t closestArchetype = findData->closestArchetype;
    Vec3 *closestPos = findData->closestPos;

    Vec3 nearPos = { findData->nearPos[0], findData->nearPos[1], findData->nearPos[2] };
    Vec3 *curPos = componentArrays[COMPONENT_INDEX(Position, archetype)];
    while (count)
    {
        Vec3 posDiff;
        float curDistSq;
        VEC3_DIFF(posDiff, *curPos, nearPos);
        curDistSq = VEC3_DOT(posDiff, posDiff);

        if (curDistSq < maxDistSq && curDistSq < closestDistSq)
        {
            closestDistSq = curDistSq;
            closestPos = curPos;
            closestArchetype = archetype;
        }

        count--;
        curPos++;
    }

    findData->closestDistSq = closestDistSq;
    findData->closestPos = closestPos;
    findData->closestArchetype = closestArchetype;
}

Entity *findClosestEntity(Vec3 pos, archetype_t archetype, float maxDist, float *foundDist, Vec3 foundPos)
{
    FindClosestData findData = 
    {
        .nearPos = pos,
        .maxDistSq = POW2(maxDist),
        .closestDistSq = FLT_MAX,
        .closestPos = NULL,
        .closestArchetype = 0,
    };
    // Entities need a position component to be "close" to something, so only look for ones that have it
    archetype |= Bit_Position;
    iterateOverEntitiesAllComponents(findClosestCallback, &findData, archetype, 0);

    if (findData.closestArchetype != 0)
    {
        Entity *foundEntity = findEntityFromComponent(findData.closestArchetype, COMPONENT_INDEX(Position, findData.closestArchetype), findData.closestPos);
        *foundDist = sqrtf(findData.closestDistSq);
        VEC3_COPY(foundPos, *findData.closestPos);
        return foundEntity;
    }

    return NULL;
}
