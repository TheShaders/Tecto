#include <ecs.h>
#include <static_assert.h>

#define COMPONENT(Name, Type) sizeof(Name),

size_t g_componentSizes[] = {
#include "components.inc.h"
};

#undef COMPONENT
