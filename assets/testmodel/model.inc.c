extern Gfx* gfxSetEnvColor(Bone*, BoneLayer*);

Vtx cube_Cube_mesh_vtx_0[24] = {
	{{{ 10,  10, -10},0, {624, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-10,  10, -10},0, {880, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-10,  10,  10},0, {880, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{ 10,  10,  10},0, {624, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{ 10, -10,  10},0, {368, 240},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{ 10,  10,  10},0, {624, 240},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-10,  10,  10},0, {624, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-10, -10,  10},0, {368, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-10, -10,  10},0, {368, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-10,  10,  10},0, {624, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-10,  10, -10},0, {624, 752},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-10, -10, -10},0, {368, 752},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-10, -10, -10},0, {112, 496},{0x0, 0x81, 0x0, 0xFF}}},
	{{{ 10, -10, -10},0, {368, 496},{0x0, 0x81, 0x0, 0xFF}}},
	{{{ 10, -10,  10},0, {368, 240},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-10, -10,  10},0, {112, 240},{0x0, 0x81, 0x0, 0xFF}}},
	{{{ 10, -10, -10},0, {368, 496},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{ 10,  10, -10},0, {624, 496},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{ 10,  10,  10},0, {624, 240},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{ 10, -10,  10},0, {368, 240},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{-10, -10, -10},0, {368, 752},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-10,  10, -10},0, {624, 752},{0x0, 0x0, 0x81, 0xFF}}},
	{{{ 10,  10, -10},0, {624, 496},{0x0, 0x0, 0x81, 0xFF}}},
	{{{ 10, -10, -10},0, {368, 496},{0x0, 0x0, 0x81, 0xFF}}},
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

s16 testmodelBone0Tables[] = {
    16384,17241,18096,18946,19790,20624,21446,22255,23047,23821,24575,25307,26013,26694,27346,27968,
    28559,29116,29638,30124,30572,30981,31351,31679,31965,32209,32409,32565,32677,32745,32767,32745,
    32677,32565,32409,32209,31965,31679,31351,30981,30572,30124,29638,29116,28559,27968,27346,26694,
    26013,25307,24575,23821,23047,22255,21446,20624,19790,18946,18096,17241,16384,15526,14671,13821,
    12977,12143,11321,10512,9720,8946,8192,7460,6754,6073,5421,4799,4208,3651,3129,2643,
    2195,1786,1416,1088,802,558,358,202,90,22,0,22,90,202,358,558,
    802,1088,1416,1786,2195,2643,3129,3651,4208,4799,5421,6073,6754,7460,8192,8946,
    9720,10512,11321,12143,12977,13821,14671,15526,16384,
};

s16 testmodelBone1Tables[] = {
    1000,1052,1105,1156,1208,1259,1309,1358,1407,1454,1500,1545,1588,1629,1669,1707,
    1743,1777,1809,1839,1866,1891,1914,1934,1951,1966,1978,1988,1995,1999,2000,1999,
    1995,1988,1978,1966,1951,1934,1914,1891,1866,1839,1809,1777,1743,1707,1669,1629,
    1588,1545,1500,1454,1407,1358,1309,1259,1208,1156,1105,1052,1000,948,895,844,
    792,741,691,642,593,546,500,455,412,371,331,293,257,223,191,161,
    134,109,86,66,49,34,22,12,5,1,0,1,5,12,22,34,
    49,66,86,109,134,161,191,223,257,293,331,371,412,455,500,546,
    593,642,691,741,792,844,895,948,1000,
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
        0.0f, // x
        0.0f, // y
        0.0f, // z
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
        0.0f, // x
        30.0f, // y
        0.0f, // z
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

BoneTable testmodelBoneTables[] = {
    {
        CHANNEL_ROT_Z,
        testmodelBone0Tables,
    },
    {
        CHANNEL_POS_Y,
        testmodelBone1Tables
    },
};

Animation testmodelAnim = {
    16, // frame count
    2, // bone count
    ANIM_LOOP, // flags
    testmodelBoneTables, // bone table array pointer
    NULL // trigger array pointer
};
