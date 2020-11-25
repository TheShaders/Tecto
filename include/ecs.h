#ifndef __ECS_H__
#define __ECS_H__

#include <types.h>

#define MAX_ARCHETYPES 1024

#define COMPONENT(Name, Type) Component_##Name,

enum Components
{
#include "components.inc.h"
NUM_COMPONENT_TYPES
};

#undef COMPONENT

#define COMPONENT(Name, Type) Bit_##Name = 1 << Component_##Name,

enum ComponentBits
{
#include "components.inc.h"
};

#undef COMPONENT

// Callback provided to the ecs to be called for every array of a given component selection when iterating
typedef void (*EntityArrayCallback)(size_t count, void **componentArrays);

// Calls the given callback for each array that fits the given archetype and does not fit the reject archetype
void iterateOverComponents(EntityArrayCallback callback, archetype_t componentMask, archetype_t rejectMask);
// Registers a new archetype
void registerArchetype(archetype_t archetype);
// Gets the arraylist for a given archetype
MultiArrayList* getArchetypeArray(archetype_t archetype);

extern const size_t g_componentSizes[];

#endif
