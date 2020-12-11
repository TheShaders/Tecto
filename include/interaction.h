#ifndef __INTERACTION_H__
#define __INTERACTION_H__

#include <types.h>

Entity *findClosestEntity(Vec3 pos, archetype_t archetype, float maxDist, float *foundDist);

#endif
