#include <ultra64.h>
#include <model.h>
#include <gfx.h>
#include <collision.h>
#include <surface_types.h>
#include <level.h>
#include <ecs.h>
#include <physics.h>
#include <resize.h>

#include "assets/friend1/model.inc.c"
#include "assets/friend1/anims/data.inc.c"

#include "assets/friend2/model.inc.c"
#include "assets/friend2/anims/data.inc.c"

#include "assets/friendplayer/model.inc.c"
#include "assets/friendplayer/anims/data.inc.c"

#include "assets/credits/model.inc.c"
#include "assets/credits/anims/data.inc.c"

extern Model friend1_model;
extern Model friend2_model;
extern Model friendplayer_model;
extern Model credits_model;

extern Animation friend1_anim_Friend_Idle;
extern Animation friend2_anim_Run;
extern Animation friendplayer_anim_Dance;
extern Animation credits_anim_Action;

Vec3 credits_ARCHETYPE_ANIM_MODEL_Positions[4] = {
    {-236.0f, 0.0f, 0.0f},
    {-20.0f, 0.0f, 0.0f},
    {236.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
};

Vec3s credits_ARCHETYPE_ANIM_MODEL_Rotations[4] = {
    {0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000},
};

Model *credits_ARCHETYPE_ANIM_MODEL_Models[4] = {
    &friend1_model,
    &friend2_model,
    &friendplayer_model,
    &credits_model,
};

AnimState credits_ARCHETYPE_ANIM_MODEL_AnimStates[4] = {
    { .anim = &friend1_anim_Friend_Idle, .counter = 0, .speed = 1 << ANIM_COUNTER_SHIFT, .triggerIndex = 0},
    { .anim = &friend2_anim_Run, .counter = 0, .speed = 1 << ANIM_COUNTER_SHIFT, .triggerIndex = 0},
    { .anim = &friendplayer_anim_Dance, .counter = 0, .speed = 1 << ANIM_COUNTER_SHIFT, .triggerIndex = 0},
    { .anim = &credits_anim_Action, .counter = 0, .speed = 1 << 3, .triggerIndex = 0},
};

// Bit_Position | Bit_Rotation | Bit_Model | Bit_AnimState
void *credits_ARCHETYPE_ANIM_MODEL_ComponentData[NUM_COMPONENTS(ARCHETYPE_ANIM_MODEL)] = {
    credits_ARCHETYPE_ANIM_MODEL_Positions, // pos
    credits_ARCHETYPE_ANIM_MODEL_Rotations, // rotation
    credits_ARCHETYPE_ANIM_MODEL_Models, // model
    credits_ARCHETYPE_ANIM_MODEL_AnimStates, // animstate
};

archetype_t creditsArchetypes[1] = {
    ARCHETYPE_ANIM_MODEL,
};

int creditsArchetypeCounts[1] = {
    4,
};

void **creditsComponentData[1] = {
    credits_ARCHETYPE_ANIM_MODEL_ComponentData,
};

LevelHeader creditsHeader = {
    1, // archetype count
    creditsArchetypes, // archetypes
    creditsArchetypeCounts, // archetype counts
    creditsComponentData, // archetype component data
};
