
Gfx dande_model_fluff_i4_aligner[] = {gsSPEndDisplayList()};
u8 dande_model_fluff_i4[] = {
	
};


Gfx mat_dande_model_stem_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, SHADE_ALPHA, ENVIRONMENT, 0, 0, 0, 1, PRIMITIVE, ENVIRONMENT, SHADE_ALPHA, ENVIRONMENT, 0, 0, 0, 1),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 123, 187, 146, 255),
	gsDPSetEnvColor(113, 83, 49, 255),
	gsSPEndDisplayList(),
};


Gfx mat_dande_model_fuzz_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 44, dande_model_fluff_i4),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 6, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 7, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 174, 348),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 6, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 7, 0),
	gsDPSetTileSize(0, 0, 0, 348, 348),
	gsDPSetPrimColor(0, 0, 207, 207, 207, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_dande_model_fuzz_f3d[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};



Vtx dandelion_Root_mesh_vtx_0[11] = {
	{{{0, -28, -2},0, {308, 572},{0xFB, 0xB7, 0x98, 0xFF}}},
	{{{2, -28, 2},0, {368, 240},{0x57, 0xB7, 0x38, 0xFF}}},
	{{{-2, -28, 2},0, {112, 240},{0xA7, 0xBA, 0x39, 0xFF}}},
	{{{3, -8, 2},0, {496, 240},{0x6E, 0xFF, 0x3F, 0xB0}}},
	{{{1, -8, -3},0, {479, 599},{0xFF, 0xFF, 0x81, 0xFE}}},
	{{{-2, -8, 2},0, {496, -16},{0x95, 0x2, 0x44, 0xFF}}},
	{{{-2, -28, 2},0, {368, -16},{0xA7, 0xBA, 0x39, 0xFF}}},
	{{{-2, -28, 2},0, {368, 1008},{0xA7, 0xBA, 0x39, 0xFF}}},
	{{{1, -8, -3},0, {496, 632},{0xFF, 0xFF, 0x81, 0xFE}}},
	{{{0, -28, -2},0, {368, 632},{0xFB, 0xB7, 0x98, 0xFF}}},
	{{{-2, -8, 2},0, {496, 1008},{0x95, 0x2, 0x44, 0xFF}}},
};

Gfx dandelion_Root_mesh_tri_0[] = {
	gsSPVertex(dandelion_Root_mesh_vtx_0 + 0, 11, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(0, 4, 3, 0, 1, 3, 5, 0),
	gsSP2Triangles(1, 5, 6, 0, 7, 8, 9, 0),
	gsSP1Triangle(7, 10, 8, 0),
	gsSPEndDisplayList(),
};

Gfx dandelion_Root_mesh[] = {
	gsSPDisplayList(mat_dande_model_stem_f3d),
	gsSPDisplayList(dandelion_Root_mesh_tri_0),
	gsSPEndDisplayList(),
};



Vtx dandelion_Stem2_mesh_vtx_0[5] = {
	{{{-2, 18, 1},0, {566, -16},{0x9A, 0xF2, 0x4B, 0xFF}}},
	{{{2, 18, 2},0, {566, 240},{0x67, 0xFC, 0x4B, 0xFF}}},
	{{{0, 18, -2},0, {570, 587},{0x0, 0xF0, 0x82, 0xFF}}},
	{{{0, 18, -2},0, {566, 632},{0x0, 0xF0, 0x82, 0xFF}}},
	{{{-2, 18, 1},0, {566, 1008},{0x9A, 0xF2, 0x4B, 0xFF}}},
};

Gfx dandelion_Stem2_mesh_tri_0[] = {
	gsSPVertex(dandelion_Stem2_mesh_vtx_0 + 0, 5, 5),
	gsSP2Triangles(0, 5, 1, 0, 0, 6, 5, 0),
	gsSP2Triangles(3, 6, 0, 0, 3, 7, 6, 0),
	gsSP2Triangles(2, 8, 4, 0, 2, 9, 8, 0),
	gsSPEndDisplayList(),
};Vtx dandelion_Stem2_mesh_vtx_1[23] = {
	{{{-3, 12, 1},0, {566, 1008},{0x9A, 0xF0, 0x4A, 0xFF}}},
	{{{-5, 29, 3},0, {624, 1008},{0x9F, 0xE6, 0x4E, 0x0}}},
	{{{-5, 29, -3},0, {624, 752},{0xAE, 0xEB, 0xA1, 0x0}}},
	{{{-1, 13, -2},0, {566, 632},{0x1, 0xF0, 0x82, 0xFF}}},
	{{{0, 30, -3},0, {624, 496},{0x55, 0xF8, 0xA2, 0x0}}},
	{{{0, 13, 2},0, {566, 240},{0x66, 0xFE, 0x4C, 0xFF}}},
	{{{-5, 29, 3},0, {624, -16},{0x9F, 0xE6, 0x4E, 0x0}}},
	{{{-3, 12, 1},0, {566, -16},{0x9A, 0xF0, 0x4A, 0xFF}}},
	{{{0, 30, 3},0, {624, 240},{0x5F, 0xF4, 0x53, 0x0}}},
	{{{-1, 13, -2},0, {570, 587},{0x1, 0xF0, 0x82, 0xFF}}},
	{{{-2, 24, 0},0, {624, 752},{0x7, 0x81, 0x0, 0x0}}},
	{{{-12, 32, -4},0, {624, 752},{0x8D, 0xFF, 0xCB, 0x0}}},
	{{{2, 33, -10},0, {624, 496},{0x36, 0x8, 0x8D, 0x0}}},
	{{{-3, 39, 0},0, {624, 496},{0xF6, 0x7F, 0xFD, 0x0}}},
	{{{-2, 24, 0},0, {624, 496},{0x7, 0x81, 0x0, 0x0}}},
	{{{7, 33, 5},0, {624, 240},{0x73, 0xD, 0x35, 0x0}}},
	{{{-3, 39, 0},0, {624, 240},{0xF6, 0x7F, 0xFD, 0x0}}},
	{{{-2, 24, 0},0, {624, 1008},{0x7, 0x81, 0x0, 0x0}}},
	{{{-7, 33, 10},0, {624, 1008},{0xCC, 0x3, 0x74, 0x0}}},
	{{{-3, 39, 0},0, {624, 752},{0xF6, 0x7F, 0xFD, 0x0}}},
	{{{-2, 24, 0},0, {624, 240},{0x7, 0x81, 0x0, 0x0}}},
	{{{-7, 33, 10},0, {624, -16},{0xCC, 0x3, 0x74, 0x0}}},
	{{{-3, 39, 0},0, {624, -16},{0xF6, 0x7F, 0xFD, 0x0}}},
};

Gfx dandelion_Stem2_mesh_tri_1[] = {
	gsSPVertex(dandelion_Stem2_mesh_vtx_1 + 0, 23, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(3, 2, 4, 0, 5, 6, 7, 0),
	gsSP2Triangles(5, 8, 6, 0, 9, 8, 5, 0),
	gsSP2Triangles(9, 4, 8, 0, 10, 11, 12, 0),
	gsSP2Triangles(12, 11, 13, 0, 14, 12, 15, 0),
	gsSP2Triangles(15, 12, 16, 0, 17, 18, 11, 0),
	gsSP2Triangles(11, 18, 19, 0, 20, 15, 21, 0),
	gsSP1Triangle(21, 15, 22, 0),
	gsSPEndDisplayList(),
};
Vtx dandelion_Stem2_skinned_vtx_0[5] = {
	{{{3, -8, 2},0, {496, 240},{0x6D, 0x2, 0x41, 0xB0}}},
	{{{-1, -8, 2},0, {496, -16},{0x94, 0xFF, 0x43, 0xFF}}},
	{{{-1, -8, 2},0, {496, 1008},{0x94, 0xFF, 0x43, 0xFF}}},
	{{{1, -8, -3},0, {479, 599},{0x0, 0xFF, 0x81, 0xFE}}},
	{{{1, -8, -3},0, {496, 632},{0x0, 0xFF, 0x81, 0xFE}}},
};

Gfx dandelion_Stem2_skinned_tri_0[] = {
	gsSPVertex(dandelion_Stem2_skinned_vtx_0 + 0, 5, 0),
	gsSPEndDisplayList(),
};

Gfx dandelion_Stem2_mesh[] = {
	gsSPDisplayList(mat_dande_model_stem_f3d),
	gsSPDisplayList(dandelion_Stem2_mesh_tri_0),
	gsSPDisplayList(mat_dande_model_stem_f3d),
	gsSPDisplayList(dandelion_Stem2_mesh_tri_1),
	gsSPEndDisplayList(),
};


Gfx dandelion_Stem2_skinned[] = {
	gsSPDisplayList(mat_dande_model_stem_f3d),
	gsSPDisplayList(dandelion_Stem2_skinned_tri_0),
	gsSPEndDisplayList(),
};



Vtx dandelion_Billboard_mesh_vtx_0[4] = {
	{{{-16, -15, 12},0, {-16, 2800},{0x3, 0x0, 0x7F, 0xFF}}},
	{{{15, -17, 11},0, {2800, 2800},{0x3, 0x0, 0x7F, 0xFF}}},
	{{{17, 15, 11},0, {2800, -16},{0x3, 0x0, 0x7F, 0xFF}}},
	{{{-15, 17, 12},0, {-16, -16},{0x3, 0x0, 0x7F, 0xFF}}},
};

Gfx dandelion_Billboard_mesh_tri_0[] = {
	gsSPVertex(dandelion_Billboard_mesh_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx dandelion_Billboard_mesh[] = {
	gsSPDisplayList(mat_dande_model_fuzz_f3d),
	gsSPDisplayList(dandelion_Billboard_mesh_tri_0),
	gsSPDisplayList(mat_revert_dande_model_fuzz_f3d),
	gsSPEndDisplayList(),
};




BoneLayer dande_model_bone0_layers[] = {
    {
        1,
        dandelion_Root_mesh,
    },
};
BoneLayer dande_model_bone1_layers[] = {
    {
        1,
        dandelion_Stem2_mesh,
    },
};
BoneLayer dande_model_bone2_layers[] = {
    {
        5,
        dandelion_Billboard_mesh,
    },
};

Bone dande_model_bones[] = {
    {
        0,
        255,
        1,
        0,
        0.0,
        0.0,
        0.0,
        dande_model_bone0_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        1,
        0,
        1,
        0,
        0.8488005995750427,
        5.611042022705078,
        1.945889152921154e-06,
        dande_model_bone1_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        2,
        1,
        1,
        0,
        -0.8488006591796875,
        32.001976013183594,
        -3.5898867736250395e-06,
        dande_model_bone2_layers,
        NULL,
        NULL,
        NULL,
    },
};

Model dande_model = {
    3,
    0,
    dande_model_bones
};

