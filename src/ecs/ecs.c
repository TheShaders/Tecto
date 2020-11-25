#include <ecs.h>
#include <multiarraylist.h>
#include <stdint.h>

#define COMPONENT(Name, Type) sizeof(Name),

const size_t g_componentSizes[] = {
#include "components.inc.h"
};

#undef COMPONENT

archetype_t currentArchetypes[MAX_ARCHETYPES];
MultiArrayList archetypeArrays[MAX_ARCHETYPES];

int numArchetypes = 0;

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
        if ((curArchetype & componentMask) && !(curArchetype & rejectMask))
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
    numArchetypes++;
}

// TODO use binary search after adding sorted archetype array
MultiArrayList* getArchetypeArray(archetype_t archetype)
{
    int i;
    for (i = 0; i < numArchetypes; i++)
    {
        if (currentArchetypes[i] == archetype)
            return &archetypeArrays[i];
    }
    return NULL;
}
