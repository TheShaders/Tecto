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

#define COMPONENT_INDEX(Component, Archetype) (__builtin_popcount((Archetype) & (Bit_##Component - 1)))

#define ARCHETYPE_MODEL (Bit_Position | Bit_Rotation | Bit_Model)
#define ARCHETYPE_ANIM_MODEL (Bit_Position | Bit_Rotation | Bit_Model | Bit_AnimState)
#define ARCHETYPE_PLAYER (Bit_Position | Bit_Velocity | Bit_Rotation | Bit_Behavior | Bit_Model | Bit_AnimState)

// Callback provided to the ecs to be called for every array of a given component selection when iterating
typedef void (*EntityArrayCallback)(size_t count, void *arg, void **componentArrays);

// Callback provided to the ecs to be called for every array of a given component selection when iterating
// This callback is passed ALL components in each entity, not just the ones passed in the mask
typedef void (*EntityArrayCallbackAll)(size_t count, void *arg, int numComponents, archetype_t archetype, void **componentArrays, size_t *componentSizes);

// Callback for entities that have a behavior component
// First argument passed is an array of the component pointers
// Second argument is the value of data in the behavior parameters
typedef void (*EntityBehaviorCallback)(void **components, void *data);

typedef struct BehaviorParams_t
{
    EntityBehaviorCallback callback;
    void *data;
} BehaviorParams;

// Creates a single entity, try to avoid using as creating entities in batches is more efficient
Entity *createEntity(archetype_t archetype);
// Creates a number of entities
void createEntities(archetype_t archetype, int count);
// Creates a number of entities, and calls the provided callback for each block of allocated entities
void createEntitiesCallback(archetype_t archetype, void *arg, int count, EntityArrayCallback callback);

// Calls the given callback for each array that fits the given archetype and does not fit the reject archetype
void iterateOverEntities(EntityArrayCallback callback, void *arg, archetype_t componentMask, archetype_t rejectMask);
// Same as above, but this time an array of ALL components is passed (not just the masked ones), as well as an array of component sizes
void iterateOverEntitiesAllComponents(EntityArrayCallbackAll callback, void *arg, archetype_t componentMask, archetype_t rejectMask);
// Registers a new archetype
void registerArchetype(archetype_t archetype);
// Gets the arraylist for a given archetype
MultiArrayList* getArchetypeArray(archetype_t archetype);

extern const size_t g_componentSizes[];

#endif
