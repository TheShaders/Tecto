#ifndef __ECS_H__
#define __ECS_H__

#include <types.h>

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

extern size_t g_componentSizes[];

#endif
