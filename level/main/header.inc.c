extern Model main_model;
extern Model logo_model;
extern Model dande_model;
extern Model treevineleaf_model;
extern Model lilypad_model;
extern Model bounceflower_model;
extern BVHTree main_collision_tree;
extern Animation dandelion_anim_dande_idle;
extern Animation treevineleaf_anim_tvleaf_grow;
extern Animation lilypad_anim_lilypad_Idle;

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

Vec3 main_ARCHETYPE_HOLDABLE_COL_Positions[1] = {
    {-4720.0f, 32.4f, -2630.0f},
};

ColliderParams main_ARCHETYPE_HOLDABLE_COL_Colliders[1] = {
    { .radius = 58.0f, .numHeights = 1, .startOffset = 29.0f, .ySpacing = 0.0f, .frictionDamping = 0.9f, .floor = NULL, .floorSurfaceType = SURFACE_NONE },
};

Model *main_ARCHETYPE_HOLDABLE_COL_Models[1] = {
    &logo_model,
};

GravityParams main_ARCHETYPE_HOLDABLE_COL_Gravities[1] = {
    { .accel = -1.0f, .terminalVelocity = -30.0f },
};

HoldState main_ARCHETYPE_HOLDABLE_COL_HoldStates[1] = {
    { .holder = NULL, .type = HoldType_Normal },
};

extern void setLogoCollision();

ResizeParams main_ARCHETYPE_HOLDABLE_COL_ResizeParams[1] = {
    { .curSize = Size_Grown, .growTemporary = 0, .grownTime = 0, .resizeTimer = 0, .type = ResizeType_Shrink_While_Held, .smallScale = 1.0f, .largeScale = 3.0f, .callback = setLogoCollision },
};

float main_ARCHETYPE_HOLDABLE_COL_Scales[1] = {
    1.0f,
};

// Bit_Position | Bit_Velocity | Bit_Collision | Bit_Collider | Bit_Rotation | Bit_Model | Bit_Gravity | Bit_Holdable | Bit_Resizable | Bit_Scale
void *main_ARCHETYPE_HOLDABLE_COL_ComponentData[NUM_COMPONENTS(ARCHETYPE_HOLDABLE_COL)] = {
    main_ARCHETYPE_HOLDABLE_COL_Positions, // pos
    NULL, // velocity
    NULL, // collision
    main_ARCHETYPE_HOLDABLE_COL_Colliders, // collider
    NULL, // rotation
    main_ARCHETYPE_HOLDABLE_COL_Models, // model
    main_ARCHETYPE_HOLDABLE_COL_Gravities, // gravity
    main_ARCHETYPE_HOLDABLE_COL_HoldStates, // holdable
    main_ARCHETYPE_HOLDABLE_COL_ResizeParams, // resizable
    main_ARCHETYPE_HOLDABLE_COL_Scales, // scale
};

Vec3 main_ARCHETYPE_HOLDABLE_ANIM_Positions[1] = {
    {-4642.0f, 264.0f, -3986.0f},
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
    { .curSize = Size_Shrunk, .growTemporary = 0, .grownTime = 0, .resizeTimer = 0, .type = ResizeType_Grow_While_Held, .smallScale = 1.0f, .largeScale = 4.0f, .callback = NULL },
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

Vec3 main_ARCHETYPE_INTERACTABLE_Positions[6] = {
    {-4108.0f, -22.4f, -1796.8f},
    {-3356.0f, 407.0f, -4956.0f},
    {-2998.0f, 407.0f, -5140.0f},
    {-3012.0f, 407.0f, -5520.0f},
    {-5312.0f, -14.6f, -3660.0f},
    {-3604.0f, 171.8f, -3970.0f},
};

Vec3s main_ARCHETYPE_INTERACTABLE_Rotations[6] = {
    {0x0000, 0x727D, 0x0000},
    {0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000},
};

Model *main_ARCHETYPE_INTERACTABLE_Models[6] = {
    &treevineleaf_model,
    &lilypad_model,
    &lilypad_model,
    &lilypad_model,
    &bounceflower_model,
    &bounceflower_model,
};

AnimState main_ARCHETYPE_INTERACTABLE_AnimStates[6] = {
    { .anim = &treevineleaf_anim_tvleaf_grow, .counter = 0, .speed = 0 << ANIM_COUNTER_SHIFT, .triggerIndex = 0},
    { .anim = &lilypad_anim_lilypad_Idle, .counter = 0, .speed = 1 << ANIM_COUNTER_SHIFT, .triggerIndex = 0},
    { .anim = &lilypad_anim_lilypad_Idle, .counter = 0, .speed = 1 << ANIM_COUNTER_SHIFT, .triggerIndex = 0},
    { .anim = &lilypad_anim_lilypad_Idle, .counter = 0, .speed = 1 << ANIM_COUNTER_SHIFT, .triggerIndex = 0},
    { .anim = NULL, .counter = 0, .speed = 1 << ANIM_COUNTER_SHIFT, .triggerIndex = 0},
    { .anim = NULL, .counter = 0, .speed = 1 << ANIM_COUNTER_SHIFT, .triggerIndex = 0},
};

extern void treevineleafResizeCallback();
extern void lillypadResizeCallback();
extern void bounceflowerResizeCallback();

ResizeParams main_ARCHETYPE_INTERACTABLE_ResizeParams[6] = {
    { .curSize = Size_Shrunk, .growTemporary = 1, .grownTime = 255, .growAllowed = 1, .shrinkAllowed = 0, .horizontalIndicator = 1, .resizeTimer = 0, .type = ResizeType_Interactable, .smallScale = 1.0f, .largeScale = 1.0f, .callback = treevineleafResizeCallback },
    { .curSize = Size_Shrunk, .growTemporary = 1, .grownTime = 150, .growAllowed = 1, .shrinkAllowed = 0, .horizontalIndicator = 0, .resizeTimer = 0, .type = ResizeType_Interactable, .smallScale = 1.0f, .largeScale = 9.4f, .callback = lillypadResizeCallback },
    { .curSize = Size_Shrunk, .growTemporary = 1, .grownTime = 150, .growAllowed = 1, .shrinkAllowed = 0, .horizontalIndicator = 0, .resizeTimer = 0, .type = ResizeType_Interactable, .smallScale = 1.0f, .largeScale = 9.4f, .callback = lillypadResizeCallback },
    { .curSize = Size_Shrunk, .growTemporary = 1, .grownTime = 150, .growAllowed = 1, .shrinkAllowed = 0, .horizontalIndicator = 0, .resizeTimer = 0, .type = ResizeType_Interactable, .smallScale = 1.0f, .largeScale = 9.4f, .callback = lillypadResizeCallback },
    { .curSize = Size_Shrunk, .growTemporary = 1, .grownTime = 150, .growAllowed = 1, .shrinkAllowed = 0, .horizontalIndicator = 0, .resizeTimer = 0, .type = ResizeType_Interactable, .smallScale = 1.0f, .largeScale = 4.0f, .callback = bounceflowerResizeCallback },
    { .curSize = Size_Shrunk, .growTemporary = 1, .grownTime = 150, .growAllowed = 1, .shrinkAllowed = 0, .horizontalIndicator = 0, .resizeTimer = 0, .type = ResizeType_Interactable, .smallScale = 1.0f, .largeScale = 4.0f, .callback = bounceflowerResizeCallback },
};

float main_ARCHETYPE_INTERACTABLE_Scales[6] = {
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
};

// Bit_Position | Bit_Collision | Bit_Rotation | Bit_Model | Bit_AnimState | Bit_Resizable | Bit_Scale
void *main_ARCHETYPE_INTERACTABLE_ComponentData[NUM_COMPONENTS(ARCHETYPE_INTERACTABLE)] = {
    main_ARCHETYPE_INTERACTABLE_Positions, // pos
    NULL, // collision
    main_ARCHETYPE_INTERACTABLE_Rotations, // rotation
    main_ARCHETYPE_INTERACTABLE_Models, // model
    main_ARCHETYPE_INTERACTABLE_AnimStates, // animstate
    main_ARCHETYPE_INTERACTABLE_ResizeParams, // resizable
    main_ARCHETYPE_INTERACTABLE_Scales, // scale
};

archetype_t mainArchetypes[5] = {
    ARCHETYPE_MODEL,
    ARCHETYPE_STATIC_COL,
    ARCHETYPE_HOLDABLE_COL,
    ARCHETYPE_HOLDABLE_ANIM,
    ARCHETYPE_INTERACTABLE
};

int mainArchetypeCounts[5] = {
    1,
    1,
    1,
    1,
    6,
};

void **mainComponentData[5] = {
    main_ARCHETYPE_MODEL_ComponentData,
    main_ARCHETYPE_STATIC_COL_ComponentData,
    main_ARCHETYPE_HOLDABLE_COL_ComponentData,
    main_ARCHETYPE_HOLDABLE_ANIM_ComponentData,
    main_ARCHETYPE_INTERACTABLE_ComponentData,
};

LevelHeader mainHeader = {
    5, // archetype count
    mainArchetypes, // archetypes
    mainArchetypeCounts, // archetype counts
    mainComponentData, // archetype component data
};
