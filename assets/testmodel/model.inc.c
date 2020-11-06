extern Gfx* gfxSetEnvColor(Bone*, BoneLayer*);

Vtx cube_Cube_mesh_vtx_0[24] = {
	{{{10, 10, -10},0, {624, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-10, 10, -10},0, {880, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-10, 10, 10},0, {880, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{10, 10, 10},0, {624, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{10, -10, 10},0, {368, 240},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{10, 10, 10},0, {624, 240},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-10, 10, 10},0, {624, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-10, -10, 10},0, {368, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-10, -10, 10},0, {368, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-10, 10, 10},0, {624, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-10, 10, -10},0, {624, 752},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-10, -10, -10},0, {368, 752},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-10, -10, -10},0, {112, 496},{0x0, 0x81, 0x0, 0xFF}}},
	{{{10, -10, -10},0, {368, 496},{0x0, 0x81, 0x0, 0xFF}}},
	{{{10, -10, 10},0, {368, 240},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-10, -10, 10},0, {112, 240},{0x0, 0x81, 0x0, 0xFF}}},
	{{{10, -10, -10},0, {368, 496},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{10, 10, -10},0, {624, 496},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{10, 10, 10},0, {624, 240},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{10, -10, 10},0, {368, 240},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{-10, -10, -10},0, {368, 752},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-10, 10, -10},0, {624, 752},{0x0, 0x0, 0x81, 0xFF}}},
	{{{10, 10, -10},0, {624, 496},{0x0, 0x0, 0x81, 0xFF}}},
	{{{10, -10, -10},0, {368, 496},{0x0, 0x0, 0x81, 0xFF}}},
};

Gfx testmodelBone0LayerOpa[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(ENVIRONMENT, 0, SHADE, 0, 0, 0, 0, 1, ENVIRONMENT, 0, SHADE, 0, 0, 0, 0, 1),
    gsSPSetGeometryMode(G_LIGHTING),

	gsSPVertex(cube_Cube_mesh_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(cube_Cube_mesh_vtx_0 + 16, 8, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),

    gsSPClearGeometryMode(G_LIGHTING),
	gsSPEndDisplayList(),
};

BoneLayer testmodelBone0Layers[] = {
    {
        LAYER_OPA_SURF, // layer
        testmodelBone0LayerOpa, // displaylist
    }
};

Bone testmodelBones[] = {
    {
        0, // index
        0xFF, // parent
        1, // number of layers
        0, // reserved
        testmodelBone0Layers,
        gfxSetEnvColor, // beforeCb
        NULL, // afterCb
        NULL, // matrix pointer, used at runtime
    },
    {
        1, // index
        0, // parent
        1, // number of layers
        0, // reserved
        testmodelBone0Layers,
        gfxSetEnvColor, // beforeCb
        NULL, // afterCb
        NULL, // matrix pointer, used at runtime
    }
};

Model testmodel = {
    2, // numBones
    0, // reserved
    testmodelBones,
};
