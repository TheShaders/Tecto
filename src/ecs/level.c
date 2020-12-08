#include <level.h>
#include <ecs.h>
#include <mem.h>
#include <string.h>

struct LevelCreateEntitiesCallbackArg_t {
    archetype_t archetype;
    void **componentArrays;
};

void levelCreateEntitiesCallback(size_t count, void *arg, void **componentArrays)
{
    archetype_t archetype = ((struct LevelCreateEntitiesCallbackArg_t *)arg)->archetype;
    void **curComponentSourceArray = ((struct LevelCreateEntitiesCallbackArg_t *)arg)->componentArrays;
    void **curComponentDestArray = componentArrays;
    archetype_t archetypeBits = archetype;
    int curComponentIndex = 0;

    // Check every component in the archetype
    while (archetypeBits)
    {
        // If the archetype has the current component, check the source array to see if it has data
        if (archetypeBits & 0x01)
        {
            // If the source data has an array for this component, copy it into the destination
            if (*curComponentSourceArray)
            {
                // Get the size of the current component
                int curComponentSize = g_componentSizes[curComponentIndex];
                // Calculate how many bytes to copy
                int numBytes = curComponentSize * count;
                // Copy the bytes from the source array to the destination array
                memcpy(*curComponentDestArray, *curComponentSourceArray, numBytes);
                // Increment the current component array by the number of bytes copied (in preparation for the next callback)
                *curComponentSourceArray += numBytes;
            }
            // Continue to the next component destination and source arrays
            curComponentSourceArray++;
            curComponentDestArray++;
        }

        // Continue to the next component
        archetypeBits >>= 1;
        curComponentIndex++;
    }
}

void processLevelHeader(LevelHeader *header)
{
    int archetypesRemaining = header->archetypeCount;
    int *entityArchetypeCounts = segmentedToVirtual(header->entityArchetypeCounts);
    archetype_t *curArchetypePtr = segmentedToVirtual(header->entityArchetypes);
    void ***curArchetypeComponentArrayPtr = segmentedToVirtual(header->entityComponentData);

    // Iterate over every archetype in the level header
    while (archetypesRemaining)
    {
        archetype_t curArchetype = *curArchetypePtr;
        int numComponents = NUM_COMPONENTS(curArchetype);
        void *curComponentArrays[numComponents];
        int i;
        struct LevelCreateEntitiesCallbackArg_t arg = {
            curArchetype,
            curComponentArrays,
        };

        // Copy the source array pointers into the argument, converting them to virtual addresses
        for (i = 0; i < numComponents; i++)
        {
            curComponentArrays[i] = segmentedToVirtual(((void**)segmentedToVirtual(*curArchetypeComponentArrayPtr))[i]);
        }

        // Create the entities for the current archetype
        createEntitiesCallback(curArchetype, (void*) &arg, *entityArchetypeCounts, levelCreateEntitiesCallback);

        archetypesRemaining--;
        entityArchetypeCounts++;
        curArchetypePtr++;
        curArchetypeComponentArrayPtr++;
    }
}
