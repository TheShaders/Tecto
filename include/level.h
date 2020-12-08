#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <types.h>

typedef struct LevelHeader_t {
    // Number of archetypes in the level (length of entityArchetypes)
    int archetypeCount;
    // Every archetype in the level
    archetype_t *entityArchetypes;
    // Quantity of entities for each archetype (index i corresponds to the length of index i of entityComponentData)
    int *entityArchetypeCounts;
    // Pointer to an array of pointers to arrays of pointers to component data
    void ***entityComponentData;
} LevelHeader;

void processLevelHeader(LevelHeader *header);

#endif
