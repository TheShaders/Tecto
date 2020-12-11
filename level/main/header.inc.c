extern Model main_model;
extern Model dande_model;
extern BVHTree main_collision_tree;
extern Animation dandelion_anim_dande_idle;

Vec3 main_ARCHETYPE_MODEL_Positions[1] = {
    {  0.0f, 0.0f,   0.0f},
};

Model *main_ARCHETYPE_MODEL_Models[1] = {
    &main_model,
};

void *main_ARCHETYPE_MODEL_ComponentData[NUM_COMPONENTS(ARCHETYPE_MODEL)] = {
    main_ARCHETYPE_MODEL_Positions, // pos
    NULL, // rot
    main_ARCHETYPE_MODEL_Models, // model
};

Vec3 main_ARCHETYPE_STATIC_COL_Positions[1] = {
    {  0.0f, 0.0f,   0.0f},
};

BVHTree *main_ARCHETYPE_STATIC_COL_Collisions[1] = {
    &main_collision_tree,
};

void *main_ARCHETYPE_STATIC_COL_ComponentData[NUM_COMPONENTS(ARCHETYPE_STATIC_COL)] = {
    main_ARCHETYPE_STATIC_COL_Positions, // pos
    main_ARCHETYPE_STATIC_COL_Collisions, // collision
};

Vec3 main_ARCHETYPE_HOLDABLE_ANIM_Positions[1] = {
    {-305.25, -354.25, -1141.81},
};

ColliderParams main_ARCHETYPE_HOLDABLE_ANIM_Colliders[1] = {
    { .radius = 58.0f, .numHeights = 1, .startOffset = 29.0f, .ySpacing = 0.0f, .frictionDamping = 0.9f, .floor = NULL, .floorSurfaceType = SURFACE_NONE },
};

Model *main_ARCHETYPE_HOLDABLE_ANIM_Models[1] = {
    &dande_model,
};

AnimState main_ARCHETYPE_HOLDABLE_ANIM_AnimStates[1] = {
    { .anim = &dandelion_anim_dande_idle, .counter = 0, .speed = 1 << ANIM_COUNTER_SHIFT, .triggerIndex = 0},
};

GravityParams main_ARCHETYPE_HOLDABLE_ANIM_Gravities[1] = {
    { .accel = -1.0f, .terminalVelocity = -30.0f },
};

HoldState main_ARCHETYPE_HOLDABLE_ANIM_HoldStates[1] = {
    { .holder = NULL, .type = HoldType_Glide },
};

ResizeParams main_ARCHETYPE_HOLDABLE_ANIM_ResizeParams[1] = {
    { .curSize = Size_Shrunk, .growAllowed = 1, .shrinkAllowed = 1, .resizeTimer = 0, .type = ResizeType_Grow_While_Held, .smallScale = 1.0f, .largeScale = 4.0f, .callback = NULL },
};

float main_ARCHETYPE_HOLDABLE_ANIM_Scales[1] = {
    1.0f,
};

// Bit_Position | Bit_Velocity | Bit_Collider | Bit_Rotation | Bit_Model | Bit_AnimState | Bit_Gravity | Bit_Holdable | Bit_Resizable | Bit_Scale
void *main_ARCHETYPE_HOLDABLE_ANIM_ComponentData[NUM_COMPONENTS(ARCHETYPE_HOLDABLE_ANIM)] = {
    main_ARCHETYPE_HOLDABLE_ANIM_Positions, // pos
    NULL, // velocity
    main_ARCHETYPE_HOLDABLE_ANIM_Colliders, // collider
    NULL, // rotation
    main_ARCHETYPE_HOLDABLE_ANIM_Models, // model
    main_ARCHETYPE_HOLDABLE_ANIM_AnimStates, // animstate
    main_ARCHETYPE_HOLDABLE_ANIM_Gravities, // gravity
    main_ARCHETYPE_HOLDABLE_ANIM_HoldStates, // holdable
    main_ARCHETYPE_HOLDABLE_ANIM_ResizeParams, // resizable
    main_ARCHETYPE_HOLDABLE_ANIM_Scales, // scale
};

archetype_t mainArchetypes[3] = {
    ARCHETYPE_MODEL,
    ARCHETYPE_STATIC_COL,
    ARCHETYPE_HOLDABLE_ANIM,
};

int mainArchetypeCounts[3] = {
    1,
    1,
    1,
};

void **mainComponentData[3] = {
    main_ARCHETYPE_MODEL_ComponentData,
    main_ARCHETYPE_STATIC_COL_ComponentData,
    main_ARCHETYPE_HOLDABLE_ANIM_ComponentData,
};

LevelHeader mainHeader = {
    3, // archetype count
    mainArchetypes, // archetypes
    mainArchetypeCounts, // archetype counts
    mainComponentData, // archetype component data
};
