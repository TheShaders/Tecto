#include <ecs.h>
#include <multiarraylist.h>
#include <stdint.h>

#define COMPONENT(Name, Type) sizeof(Name),

const size_t g_componentSizes[] = {
#include "components.inc.h"
};

#undef COMPONENT

int archetypeEntityCounts[MAX_ARCHETYPES];
archetype_t currentArchetypes[MAX_ARCHETYPES];
MultiArrayList archetypeArrays[MAX_ARCHETYPES];

int numArchetypes = 0;

Entity allEntities[MAX_ENTITIES];
int numEntities = 0;

// https://stackoverflow.com/questions/109023/how-to-count-the-number-of-set-bits-in-a-32-bit-integer
int numberOfSetBits(uint32_t i)
{
     i = i - ((i >> 1) & 0x55555555);
     i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
     return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

void iterateOverComponents(EntityArrayCallback callback, archetype_t componentMask, archetype_t rejectMask)
{
    int componentIndex, curArchetypeIndex;
    int numComponents = numberOfSetBits(componentMask);
    int numComponentsFound = 0;
    size_t components[numComponents];
    archetype_t componentBits = componentMask;

    componentIndex = 0;
    while (componentBits)
    {
        if (componentBits & 1)
        {
            components[numComponentsFound++] = componentIndex;
        }
        componentBits >>= 1;
        componentIndex++;
    }

    for (curArchetypeIndex = 0; curArchetypeIndex < numArchetypes; curArchetypeIndex++)
    {
        archetype_t curArchetype = currentArchetypes[curArchetypeIndex];
        if (((curArchetype & componentMask) == componentMask) && !(curArchetype & rejectMask))
        {
            MultiArrayList *arr = &archetypeArrays[curArchetypeIndex];
            MultiArrayListBlock *curBlock = arr->start;
            size_t curOffsets[numComponents];
            void* curAddresses[numComponents];
            int i;
            
            // Find the offsets for each component
            // TODO this can be optimized by not using multiarraylist_get_component_offset
            for (i = 0; i < numComponents; i++)
            {
                curOffsets[i] = multiarraylist_get_component_offset(arr, components[i]);
            }

            // Iterate over every block in this multiarray
            while (curBlock)
            {
                // Get the addresses for each sub-array in the block
                for (i = 0; i < numComponents; i++)
                {
                    curAddresses[i] = (void*)(curOffsets[i] + (uintptr_t)curBlock);
                }
                // Call the provided callback
                callback(curBlock->numElements, curAddresses);
                // Advance to the next block
                curBlock = curBlock->next;
            }
        }
    }
}

// TODO sort upon add, use binary search to check if already exists
void registerArchetype(archetype_t archetype)
{
    int i;
    // Don't add an archetype that is already registered
    for (i = 0; i < numArchetypes; i++)
    {
        if (currentArchetypes[i] == archetype)
            return;
    }
    currentArchetypes[numArchetypes] = archetype;
    multiarraylist_init(&archetypeArrays[numArchetypes], archetype);
    archetypeEntityCounts[numArchetypes] = 0;
    numArchetypes++;
}

// TODO use binary search after adding sorted archetype array
int getArchetypeIndex(archetype_t archetype)
{
    int i;
    for (i = 0; i < numArchetypes; i++)
    {
        if (currentArchetypes[i] == archetype)
            return i;
    }
    return -1;
}

void allocEntities(archetype_t archetype, int count)
{
    // The index of this archetype
    int archetypeIndex = getArchetypeIndex(archetype);
    int archetypeEntityCount = archetypeEntityCounts[archetypeIndex];
    Entity *curEntity;
    int curNumEntities = numEntities;
    for (curEntity = &allEntities[numEntities]; curEntity < &allEntities[numEntities + count]; curEntity++)
    {
        curEntity->archetype = archetype;
        curEntity->archetypeArrayIndex = archetypeEntityCount++;
        curNumEntities++;
    }
    archetypeEntityCounts[archetypeIndex] = archetypeEntityCount;
    curNumEntities = numEntities;
}

Entity *createEntity(archetype_t archetype)
{
    // The index of this archetype
    int archetypeIndex = getArchetypeIndex(archetype);
    Entity *curEntity = &allEntities[numEntities];
    // The arraylist for this archetype
    MultiArrayList *archetypeList = &archetypeArrays[archetypeIndex];
    
    // Allocate the components for the new entity
    multiarraylist_alloccount(archetypeList, 1);

    curEntity->archetype = archetype;
    curEntity->archetypeArrayIndex = archetypeEntityCounts[archetypeIndex]++;

    archetypeEntityCounts[archetypeIndex]++;

    return curEntity;
}

void createEntities(archetype_t archetype, int count)
{
    // The index of this archetype
    int archetypeIndex = getArchetypeIndex(archetype);
    // The arraylist for this archetype
    MultiArrayList *archetypeList = &archetypeArrays[archetypeIndex];
    
    // Allocate the components for the given number of the given archetype
    multiarraylist_alloccount(archetypeList, count);
    // Allocate the number of entities given of the archetype given
    allocEntities(archetype, count);
    // Increase the entity count for the given archetype by the given amount
    archetypeEntityCounts[archetypeIndex] += count;
}

void createEntitiesCallback(archetype_t archetype, int count, EntityArrayCallback callback)
{
    // The index of this archetype
    int archetypeIndex = getArchetypeIndex(archetype);
    // The arraylist for this archetype
    MultiArrayList *archetypeList = &archetypeArrays[archetypeIndex];
    // Number of components in the given archetype
    int numComponents = numberOfSetBits(archetype);

    // Iteration values
    // Offsets for each component in the arraylist blocks
    size_t componentOffsets[numComponents];
    // Sizes of each component in the arraylist blocks
    size_t componentSizes[numComponents];
    // The block being iterated through
    MultiArrayListBlock *curBlock = archetypeList->end;
    // Number of elements in the current block before allocating more
    u32 startingElementCount = curBlock->numElements;
    
    // Allocate the number of entities given of the archetype given
    allocEntities(archetype, count);
    // Increase the entity count for the given archetype by the given amount
    archetypeEntityCounts[archetypeIndex] += count;
    // Allocate the requested number of entities for the given archetype
    multiarraylist_alloccount(archetypeList, count);

    // Find all the components in this archetype and get their offsets and sizes for iteration
    // TODO this can be optimized by not using multiarraylist_get_component_offset
    {
        int numComponentsFound = 0;
        int componentIndex = 0;
        archetype_t componentBits = archetype;
        while (componentBits)
        {
            if (componentBits & 1)
            {
                componentOffsets[numComponentsFound] = multiarraylist_get_component_offset(archetypeList, componentIndex);
                componentSizes[numComponentsFound++] = g_componentSizes[componentIndex];
            }
            componentBits >>= 1;
            componentIndex++;
        }
    }

    // Call the provided callback for modified or new block in the list
    {
        int i;
        void* componentArrays[numComponents];

        // Call the callback for the original block, which was modified
        for (i = 0; i < numComponents; i++)
        {
            componentArrays[i] = (void*)((uintptr_t)curBlock + componentOffsets[i] + componentSizes[i] * startingElementCount);
        }

        callback(curBlock->numElements - startingElementCount, componentArrays);
        curBlock = curBlock->next;

        // Call the callback for any following blocks, which were allocated
        while (curBlock)
        {
            for (i = 0; i < numComponents; i++)
            {
                componentArrays[i] = (void*)((uintptr_t)curBlock + componentOffsets[i]);
            }

            callback(curBlock->numElements, componentArrays);
            curBlock = curBlock->next;
        }
    }
}
