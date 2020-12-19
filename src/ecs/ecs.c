#include <stdint.h>

#include <ecs.h>
#include <multiarraylist.h>
#include <mem.h>
#include <model.h>
#include <physics.h>
#include <collision.h>
#include <resize.h>

#define COMPONENT(Name, Type) sizeof(Type),

const size_t g_componentSizes[] = {
#include "components.inc.h"
};

#undef COMPONENT

int archetypeEntityCounts[MAX_ARCHETYPES];
archetype_t currentArchetypes[MAX_ARCHETYPES];
MultiArrayList archetypeArrays[MAX_ARCHETYPES];

int numArchetypes = 0;

Entity allEntities[MAX_ENTITIES];
// End of the populated entities in the array
int entitiesEnd = 0;
// Actual number of entities (accounts for gaps in the array)
int numEntities = 0;
int numGaps = 0;
int firstGap = INT32_MAX;

// Underlying implementation for popcount
// https://stackoverflow.com/questions/109023/how-to-count-the-number-of-set-bits-in-a-32-bit-integer
int numberOfSetBits(uint32_t i)
{
     i = i - ((i >> 1) & 0x55555555);
     i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
     return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

void iterateOverEntities(EntityArrayCallback callback, void *arg, archetype_t componentMask, archetype_t rejectMask)
{
    int componentIndex, curArchetypeIndex;
    int numComponents = NUM_COMPONENTS(componentMask);
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
                callback(curBlock->numElements, arg, curAddresses);
                // Advance to the next block
                curBlock = curBlock->next;
            }
        }
    }
}

void iterateOverEntitiesAllComponents(EntityArrayCallbackAll callback, void *arg, archetype_t componentMask, archetype_t rejectMask)
{
    int curArchetypeIndex;
    for (curArchetypeIndex = 0; curArchetypeIndex < numArchetypes; curArchetypeIndex++)
    {
        archetype_t curArchetype = currentArchetypes[curArchetypeIndex];
        if (((curArchetype & componentMask) == componentMask) && !(curArchetype & rejectMask))
        {
            int curComponentIndex;
            int curNumComponents = NUM_COMPONENTS(curArchetype);
            int curNumComponentsFound = 0;
            archetype_t componentBits = curArchetype;
            MultiArrayList *arr = &archetypeArrays[curArchetypeIndex];
            MultiArrayListBlock *curBlock = arr->start;
            size_t curComponentSizes[curNumComponents];
            size_t curOffsets[curNumComponents];
            void* curAddresses[curNumComponents];
            size_t curOffset = sizeof(MultiArrayListBlock);
            
            // Find all components in the current archetype and determine their size and offset in the multi array block
            curComponentIndex = 0;
            while (componentBits)
            {
                if (componentBits & 1)
                {
                    curOffsets[curNumComponentsFound] = curOffset;
                    curComponentSizes[curNumComponentsFound] = g_componentSizes[curComponentIndex];
                    curOffset += curComponentSizes[curNumComponentsFound] * arr->elementCount;
                    curNumComponentsFound++;
                }
                componentBits >>= 1;
                curComponentIndex++;
            }

            // Iterate over every block in this multiarray
            while (curBlock)
            {
                int i;
                // Get the addresses for each sub-array in the block
                for (i = 0; i < curNumComponents; i++)
                {
                    curAddresses[i] = (void*)(curOffsets[i] + (uintptr_t)curBlock);
                }
                // Call the provided callback
                callback(curBlock->numElements, arg, curNumComponents, curArchetype, curAddresses, curComponentSizes);
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
    // If the loop completed then the archetype isn't registered, so register it
    registerArchetype(archetype);
    // Return the last archetype, which will be the newly registered one
    return numArchetypes - 1;
}

int findNextGap(int prevGap)
{
    int retVal;
    for (retVal = prevGap + 1; retVal < entitiesEnd; retVal++)
    {
        if (allEntities[retVal].archetype == 0)
        {
            return retVal;
        }
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
    int curGap = firstGap;

    // Fill in any gaps in the entity array
    while (numGaps)
    {
        allEntities[curGap].archetype = archetype;
        allEntities[curGap].archetypeArrayIndex = archetypeEntityCount++;
        curGap = findNextGap(curGap);
        curNumEntities++;
        numGaps--;
        count--;
    }
    // Update the first gap index
    firstGap = curGap;

    // Append new entities to the end of the array
    for (curEntity = &allEntities[entitiesEnd]; curEntity < &allEntities[entitiesEnd + count]; curEntity++)
    {
        curEntity->archetype = archetype;
        curEntity->archetypeArrayIndex = archetypeEntityCount++;
        curNumEntities++;
    }

    // Update the count of entities of this archetype
    archetypeEntityCounts[archetypeIndex] = archetypeEntityCount;
    // Update the total entity count
    numEntities = curNumEntities;

    // If the entity list has run past the previous end index, update the end
    if (numEntities > entitiesEnd)
    {
        entitiesEnd = numEntities;
    }
}

Entity *createEntity(archetype_t archetype)
{
    // The index of this archetype
    int archetypeIndex = getArchetypeIndex(archetype);
    Entity *curEntity;
    // The arraylist for this archetype
    MultiArrayList *archetypeList = &archetypeArrays[archetypeIndex];
    
    // Allocate the components for the new entity
    multiarraylist_alloccount(archetypeList, 1);

    if (numGaps)
    {
        curEntity = &allEntities[firstGap];
        firstGap = findNextGap(firstGap);
    }
    else
    {
        curEntity = &allEntities[entitiesEnd];
        entitiesEnd++;
    }

    curEntity->archetype = archetype;
    curEntity->archetypeArrayIndex = archetypeEntityCounts[archetypeIndex];

    archetypeEntityCounts[archetypeIndex]++;
    numEntities++;

    return curEntity;
}

void deleteEntity(Entity *e)
{
    // The index of this archetype
    int archetypeIndex = getArchetypeIndex(e->archetype);
    size_t newLength = --archetypeEntityCounts[archetypeIndex];
    Entity *curEntity;
    int i;

    multiarraylist_delete(&archetypeArrays[archetypeIndex], e->archetypeArrayIndex);

    // Ugly linear search over all entities to update the archetype array index of the entity that was moved in the delete
    // TODO keep the entity list sorted?
    for (curEntity = &allEntities[0]; curEntity != &allEntities[entitiesEnd]; curEntity++)
    {
        if (curEntity->archetypeArrayIndex == newLength)
        {
            curEntity->archetypeArrayIndex = e->archetypeArrayIndex;
            break;
        }
    }
    
    // Find the deleted entity in the list and clear its data
    for (i = 0; i < entitiesEnd; i++)
    {
        if (&allEntities[i] == e)
        {
            allEntities[i].archetype = 0;
            allEntities[i].archetypeArrayIndex = 0;
            numEntities--;
            // If this is the last entity, update the end index
            if (i == entitiesEnd - 1)
            {
                entitiesEnd--;
            }
            // Otherwise, increase the number of gaps
            else
            {
                numGaps++;
                // If this new gap is less than the previous first gap, update the first gap to this one
                if (i < firstGap)
                {
                    firstGap = i;
                }
            }
            break;
        }
    }
}

void deleteEntityIndex(int index)
{
    // The archetype and array list index for this entity
    archetype_t archetype = allEntities[index].archetype;
    size_t archetypeArrayIndex = allEntities[index].archetypeArrayIndex;
    // The index of this archetype
    int archetypeIndex = getArchetypeIndex(archetype);
    size_t newLength = --archetypeEntityCounts[archetypeIndex];
    Entity *curEntity;

    // Delete this entity's component info
    multiarraylist_delete(&archetypeArrays[archetypeIndex], archetypeArrayIndex);

    // Ugly linear search over all entities to update the archetype array index of the entity that was moved in the delete
    // TODO keep the entity list sorted?
    for (curEntity = &allEntities[0]; curEntity != &allEntities[entitiesEnd]; curEntity++)
    {
        if (curEntity->archetypeArrayIndex == newLength)
        {
            curEntity->archetypeArrayIndex = archetypeArrayIndex;
            break;
        }
    }
    
    // Clear the deleted entity's data
    allEntities[index].archetype = 0;
    allEntities[index].archetypeArrayIndex = 0;
    numEntities--;

    // If this is the last entity, update the end index
    if (index == entitiesEnd - 1)
    {
        entitiesEnd--;
    }
    // Otherwise, increase the number of gaps
    else
    {
        numGaps++;
        // If this new gap is less than the previous first gap, update the first gap to this one
        if (index < firstGap)
        {
            firstGap = index;
        }
    }
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
}

void createEntitiesCallback(archetype_t archetype, void *arg, int count, EntityArrayCallback callback)
{
    // The index of this archetype
    int archetypeIndex = getArchetypeIndex(archetype);
    // The arraylist for this archetype
    MultiArrayList *archetypeList = &archetypeArrays[archetypeIndex];
    // Number of components in the given archetype
    int numComponents = NUM_COMPONENTS(archetype);

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

        callback(curBlock->numElements - startingElementCount, arg, componentArrays);
        curBlock = curBlock->next;

        // Call the callback for any following blocks, which were allocated
        while (curBlock)
        {
            for (i = 0; i < numComponents; i++)
            {
                componentArrays[i] = (void*)((uintptr_t)curBlock + componentOffsets[i]);
            }

            callback(curBlock->numElements, arg, componentArrays);
            curBlock = curBlock->next;
        }
    }
}

void getEntityComponents(Entity *entity, void **componentArrayOut)
{
    archetype_t archetype = entity->archetype;
    int archetypeIndex = getArchetypeIndex(archetype);
    MultiArrayList *archetypeArray = &archetypeArrays[archetypeIndex];
    size_t blockElementCount = archetypeArray->elementCount;
    size_t arrayIndex = entity->archetypeArrayIndex;
    MultiArrayListBlock *curBlock = archetypeArray->start;
    int componentIndex = 0; // Index of the component in all components
    int componentArrayIndex = 0; // Index of the component in those in the archetype

    while (arrayIndex >= blockElementCount)
    {
        curBlock = curBlock->next;
        arrayIndex -= blockElementCount;
    }

    while (archetype)
    {
        if (archetype & 0x01)
        {
            componentArrayOut[componentArrayIndex] = (void *)(
                (uintptr_t)curBlock + // skip the block header
                multiarraylist_get_component_offset(archetypeArray, componentIndex) + // go to the start of the component array for this component
                g_componentSizes[componentIndex] * arrayIndex), // index the component array
            componentArrayIndex++;
        }
        componentIndex++;
        archetype >>= 1;
    }
}

Entity *findEntity(archetype_t archetype, size_t archetypeArrayIndex)
{
    Entity* curEntity;

    for (curEntity = &allEntities[0]; curEntity != &allEntities[entitiesEnd]; curEntity++)
    {
        if (curEntity->archetype == archetype && curEntity->archetypeArrayIndex == archetypeArrayIndex)
            return curEntity;
    }
    return NULL;
}

Entity *findEntityFromComponent(archetype_t archetype, int componentIndex, void* componentPointer)
{
    MultiArrayList *archetypeArray = &archetypeArrays[getArchetypeIndex(archetype)];
    // Take advantage of the fact that array list blocks are chunk aligned and chunk sized,
    // so round down to the nearest chunk start to get the block this component is in
    MultiArrayListBlock *archetypeArrayBlock = (MultiArrayListBlock *)ROUND_DOWN((uintptr_t)componentPointer, MEM_CHUNK_SIZE);
    // Get the start of the component array for the given component type
    uintptr_t componentArrayStart = (uintptr_t)archetypeArrayBlock + multiarraylist_get_component_offset(archetypeArray, componentIndex);
    // Get the index into the array by dividing the offset into the array by the component's size
    size_t archetypeArrayIndex = ((uintptr_t)componentPointer - componentArrayStart) / g_componentSizes[componentIndex];

    return findEntity(archetype, archetypeArrayIndex);
}

extern void bzero(void *, int);

void deleteAllEntities(void)
{
    int archetypeIndex;
    for (archetypeIndex = 0; archetypeIndex < numArchetypes; archetypeIndex++)
    {
        MultiArrayList *curArr = &archetypeArrays[archetypeIndex];
        MultiArrayListBlock *curBlock = curArr->start;

        bzero(curArr, sizeof(MultiArrayList));
        archetypeEntityCounts[archetypeIndex] = 0;
        currentArchetypes[archetypeIndex] = 0;
        while (curBlock)
        {
            MultiArrayListBlock *nextBlock = curBlock->next;

            freeAlloc(curBlock);

            curBlock = nextBlock;
        }
    }
    numArchetypes = 0;
    bzero(allEntities, sizeof(allEntities));
    numEntities = 0;
    entitiesEnd = 0;
    numGaps = 0;
    firstGap = 0;
}
