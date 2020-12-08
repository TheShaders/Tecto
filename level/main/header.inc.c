extern Model main_model;
extern BVHTree main_collision_tree;

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

archetype_t mainArchetypes[2] = {
    ARCHETYPE_MODEL,
    ARCHETYPE_STATIC_COL,
};

int mainArchetypeCounts[2] = {
    1,
    1,
};

void **mainComponentData[2] = {
    main_ARCHETYPE_MODEL_ComponentData,
    main_ARCHETYPE_STATIC_COL_ComponentData,
};

LevelHeader mainHeader = {
    2, // archetype count
    mainArchetypes, // archetypes
    mainArchetypeCounts, // archetype counts
    mainComponentData, // archetype component data
};
