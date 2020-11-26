#ifndef __ECS_H__
#define __ECS_H__

#include <types.h>

#define MAX_ARCHETYPES 256

// TODO dynamically allocate entity memory
#define MAX_ENTITIES 65536

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
typedef void (*EntityArrayCallback)(size_t count, void* arg, void **componentArrays);

// Creates a single entity, try to avoid using as creating entities in batches is more efficient
Entity *createEntity(archetype_t archetype);
// Creates a number of entities
void createEntities(archetype_t archetype, int count);
// Creates a number of entities, and calls the provided callback for each block of allocated entities
void createEntitiesCallback(archetype_t archetype, void *arg, int count, EntityArrayCallback callback);

// Calls the given callback for each array that fits the given archetype and does not fit the reject archetype
void iterateOverComponents(EntityArrayCallback callback, void *arg, archetype_t componentMask, archetype_t rejectMask);
// Registers a new archetype
void registerArchetype(archetype_t archetype);
// Gets the arraylist for a given archetype
MultiArrayList* getArchetypeArray(archetype_t archetype);

extern const size_t g_componentSizes[];

#endif
