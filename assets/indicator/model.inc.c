
Gfx indicator_model_test_tex_i8_aligner[] = {gsSPEndDisplayList()};
u8 indicator_model_test_tex_i8[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xC0, 0xC0, 0xC0, 0x77, 0x77, 0x77, 0x77, 
};


Gfx mat_indicator_model_f3d_material[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, 1, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, 1),
	gsSPSetGeometryMode(G_TEXTURE_GEN),
	gsSPClearGeometryMode(G_SHADE | G_LIGHTING),
	gsDPSetTextureFilter(G_TF_POINT),
	gsSPTexture(959, 0, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 16, indicator_model_test_tex_i8),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 2, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 60, 0),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 2, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 0),
	gsDPSetEnvColor(254, 0, 0, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_indicator_model_f3d_material[] = {
	gsDPPipeSync(),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsSPSetGeometryMode(G_SHADE | G_LIGHTING),
	gsDPSetTextureFilter(G_TF_BILERP),
	gsSPEndDisplayList(),
};



Vtx indicator_model_Cube_mesh_vtx_cull[8] = {
	{{{-50, 0, -10},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-50, 0, 10},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-50, 50, 10},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-50, 50, -10},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{50, 0, -10},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{50, 0, 10},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{50, 50, 10},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{50, 50, -10},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
};

Vtx indicator_model_Cube_mesh_vtx_0[12] = {
	{{{0, 0, -10},0, {192, 32},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-50, 50, -10},0, {320, 32},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{50, 50, -10},0, {320, 24},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{50, 50, 10},0, {320, 16},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{50, 50, -10},0, {448, 16},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-50, 50, -10},0, {448, 8},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-50, 50, 10},0, {320, 8},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, 0, 10},0, {192, 16},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, 0, -10},0, {192, 24},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, 0, 10},0, {192, 8},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-50, 50, -10},0, {320, 0},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, 0, -10},0, {192, 0},{0xFF, 0xFF, 0xFF, 0xFF}}},
};

Gfx indicator_model_Cube_mesh_tri_0[] = {
	gsSPVertex(indicator_model_Cube_mesh_vtx_0 + 0, 12, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(3, 5, 6, 0, 7, 3, 6, 0),
	gsSP2Triangles(8, 3, 7, 0, 8, 2, 3, 0),
	gsSP2Triangles(9, 6, 10, 0, 9, 10, 11, 0),
	gsSPEndDisplayList(),
};

Gfx indicator_model_Cube_mesh[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(indicator_model_Cube_mesh_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_indicator_model_f3d_material),
	gsSPDisplayList(indicator_model_Cube_mesh_tri_0),
	gsSPDisplayList(mat_revert_indicator_model_f3d_material),
	gsSPEndDisplayList(),
};




BoneLayer indicator_model_bone0_layers[] = {
    {
        0,
        indicator_model_Cube_mesh,
    },
};

Bone indicator_model_bones[] = {
    {
        0,
        255,
        1,
        0,
        0.0,
        0.0,
        0.0,
        indicator_model_bone0_layers,
        NULL,
        NULL,
        NULL,
    },
};

Model indicator_model = {
    1,
    0,
    indicator_model_bones
};

