Gfx character_model_shading_i4_aligner[] = {gsSPEndDisplayList()};
u8 character_model_shading_i4[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xBB, 0x77, 0x77, 
};

Gfx character_model_eyecut_I4_i8_aligner[] = {gsSPEndDisplayList()};
u8 character_model_eyecut_I4_i8[] = {
	0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0xFF, 0xFF, 0x0, 
	0x0, 0x0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0, 0x0, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 
};

Gfx character_model_gem_env_rgba16_ci4_aligner[] = {gsSPEndDisplayList()};
u8 character_model_gem_env_rgba16_ci4[] = {
	0x1, 0x23, 0x45, 0x60, 
};

Gfx character_model_gem_env_rgba16_ci4_pal_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 character_model_gem_env_rgba16_ci4_pal_rgba16[] = {
	0xF2, 0xDB, 0xC2, 0xE5, 0xAB, 0xBD, 0xC5, 0x3D, 0xEE, 
	0xB7, 0xF6, 0x29, 0xF5, 0x1D, 
};


Gfx mat_character_model_base_toon_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, ENVIRONMENT, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, ENVIRONMENT),
	gsSPSetGeometryMode(G_TEXTURE_GEN),
	gsDPSetTextureFilter(G_TF_POINT),
	gsSPTexture(959, 0, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 8, character_model_shading_i4),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 30, 0),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 0),
	gsDPSetPrimColor(0, 0, 227, 222, 211, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_character_model_base_toon_f3d[] = {
	gsDPPipeSync(),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetTextureFilter(G_TF_BILERP),
	gsSPEndDisplayList(),
};


Gfx mat_character_model_shroom_placeholder_1_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 1, 0, 0, 0, PRIMITIVE, 0, 0, 0, 1),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 254, 175, 0, 255),
	gsSPEndDisplayList(),
};


Gfx mat_character_model_shroom_placeholder_2_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 1, 0, 0, 0, PRIMITIVE, 0, 0, 0, 1),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 233, 66, 63, 255),
	gsSPEndDisplayList(),
};


Gfx mat_character_model_eye_decal_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, 0, 0, 0, 0, TEXEL0, 0, 0, 0, 0, 0, 0, 0, TEXEL0),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 8, character_model_eyecut_I4_i8),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_WRAP | G_TX_MIRROR, 4, 0, G_TX_WRAP | G_TX_MIRROR, 3, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 28, 60),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 0, 0, G_TX_WRAP | G_TX_MIRROR, 4, 0, G_TX_WRAP | G_TX_MIRROR, 3, 0),
	gsDPSetTileSize(0, 0, 0, 28, 60),
	gsSPEndDisplayList(),
};


Gfx mat_character_model_t_env_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, PRIMITIVE, SHADE_ALPHA, PRIMITIVE, 0, 0, 0, ENVIRONMENT, TEXEL0, PRIMITIVE, SHADE_ALPHA, PRIMITIVE, 0, 0, 0, ENVIRONMENT),
	gsSPSetGeometryMode(G_TEXTURE_GEN),
	gsSPTexture(447, 0, 0, 0, 1),
	gsDPSetTextureLUT(G_TT_RGBA16),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, character_model_gem_env_rgba16_ci4_pal_rgba16),
	gsDPTileSync(),
	gsDPSetTile(0, 0, 0, 256, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTLUTCmd(7, 6),
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b, 4, character_model_gem_env_rgba16_ci4),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 14, 0),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, 0),
	gsDPSetTileSize(0, 0, 0, 28, 0),
	gsDPSetPrimColor(0, 0, 254, 89, 91, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_character_model_t_env_f3d[] = {
	gsDPPipeSync(),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetTextureLUT(G_TT_NONE),
	gsSPEndDisplayList(),
};



Vtx character_Foot_L_mesh_vtx_0[17] = {
	{{{-10, 18, 22},0, {320, 32},{0xC3, 0x43, 0x59, 0xFF}}},
	{{{10, 0, 27},0, {192, 32},{0x3F, 0xCA, 0x60, 0xFF}}},
	{{{11, 25, 7},0, {320, 32},{0x59, 0x5A, 0x10, 0xFF}}},
	{{{13, 0, 8},0, {192, 24},{0x63, 0xB2, 0xF3, 0xFF}}},
	{{{3, 25, -11},0, {320, 24},{0x2F, 0x51, 0xAB, 0xFF}}},
	{{{2, 0, -15},0, {192, 16},{0x27, 0xBC, 0x9C, 0xFF}}},
	{{{-16, 25, -6},0, {320, 16},{0xA5, 0x50, 0xDB, 0xFF}}},
	{{{-20, 0, -8},0, {192, 12},{0x9F, 0xC1, 0xCC, 0xFF}}},
	{{{10, 0, 27},0, {64, 8},{0x3F, 0xCA, 0x60, 0xFF}}},
	{{{13, 0, 8},0, {64, 16},{0x63, 0xB2, 0xF3, 0xFF}}},
	{{{-12, 0, 21},0, {192, 8},{0xB6, 0xB5, 0x46, 0xFF}}},
	{{{-10, 18, 22},0, {320, 8},{0xC3, 0x43, 0x59, 0xFF}}},
	{{{10, 0, 27},0, {192, 0},{0x3F, 0xCA, 0x60, 0xFF}}},
	{{{-10, 25, 7},0, {320, 8},{0xC2, 0x6A, 0x20, 0xFF}}},
	{{{11, 25, 7},0, {448, 8},{0x59, 0x5A, 0x10, 0xFF}}},
	{{{-10, 18, 22},0, {448, 8},{0xC3, 0x43, 0x59, 0xFF}}},
	{{{3, 25, -11},0, {448, 16},{0x2F, 0x51, 0xAB, 0xFF}}},
};

Gfx character_Foot_L_mesh_tri_0[] = {
	gsSPVertex(character_Foot_L_mesh_vtx_0 + 0, 17, 0),
	gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
	gsSP2Triangles(2, 3, 4, 0, 4, 3, 5, 0),
	gsSP2Triangles(4, 5, 6, 0, 6, 5, 7, 0),
	gsSP2Triangles(8, 7, 5, 0, 5, 9, 8, 0),
	gsSP2Triangles(8, 10, 7, 0, 10, 11, 7, 0),
	gsSP2Triangles(10, 12, 11, 0, 7, 11, 13, 0),
	gsSP2Triangles(6, 7, 13, 0, 6, 13, 14, 0),
	gsSP2Triangles(13, 15, 14, 0, 6, 14, 16, 0),
	gsSPEndDisplayList(),
};

Gfx character_Foot_L_mesh[] = {
	gsSPDisplayList(mat_character_model_base_toon_f3d),
	gsSPDisplayList(character_Foot_L_mesh_tri_0),
	gsSPDisplayList(mat_revert_character_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx character_Foot_R_mesh_vtx_0[18] = {
	{{{6, 25, -21},0, {320, 16},{0xA, 0x46, 0x97, 0xFF}}},
	{{{12, 25, 12},0, {448, 8},{0x3F, 0x5F, 0x37, 0xFF}}},
	{{{14, 25, -7},0, {448, 16},{0x5B, 0x56, 0xEC, 0xFF}}},
	{{{-8, 25, -2},0, {320, 8},{0xB7, 0x66, 0xEE, 0xFF}}},
	{{{-11, 0, -9},0, {192, 12},{0xB2, 0xB7, 0xBA, 0xFF}}},
	{{{13, 0, -15},0, {192, 16},{0x40, 0xB1, 0xB5, 0xFF}}},
	{{{14, 25, -7},0, {320, 24},{0x5B, 0x56, 0xEC, 0xFF}}},
	{{{17, 0, 9},0, {192, 24},{0x62, 0xB5, 0x1E, 0xFF}}},
	{{{12, 25, 12},0, {320, 32},{0x3F, 0x5F, 0x37, 0xFF}}},
	{{{5, 18, 21},0, {320, 32},{0x15, 0x42, 0x6A, 0xFF}}},
	{{{-1, 0, 28},0, {192, 32},{0xFC, 0xC8, 0x72, 0xFF}}},
	{{{-1, 0, 28},0, {64, 8},{0xFC, 0xC8, 0x72, 0xFF}}},
	{{{-20, 0, 14},0, {192, 8},{0x95, 0xC9, 0x29, 0xFF}}},
	{{{-14, 18, 7},0, {320, 8},{0x9C, 0x4B, 0x16, 0xFF}}},
	{{{5, 18, 21},0, {320, 0},{0x15, 0x42, 0x6A, 0xFF}}},
	{{{-1, 0, 28},0, {192, 0},{0xFC, 0xC8, 0x72, 0xFF}}},
	{{{5, 18, 21},0, {448, 8},{0x15, 0x42, 0x6A, 0xFF}}},
	{{{17, 0, 9},0, {64, 16},{0x62, 0xB5, 0x1E, 0xFF}}},
};

Gfx character_Foot_R_mesh_tri_0[] = {
	gsSPVertex(character_Foot_R_mesh_vtx_0 + 0, 18, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(0, 4, 3, 0, 0, 5, 4, 0),
	gsSP2Triangles(6, 5, 0, 0, 6, 7, 5, 0),
	gsSP2Triangles(8, 7, 6, 0, 8, 9, 7, 0),
	gsSP2Triangles(7, 9, 10, 0, 11, 4, 5, 0),
	gsSP2Triangles(11, 12, 4, 0, 12, 13, 4, 0),
	gsSP2Triangles(12, 14, 13, 0, 12, 15, 14, 0),
	gsSP2Triangles(4, 13, 3, 0, 3, 13, 16, 0),
	gsSP2Triangles(3, 16, 1, 0, 5, 17, 11, 0),
	gsSPEndDisplayList(),
};

Gfx character_Foot_R_mesh[] = {
	gsSPDisplayList(mat_character_model_base_toon_f3d),
	gsSPDisplayList(character_Foot_R_mesh_tri_0),
	gsSPDisplayList(mat_revert_character_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx character_Head_mesh_vtx_0[19] = {
	{{{-20, -15, -23},0, {64, 16},{0xD9, 0xAF, 0xA7, 0xFF}}},
	{{{-26, -15, 16},0, {64, 8},{0xCD, 0xAA, 0x4F, 0xFF}}},
	{{{-43, 6, 5},0, {64, 16},{0x82, 0x1, 0x10, 0xFF}}},
	{{{32, -15, 16},0, {192, 8},{0x37, 0xAF, 0x50, 0xFF}}},
	{{{34, -15, -5},0, {192, 16},{0x4D, 0xA8, 0xCD, 0xFF}}},
	{{{38, 12, 16},0, {320, 8},{0x56, 0x29, 0x54, 0xFF}}},
	{{{42, 5, -10},0, {320, 16},{0x68, 0x16, 0xBB, 0xFF}}},
	{{{-20, -15, -23},0, {192, 24},{0xD9, 0xAF, 0xA7, 0xFF}}},
	{{{-20, 25, -23},0, {320, 24},{0xD9, 0x47, 0x9E, 0xFF}}},
	{{{-43, 6, 5},0, {320, 24},{0x82, 0x1, 0x10, 0xFF}}},
	{{{-3, 32, -2},0, {320, 24},{0x13, 0x7E, 0xFC, 0xFF}}},
	{{{-26, 25, 16},0, {320, 32},{0xCC, 0x53, 0x52, 0xFF}}},
	{{{-43, 6, 5},0, {320, 32},{0x82, 0x1, 0x10, 0xFF}}},
	{{{30, 21, 2},0, {320, 16},{0x3A, 0x71, 0xFC, 0xFF}}},
	{{{-26, -15, 16},0, {192, 0},{0xCD, 0xAA, 0x4F, 0xFF}}},
	{{{-26, 25, 16},0, {320, 0},{0xCC, 0x53, 0x52, 0xFF}}},
	{{{-43, 6, 5},0, {192, 0},{0x82, 0x1, 0x10, 0xFF}}},
	{{{30, 21, 2},0, {320, 8},{0x3A, 0x71, 0xFC, 0xFF}}},
	{{{-3, 32, -2},0, {320, 0},{0x13, 0x7E, 0xFC, 0xFF}}},
};

Gfx character_Head_mesh_tri_0[] = {
	gsSPVertex(character_Head_mesh_vtx_0 + 0, 19, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(0, 4, 3, 0, 4, 5, 3, 0),
	gsSP2Triangles(4, 6, 5, 0, 7, 6, 4, 0),
	gsSP2Triangles(7, 8, 6, 0, 8, 7, 9, 0),
	gsSP2Triangles(6, 8, 10, 0, 8, 11, 10, 0),
	gsSP2Triangles(11, 8, 12, 0, 6, 10, 13, 0),
	gsSP2Triangles(14, 15, 16, 0, 3, 15, 14, 0),
	gsSP2Triangles(3, 5, 15, 0, 15, 5, 17, 0),
	gsSP2Triangles(5, 6, 17, 0, 15, 17, 18, 0),
	gsSPEndDisplayList(),
};Vtx character_Head_mesh_vtx_1[8] = {
	{{{0, 37, 2},0, {624, 1008},{0x40, 0x26, 0x67, 0xFF}}},
	{{{1, 37, -7},0, {624, 752},{0x57, 0x1B, 0xA8, 0xFF}}},
	{{{-12, 51, -3},0, {624, 1008},{0xBC, 0x6B, 0x5, 0xFF}}},
	{{{-3, 27, 4},0, {624, 1008},{0x22, 0x1B, 0x77, 0xFF}}},
	{{{-11, 28, -5},0, {624, 752},{0x8C, 0x2A, 0xE0, 0xFF}}},
	{{{-7, 36, -6},0, {624, 752},{0x8E, 0x8, 0xC9, 0xFF}}},
	{{{-12, 51, -3},0, {624, 752},{0xBC, 0x6B, 0x5, 0xFF}}},
	{{{-2, 27, -6},0, {624, 752},{0x4F, 0xE4, 0xA0, 0xFF}}},
};

Gfx character_Head_mesh_tri_1[] = {
	gsSPVertex(character_Head_mesh_vtx_1 + 0, 8, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
	gsSP2Triangles(4, 3, 0, 0, 4, 0, 5, 0),
	gsSP2Triangles(5, 0, 6, 0, 1, 5, 6, 0),
	gsSP2Triangles(7, 5, 1, 0, 3, 7, 1, 0),
	gsSP1Triangle(7, 4, 5, 0),
	gsSPEndDisplayList(),
};Vtx character_Head_mesh_vtx_2[7] = {
	{{{-5, 46, -20},0, {624, 752},{0xF9, 0x79, 0xD9, 0xFF}}},
	{{{-24, 41, -13},0, {624, 752},{0xB5, 0x66, 0xF9, 0xFF}}},
	{{{-12, 51, -3},0, {624, 752},{0xDE, 0x79, 0x15, 0xFF}}},
	{{{-19, 38, 5},0, {624, 863},{0xB8, 0x51, 0x41, 0xFF}}},
	{{{0, 43, 11},0, {624, 1008},{0xFB, 0x6C, 0x42, 0xFF}}},
	{{{7, 46, -4},0, {624, 885},{0x1F, 0x7B, 0xC, 0xFF}}},
	{{{-12, 51, -3},0, {624, 1008},{0xDE, 0x79, 0x15, 0xFF}}},
};

Gfx character_Head_mesh_tri_2[] = {
	gsSPVertex(character_Head_mesh_vtx_2 + 0, 7, 0),
	gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
	gsSP2Triangles(2, 3, 4, 0, 4, 5, 6, 0),
	gsSP1Triangle(6, 5, 0, 0),
	gsSPEndDisplayList(),
};

Gfx character_Head_mesh[] = {
	gsSPDisplayList(mat_character_model_base_toon_f3d),
	gsSPDisplayList(character_Head_mesh_tri_0),
	gsSPDisplayList(mat_revert_character_model_base_toon_f3d),
	gsSPDisplayList(mat_character_model_shroom_placeholder_1_f3d),
	gsSPDisplayList(character_Head_mesh_tri_1),
	gsSPDisplayList(mat_character_model_shroom_placeholder_2_f3d),
	gsSPDisplayList(character_Head_mesh_tri_2),
	gsSPEndDisplayList(),
};



Vtx character_Eye_L_mesh_vtx_0[4] = {
	{{{-3, -9, 0},0, {-16, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{3, -9, 0},0, {496, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{3, 9, 0},0, {496, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-3, 9, 0},0, {-16, -16},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx character_Eye_L_mesh_tri_0[] = {
	gsSPVertex(character_Eye_L_mesh_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx character_Eye_L_mesh[] = {
	gsSPDisplayList(mat_character_model_eye_decal_f3d),
	gsSPDisplayList(character_Eye_L_mesh_tri_0),
	gsSPEndDisplayList(),
};



Vtx character_Eye_R_mesh_vtx_0[4] = {
	{{{-3, -9, 0},0, {-16, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{4, -9, 0},0, {496, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{4, 9, 0},0, {496, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-3, 9, 0},0, {-16, -16},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx character_Eye_R_mesh_tri_0[] = {
	gsSPVertex(character_Eye_R_mesh_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx character_Eye_R_mesh[] = {
	gsSPDisplayList(mat_character_model_eye_decal_f3d),
	gsSPDisplayList(character_Eye_R_mesh_tri_0),
	gsSPEndDisplayList(),
};



Vtx character_Torso_mesh_vtx_0[21] = {
	{{{5, -2, -40},0, {64, 16},{0x1A, 0xFD, 0x84, 0xFF}}},
	{{{31, 11, -16},0, {0, 32},{0x62, 0x1F, 0xB6, 0xFF}}},
	{{{19, -23, -17},0, {64, 16},{0x3D, 0xA7, 0xBE, 0xFF}}},
	{{{0, 27, -18},0, {0, 32},{0xF8, 0x64, 0xB3, 0xFF}}},
	{{{-31, -4, -29},0, {64, 16},{0xA4, 0x8, 0xA9, 0xFF}}},
	{{{-23, -28, -23},0, {64, 8},{0xD1, 0x9D, 0xC0, 0xFF}}},
	{{{-12, -32, -7},0, {129, 8},{0xF9, 0x82, 0xF3, 0xFF}}},
	{{{19, -23, -17},0, {129, 8},{0x3D, 0xA7, 0xBE, 0xFF}}},
	{{{-33, -19, 9},0, {64, 8},{0x97, 0xBC, 0x16, 0xFF}}},
	{{{-34, 19, -5},0, {64, 16},{0x9A, 0x49, 0xEE, 0xFF}}},
	{{{-34, 0, 22},0, {64, 8},{0x9B, 0xC, 0x4C, 0xFF}}},
	{{{-16, -22, 26},0, {129, 8},{0xDE, 0xB1, 0x5D, 0xFF}}},
	{{{30, -25, 16},0, {192, 8},{0x4B, 0xA3, 0x2D, 0xFF}}},
	{{{19, -23, -17},0, {192, 8},{0x3D, 0xA7, 0xBE, 0xFF}}},
	{{{28, 2, 31},0, {192, 8},{0x48, 0x3, 0x68, 0xFF}}},
	{{{39, -6, 3},0, {192, 16},{0x7D, 0xEF, 0xF5, 0xFF}}},
	{{{19, -23, -17},0, {192, 16},{0x3D, 0xA7, 0xBE, 0xFF}}},
	{{{26, 37, 3},0, {192, 16},{0x48, 0x68, 0xF7, 0xFF}}},
	{{{19, -23, -17},0, {0, 32},{0x3D, 0xA7, 0xBE, 0xFF}}},
	{{{2, 38, 19},0, {192, 16},{0xEC, 0x78, 0x25, 0xFF}}},
	{{{2, 29, 32},0, {192, 8},{0xF7, 0x43, 0x6B, 0xFF}}},
};

Gfx character_Torso_mesh_tri_0[] = {
	gsSPVertex(character_Torso_mesh_vtx_0 + 0, 21, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
	gsSP2Triangles(3, 0, 4, 0, 4, 0, 5, 0),
	gsSP2Triangles(6, 5, 0, 0, 7, 6, 0, 0),
	gsSP2Triangles(8, 5, 6, 0, 4, 5, 8, 0),
	gsSP2Triangles(9, 4, 8, 0, 9, 8, 10, 0),
	gsSP2Triangles(11, 10, 8, 0, 8, 6, 11, 0),
	gsSP2Triangles(11, 6, 12, 0, 12, 6, 13, 0),
	gsSP2Triangles(11, 12, 14, 0, 14, 12, 15, 0),
	gsSP2Triangles(15, 12, 16, 0, 14, 15, 17, 0),
	gsSP2Triangles(17, 15, 1, 0, 1, 15, 18, 0),
	gsSP2Triangles(17, 1, 3, 0, 19, 17, 3, 0),
	gsSP2Triangles(3, 9, 19, 0, 3, 4, 9, 0),
	gsSP2Triangles(10, 19, 9, 0, 10, 20, 19, 0),
	gsSP2Triangles(11, 20, 10, 0, 20, 11, 14, 0),
	gsSP2Triangles(20, 14, 17, 0, 20, 17, 19, 0),
	gsSPEndDisplayList(),
};Vtx character_Torso_mesh_vtx_1[11] = {
	{{{-22, 8, 25},0, {16, -8},{0xB5, 0xFD, 0x66, 0xFF}}},
	{{{-5, -10, 28},0, {48, -8},{0xEA, 0xB5, 0x64, 0xFF}}},
	{{{-3, 4, 39},0, {16, -8},{0xEE, 0xE8, 0x7B, 0xFF}}},
	{{{16, 7, 31},0, {80, -8},{0x34, 0xF4, 0x73, 0xFF}}},
	{{{-3, 4, 39},0, {48, -8},{0xEE, 0xE8, 0x7B, 0xFF}}},
	{{{10, -7, 29},0, {80, -8},{0xB3, 0xFF, 0x65, 0x0}}},
	{{{8, 21, 31},0, {80, -8},{0x18, 0xC5, 0x6E, 0x0}}},
	{{{-3, 4, 39},0, {80, -8},{0xEE, 0xE8, 0x7B, 0xFF}}},
	{{{-27, -4, 24},0, {48, -8},{0x2F, 0x32, 0x6B, 0x0}}},
	{{{8, 21, 31},0, {16, -8},{0x18, 0xC5, 0x6E, 0x0}}},
	{{{-1, 25, 31},0, {80, -8},{0xF3, 0x2E, 0x76, 0x63}}},
};

Gfx character_Torso_mesh_tri_1[] = {
	gsSPVertex(character_Torso_mesh_vtx_1 + 0, 11, 0),
	gsSP2Triangles(0, 1, 2, 0, 1, 3, 4, 0),
	gsSP2Triangles(5, 6, 7, 0, 8, 5, 4, 0),
	gsSP2Triangles(9, 8, 2, 0, 10, 0, 7, 0),
	gsSP1Triangle(3, 10, 7, 0),
	gsSPEndDisplayList(),
};

Gfx character_Torso_mesh[] = {
	gsSPDisplayList(mat_character_model_base_toon_f3d),
	gsSPDisplayList(character_Torso_mesh_tri_0),
	gsSPDisplayList(mat_revert_character_model_base_toon_f3d),
	gsSPDisplayList(mat_character_model_t_env_f3d),
	gsSPDisplayList(character_Torso_mesh_tri_1),
	gsSPDisplayList(mat_revert_character_model_t_env_f3d),
	gsSPEndDisplayList(),
};




BoneLayer character_model_bone1_layers[] = {
    {
        0,
        character_Foot_L_mesh,
    },
};
BoneLayer character_model_bone2_layers[] = {
    {
        0,
        character_Foot_R_mesh,
    },
};
BoneLayer character_model_bone3_layers[] = {
    {
        0,
        character_Head_mesh,
    },
};
BoneLayer character_model_bone4_layers[] = {
    {
        4,
        character_Eye_L_mesh,
    },
};
BoneLayer character_model_bone5_layers[] = {
    {
        4,
        character_Eye_R_mesh,
    },
};
BoneLayer character_model_bone6_layers[] = {
    {
        0,
        character_Torso_mesh,
    },
};

Bone character_model_bones[] = {
    {
        0,
        255,
        0,
        0,
        0.0,
        0.0,
        0.0,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        1,
        0,
        1,
        0,
        31.315998077392578,
        0.16871929168701172,
        -9.308012522524223e-06,
        character_model_bone1_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        2,
        0,
        1,
        0,
        -31.315967559814453,
        0.16871929168701172,
        -9.308012522524223e-06,
        character_model_bone2_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        3,
        0,
        1,
        0,
        2.9500579833984375,
        127.73494720458984,
        3.6910223960876465,
        character_model_bone3_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        4,
        3,
        1,
        0,
        10.858016014099121,
        4.263944625854492,
        18.17925453186035,
        character_model_bone4_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        5,
        3,
        1,
        0,
        -12.478515625,
        7.585477828979492,
        18.177051544189453,
        character_model_bone5_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        6,
        0,
        1,
        0,
        0.0,
        68.54440307617188,
        -2.996170678670751e-06,
        character_model_bone6_layers,
        NULL,
        NULL,
        NULL,
    },
};

Model character_model = {
    7,
    0,
    character_model_bones
};

