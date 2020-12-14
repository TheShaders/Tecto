Lights1 friendplayer_model_t_env_f3d_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);


Gfx friendplayer_model_shading_i4_aligner[] = {gsSPEndDisplayList()};
u8 friendplayer_model_shading_i4[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xBB, 0x77, 0x77, 
};

Gfx friendplayer_model_eyecut_I4_i8_aligner[] = {gsSPEndDisplayList()};
u8 friendplayer_model_eyecut_I4_i8[] = {
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

Gfx friendplayer_model_gem_env_rgba16_ci4_aligner[] = {gsSPEndDisplayList()};
u8 friendplayer_model_gem_env_rgba16_ci4[] = {
	0x1, 0x23, 0x45, 0x60, 
};

Gfx friendplayer_model_gem_env_rgba16_ci4_pal_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 friendplayer_model_gem_env_rgba16_ci4_pal_rgba16[] = {
	0xF2, 0xDB, 0xC2, 0xE5, 0xAB, 0xBD, 0xC5, 0x3D, 0xEE, 
	0xB7, 0xF6, 0x29, 0xF5, 0x1D, 
};


Gfx mat_friendplayer_model_base_toon_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, ENVIRONMENT, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, ENVIRONMENT),
	gsSPSetGeometryMode(G_TEXTURE_GEN),
	gsDPSetTextureFilter(G_TF_POINT),
	gsSPTexture(959, 0, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 8, friendplayer_model_shading_i4),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 30, 0),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 0),
	gsDPSetPrimColor(0, 0, 227, 222, 211, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_friendplayer_model_base_toon_f3d[] = {
	gsDPPipeSync(),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetTextureFilter(G_TF_BILERP),
	gsSPEndDisplayList(),
};


Gfx mat_friendplayer_model_h_env_dark[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(1, 0, ENVIRONMENT, 0, 0, 0, 0, ENVIRONMENT, 1, 0, ENVIRONMENT, 0, 0, 0, 0, ENVIRONMENT),
	gsSPSetGeometryMode(G_TEXTURE_GEN),
	gsSPTexture(447, 0, 0, 0, 1),
	gsDPSetEnvColor(138, 218, 220, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_friendplayer_model_h_env_dark[] = {
	gsDPPipeSync(),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsSPEndDisplayList(),
};


Gfx mat_friendplayer_model_h_env[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(1, 0, ENVIRONMENT, 0, 0, 0, 0, ENVIRONMENT, 1, 0, ENVIRONMENT, 0, 0, 0, 0, ENVIRONMENT),
	gsSPSetGeometryMode(G_TEXTURE_GEN),
	gsSPClearGeometryMode(G_LIGHTING),
	gsDPSetTextureFilter(G_TF_POINT),
	gsSPTexture(447, 0, 0, 0, 1),
	gsDPSetEnvColor(173, 251, 254, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_friendplayer_model_h_env[] = {
	gsDPPipeSync(),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsSPSetGeometryMode(G_LIGHTING),
	gsDPSetTextureFilter(G_TF_BILERP),
	gsSPEndDisplayList(),
};


Gfx mat_friendplayer_model_shroom_placeholder_1_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 1, 0, 0, 0, PRIMITIVE, 0, 0, 0, 1),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 254, 175, 0, 255),
	gsSPEndDisplayList(),
};


Gfx mat_friendplayer_model_shroom_placeholder_2_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, 1, 0, 0, 0, PRIMITIVE, 0, 0, 0, 1),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 233, 66, 63, 255),
	gsSPEndDisplayList(),
};


Gfx mat_friendplayer_model_eye_decal_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, 0, 0, 0, 0, TEXEL0, 0, 0, 0, 0, 0, 0, 0, TEXEL0),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 8, friendplayer_model_eyecut_I4_i8),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_WRAP | G_TX_MIRROR, 4, 0, G_TX_WRAP | G_TX_MIRROR, 3, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 28, 60),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 0, 0, G_TX_WRAP | G_TX_MIRROR, 4, 0, G_TX_WRAP | G_TX_MIRROR, 3, 0),
	gsDPSetTileSize(0, 0, 0, 28, 60),
	gsSPEndDisplayList(),
};


Gfx mat_friendplayer_model_t_env_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, PRIMITIVE, SHADE_ALPHA, PRIMITIVE, 0, 0, 0, ENVIRONMENT, TEXEL0, PRIMITIVE, SHADE_ALPHA, PRIMITIVE, 0, 0, 0, ENVIRONMENT),
	gsSPSetGeometryMode(G_TEXTURE_GEN),
	gsSPTexture(447, 0, 0, 0, 1),
	gsDPSetTextureLUT(G_TT_RGBA16),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, friendplayer_model_gem_env_rgba16_ci4_pal_rgba16),
	gsDPTileSync(),
	gsDPSetTile(0, 0, 0, 256, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTLUTCmd(7, 6),
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b, 4, friendplayer_model_gem_env_rgba16_ci4),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 14, 0),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, 0),
	gsDPSetTileSize(0, 0, 0, 28, 0),
	gsDPSetPrimColor(0, 0, 254, 89, 91, 255),
	gsSPSetLights1(friendplayer_model_t_env_f3d_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_friendplayer_model_t_env_f3d[] = {
	gsDPPipeSync(),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetTextureLUT(G_TT_NONE),
	gsSPEndDisplayList(),
};



Vtx friendplayer_Arm_1_mesh_vtx_0[16] = {
	{{{-21, 5, -3},0, {320, 32},{0x86, 0x1C, 0xED, 0xFF}}},
	{{{-10, -15, -3},0, {192, 24},{0xC0, 0x93, 0xF7, 0xFF}}},
	{{{-10, -4, 16},0, {192, 32},{0xC1, 0xD4, 0x65, 0xFF}}},
	{{{1, -6, -21},0, {320, 24},{0x1, 0xDF, 0x85, 0xFF}}},
	{{{0, 18, -11},0, {320, 24},{0xFF, 0x6D, 0xBF, 0xFF}}},
	{{{11, -15, -3},0, {192, 16},{0x40, 0x93, 0xF6, 0xFF}}},
	{{{22, 5, -2},0, {320, 16},{0x7A, 0x1F, 0xEF, 0xFF}}},
	{{{0, 18, -11},0, {320, 16},{0xFF, 0x6D, 0xBF, 0xFF}}},
	{{{11, -4, 15},0, {192, 8},{0x41, 0xD4, 0x64, 0xFF}}},
	{{{0, 16, 16},0, {320, 8},{0xFE, 0x5C, 0x57, 0xFF}}},
	{{{0, 18, -11},0, {320, 8},{0xFF, 0x6D, 0xBF, 0xFF}}},
	{{{-10, -4, 16},0, {192, 0},{0xC1, 0xD4, 0x65, 0xFF}}},
	{{{-21, 5, -3},0, {320, 0},{0x86, 0x1C, 0xED, 0xFF}}},
	{{{0, 18, -11},0, {320, 0},{0xFF, 0x6D, 0xBF, 0xFF}}},
	{{{-10, -4, 16},0, {64, 8},{0xC1, 0xD4, 0x65, 0xFF}}},
	{{{-10, -15, -3},0, {64, 16},{0xC0, 0x93, 0xF7, 0xFF}}},
};

Gfx friendplayer_Arm_1_mesh_tri_0[] = {
	gsSPVertex(friendplayer_Arm_1_mesh_vtx_0 + 0, 16, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(3, 0, 4, 0, 3, 5, 1, 0),
	gsSP2Triangles(3, 6, 5, 0, 6, 3, 7, 0),
	gsSP2Triangles(6, 8, 5, 0, 6, 9, 8, 0),
	gsSP2Triangles(9, 6, 10, 0, 9, 11, 8, 0),
	gsSP2Triangles(9, 12, 11, 0, 12, 9, 13, 0),
	gsSP2Triangles(5, 14, 15, 0, 5, 8, 14, 0),
	gsSPEndDisplayList(),
};

Gfx friendplayer_Arm_1_mesh[] = {
	gsSPDisplayList(mat_friendplayer_model_base_toon_f3d),
	gsSPDisplayList(friendplayer_Arm_1_mesh_tri_0),
	gsSPDisplayList(mat_revert_friendplayer_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx friendplayer_Arm_2_mesh_vtx_0[14] = {
	{{{7, 18, -6},0, {192, 16},{0x1A, 0x7C, 0xF4, 0xFF}}},
	{{{8, 9, 9},0, {192, 8},{0x23, 0x3C, 0x6B, 0xFF}}},
	{{{19, 5, -4},0, {64, 8},{0x7B, 0x1F, 0xFC, 0xFF}}},
	{{{-15, 7, -1},0, {320, 16},{0x90, 0x30, 0x25, 0xFF}}},
	{{{-4, 6, -25},0, {320, 24},{0xE6, 0x1B, 0x87, 0xFF}}},
	{{{19, 5, -4},0, {192, 24},{0x7B, 0x1F, 0xFC, 0xFF}}},
	{{{17, -9, -9},0, {320, 32},{0x5E, 0xB5, 0xD7, 0xFF}}},
	{{{-11, -13, -8},0, {320, 24},{0xB0, 0xA1, 0xE8, 0xFF}}},
	{{{-11, -13, -8},0, {320, 16},{0xB0, 0xA1, 0xE8, 0xFF}}},
	{{{17, -9, -9},0, {320, 0},{0x5E, 0xB5, 0xD7, 0xFF}}},
	{{{4, -12, 11},0, {320, 8},{0xB, 0xB3, 0x64, 0xFF}}},
	{{{-11, -13, -8},0, {320, 0},{0xB0, 0xA1, 0xE8, 0xFF}}},
	{{{19, 5, -4},0, {192, 0},{0x7B, 0x1F, 0xFC, 0xFF}}},
	{{{-11, -13, -8},0, {320, 8},{0xB0, 0xA1, 0xE8, 0xFF}}},
};

Gfx friendplayer_Arm_2_mesh_tri_0[] = {
	gsSPVertex(friendplayer_Arm_2_mesh_vtx_0 + 0, 14, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
	gsSP2Triangles(4, 3, 0, 0, 4, 0, 5, 0),
	gsSP2Triangles(6, 4, 5, 0, 4, 6, 7, 0),
	gsSP2Triangles(3, 4, 8, 0, 9, 10, 11, 0),
	gsSP2Triangles(10, 9, 12, 0, 10, 12, 1, 0),
	gsSP2Triangles(3, 10, 1, 0, 10, 3, 13, 0),
	gsSPEndDisplayList(),
};

Gfx friendplayer_Arm_2_mesh[] = {
	gsSPDisplayList(mat_friendplayer_model_base_toon_f3d),
	gsSPDisplayList(friendplayer_Arm_2_mesh_tri_0),
	gsSPDisplayList(mat_revert_friendplayer_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx friendplayer_Hand_mesh_vtx_0[21] = {
	{{{8, 0, 28},0, {496, 752},{0x31, 0x91, 0xDA, 0xFF}}},
	{{{29, 0, -9},0, {496, 496},{0xF9, 0xD4, 0x77, 0xFF}}},
	{{{1, 30, -1},0, {368, 752},{0x8B, 0xD3, 0xE9, 0xFF}}},
	{{{-7, 0, -30},0, {496, 240},{0xCF, 0x6F, 0x26, 0xFF}}},
	{{{-28, 0, 7},0, {496, -16},{0x7, 0x2C, 0x89, 0xFF}}},
	{{{1, 30, -1},0, {368, 240},{0x8B, 0xD3, 0xE9, 0xFF}}},
	{{{-28, 0, 7},0, {496, 1008},{0x7, 0x2C, 0x89, 0xFF}}},
	{{{1, -30, -1},0, {624, 752},{0x75, 0x2D, 0x17, 0xFF}}},
	{{{1, -30, -1},0, {624, 240},{0x75, 0x2D, 0x17, 0xFF}}},
	{{{19, 15, 9},0, {368, 496},{0xF8, 0x74, 0x33, 0xFF}}},
	{{{11, 15, -19},0, {368, 240},{0x61, 0x11, 0x51, 0xFF}}},
	{{{-18, 15, -12},0, {112, 240},{0x6E, 0xF5, 0xC2, 0xFF}}},
	{{{-10, 15, 17},0, {112, 496},{0x6, 0x57, 0xA4, 0xFF}}},
	{{{-18, -15, -12},0, {624, -16},{0x8, 0x8C, 0xCD, 0xFF}}},
	{{{-18, 15, -12},0, {368, -16},{0x6E, 0xF5, 0xC2, 0xFF}}},
	{{{11, -15, -19},0, {624, 240},{0xFA, 0xA9, 0x5C, 0xFF}}},
	{{{-10, -15, 17},0, {880, 496},{0x9F, 0xEF, 0xAF, 0xFF}}},
	{{{-18, -15, -12},0, {880, 240},{0x8, 0x8C, 0xCD, 0xFF}}},
	{{{19, -15, 9},0, {624, 496},{0x92, 0xB, 0x3E, 0xFF}}},
	{{{-10, 15, 17},0, {368, 752},{0x6, 0x57, 0xA4, 0xFF}}},
	{{{-10, -15, 17},0, {624, 752},{0x9F, 0xEF, 0xAF, 0xFF}}},
};

Gfx friendplayer_Hand_mesh_tri_0[] = {
	gsSPVertex(friendplayer_Hand_mesh_vtx_0 + 0, 21, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 0, 0, 1, 8, 3, 0),
	gsSP2Triangles(9, 10, 11, 0, 9, 11, 12, 0),
	gsSP2Triangles(13, 14, 10, 0, 13, 10, 15, 0),
	gsSP2Triangles(16, 17, 15, 0, 16, 15, 18, 0),
	gsSP2Triangles(18, 9, 19, 0, 18, 19, 20, 0),
	gsSPEndDisplayList(),
};Vtx friendplayer_Hand_mesh_vtx_1[17] = {
	{{{-28, 0, 7},0, {512, 1024},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{8, 0, 28},0, {512, 768},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{1, 30, -1},0, {384, 1024},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{29, 0, -9},0, {512, 512},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-7, 0, -30},0, {512, 256},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{1, 30, -1},0, {384, 512},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{1, -30, -1},0, {640, 512},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{1, -30, -1},0, {640, 0},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-28, 0, 7},0, {512, 0},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-18, 15, -12},0, {384, 1024},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-18, -15, -12},0, {640, 1024},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-10, -15, 17},0, {640, 768},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-10, 15, 17},0, {384, 768},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{19, 15, 9},0, {384, 512},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{11, -15, -19},0, {640, 256},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{11, 15, -19},0, {384, 256},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{19, -15, 9},0, {640, 512},{0xFF, 0xFF, 0xFF, 0xFF}}},
};

Gfx friendplayer_Hand_mesh_tri_1[] = {
	gsSPVertex(friendplayer_Hand_mesh_vtx_1 + 0, 17, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(1, 6, 3, 0, 4, 7, 8, 0),
	gsSP2Triangles(9, 10, 11, 0, 9, 11, 12, 0),
	gsSP2Triangles(13, 14, 15, 0, 13, 16, 14, 0),
	gsSPEndDisplayList(),
};

Gfx friendplayer_Hand_mesh[] = {
	gsSPDisplayList(mat_friendplayer_model_h_env_dark),
	gsSPDisplayList(friendplayer_Hand_mesh_tri_0),
	gsSPDisplayList(mat_revert_friendplayer_model_h_env_dark),
	gsSPDisplayList(mat_friendplayer_model_h_env),
	gsSPDisplayList(friendplayer_Hand_mesh_tri_1),
	gsSPDisplayList(mat_revert_friendplayer_model_h_env),
	gsSPEndDisplayList(),
};



Vtx friendplayer_Foot_L_mesh_vtx_0[17] = {
	{{{-20, 18, 14},0, {320, 32},{0x9F, 0x42, 0x30, 0xFF}}},
	{{{-5, 0, 28},0, {192, 32},{0x7, 0xCA, 0x73, 0xFF}}},
	{{{6, 25, 12},0, {320, 32},{0x45, 0x59, 0x3A, 0xFF}}},
	{{{8, 0, 13},0, {192, 24},{0x5C, 0xB2, 0x27, 0xFF}}},
	{{{8, 25, -7},0, {320, 24},{0x53, 0x51, 0xCD, 0xFF}}},
	{{{9, 0, -12},0, {192, 16},{0x54, 0xBC, 0xBC, 0xFF}}},
	{{{-11, 25, -13},0, {320, 16},{0xC3, 0x50, 0xB3, 0xFF}}},
	{{{-13, 0, -17},0, {192, 12},{0xC6, 0xC1, 0xA3, 0xFF}}},
	{{{-5, 0, 28},0, {64, 8},{0x7, 0xCA, 0x73, 0xFF}}},
	{{{8, 0, 13},0, {64, 16},{0x5C, 0xB2, 0x27, 0xFF}}},
	{{{-21, 0, 12},0, {192, 8},{0x9D, 0xB5, 0x18, 0xFF}}},
	{{{-20, 18, 14},0, {320, 8},{0x9F, 0x42, 0x30, 0xFF}}},
	{{{-5, 0, 28},0, {192, 0},{0x7, 0xCA, 0x73, 0xFF}}},
	{{{-12, 25, 1},0, {320, 8},{0xBA, 0x6A, 0xFD, 0xFF}}},
	{{{6, 25, 12},0, {448, 8},{0x45, 0x59, 0x3A, 0xFF}}},
	{{{-20, 18, 14},0, {448, 8},{0x9F, 0x42, 0x30, 0xFF}}},
	{{{8, 25, -7},0, {448, 16},{0x53, 0x51, 0xCD, 0xFF}}},
};

Gfx friendplayer_Foot_L_mesh_tri_0[] = {
	gsSPVertex(friendplayer_Foot_L_mesh_vtx_0 + 0, 17, 0),
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

Gfx friendplayer_Foot_L_mesh[] = {
	gsSPDisplayList(mat_friendplayer_model_base_toon_f3d),
	gsSPDisplayList(friendplayer_Foot_L_mesh_tri_0),
	gsSPDisplayList(mat_revert_friendplayer_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx friendplayer_Foot_R_mesh_vtx_0[18] = {
	{{{16, 25, -15},0, {320, 16},{0x3D, 0x46, 0xAA, 0xFF}}},
	{{{4, 25, 17},0, {448, 8},{0x1B, 0x5F, 0x4F, 0xFF}}},
	{{{16, 25, 1},0, {448, 16},{0x59, 0x57, 0x1C, 0xFF}}},
	{{{-6, 25, -5},0, {320, 8},{0xCA, 0x66, 0xCC, 0xFF}}},
	{{{-5, 0, -14},0, {192, 12},{0xDF, 0xB8, 0x9D, 0xFF}}},
	{{{19, 0, -6},0, {192, 16},{0x5D, 0xB1, 0xDE, 0xFF}}},
	{{{16, 25, 1},0, {320, 24},{0x59, 0x57, 0x1C, 0xFF}}},
	{{{10, 0, 16},0, {192, 24},{0x46, 0xB6, 0x4B, 0xFF}}},
	{{{4, 25, 17},0, {320, 32},{0x1B, 0x5F, 0x4F, 0xFF}}},
	{{{-6, 18, 21},0, {320, 32},{0xDD, 0x42, 0x67, 0xFF}}},
	{{{-15, 0, 24},0, {192, 32},{0xC4, 0xC7, 0x61, 0xFF}}},
	{{{-15, 0, 24},0, {64, 8},{0xC4, 0xC7, 0x61, 0xFF}}},
	{{{-25, 0, 1},0, {192, 8},{0x8F, 0xC9, 0xED, 0xFF}}},
	{{{-16, 18, -1},0, {320, 8},{0x9E, 0x4A, 0xE1, 0xFF}}},
	{{{-6, 18, 21},0, {320, 0},{0xDD, 0x42, 0x67, 0xFF}}},
	{{{-15, 0, 24},0, {192, 0},{0xC4, 0xC7, 0x61, 0xFF}}},
	{{{-6, 18, 21},0, {448, 8},{0xDD, 0x42, 0x67, 0xFF}}},
	{{{10, 0, 16},0, {64, 16},{0x46, 0xB6, 0x4B, 0xFF}}},
};

Gfx friendplayer_Foot_R_mesh_tri_0[] = {
	gsSPVertex(friendplayer_Foot_R_mesh_vtx_0 + 0, 18, 0),
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

Gfx friendplayer_Foot_R_mesh[] = {
	gsSPDisplayList(mat_friendplayer_model_base_toon_f3d),
	gsSPDisplayList(friendplayer_Foot_R_mesh_tri_0),
	gsSPDisplayList(mat_revert_friendplayer_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx friendplayer_Head_mesh_vtx_0[19] = {
	{{{-6, -15, -30},0, {64, 16},{0xB, 0xAE, 0x9F, 0xFF}}},
	{{{-31, -15, 1},0, {64, 8},{0xAC, 0xAA, 0x2B, 0xFF}}},
	{{{-40, 6, -17},0, {64, 16},{0x8B, 0x1, 0xCE, 0xFF}}},
	{{{19, -15, 30},0, {192, 8},{0x8, 0xAF, 0x61, 0xFF}}},
	{{{32, -15, 13},0, {192, 16},{0x5C, 0xA8, 0xFA, 0xFF}}},
	{{{25, 12, 33},0, {320, 8},{0x21, 0x29, 0x74, 0xFF}}},
	{{{42, 5, 12},0, {320, 16},{0x7D, 0x16, 0xF8, 0xFF}}},
	{{{-6, -15, -30},0, {192, 24},{0xB, 0xAE, 0x9F, 0xFF}}},
	{{{-6, 25, -30},0, {320, 24},{0xF, 0x47, 0x98, 0xFF}}},
	{{{-40, 6, -17},0, {320, 24},{0x8B, 0x1, 0xCE, 0xFF}}},
	{{{-2, 32, -3},0, {320, 24},{0x12, 0x7E, 0x6, 0xFF}}},
	{{{-31, 25, 1},0, {320, 32},{0xAA, 0x53, 0x2D, 0xFF}}},
	{{{-40, 6, -17},0, {320, 32},{0x8B, 0x1, 0xCE, 0xFF}}},
	{{{25, 21, 17},0, {320, 16},{0x34, 0x71, 0x1A, 0xFF}}},
	{{{-31, -15, 1},0, {192, 0},{0xAC, 0xAA, 0x2B, 0xFF}}},
	{{{-31, 25, 1},0, {320, 0},{0xAA, 0x53, 0x2D, 0xFF}}},
	{{{-40, 6, -17},0, {192, 0},{0x8B, 0x1, 0xCE, 0xFF}}},
	{{{25, 21, 17},0, {320, 8},{0x34, 0x71, 0x1A, 0xFF}}},
	{{{-2, 32, -3},0, {320, 0},{0x12, 0x7E, 0x6, 0xFF}}},
};

Gfx friendplayer_Head_mesh_tri_0[] = {
	gsSPVertex(friendplayer_Head_mesh_vtx_0 + 0, 19, 0),
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
};Vtx friendplayer_Head_mesh_vtx_1[8] = {
	{{{-1, 37, 2},0, {624, 1008},{0x3, 0x26, 0x79, 0xFF}}},
	{{{4, 37, -6},0, {624, 752},{0x78, 0x1B, 0xDF, 0xFF}}},
	{{{-8, 51, -9},0, {624, 1008},{0xC3, 0x6B, 0xE2, 0xFF}}},
	{{{-4, 27, 2},0, {624, 1008},{0xE1, 0x1B, 0x78, 0xFF}}},
	{{{-7, 28, -9},0, {624, 752},{0xAC, 0x2A, 0xAB, 0xFF}}},
	{{{-3, 36, -8},0, {624, 752},{0xB8, 0x8, 0x98, 0xFF}}},
	{{{-8, 51, -9},0, {624, 752},{0xC3, 0x6B, 0xE2, 0xFF}}},
	{{{2, 27, -6},0, {624, 752},{0x74, 0xE4, 0xD4, 0xFF}}},
};

Gfx friendplayer_Head_mesh_tri_1[] = {
	gsSPVertex(friendplayer_Head_mesh_vtx_1 + 0, 8, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
	gsSP2Triangles(4, 3, 0, 0, 4, 0, 5, 0),
	gsSP2Triangles(5, 0, 6, 0, 1, 5, 6, 0),
	gsSP2Triangles(7, 5, 1, 0, 3, 7, 1, 0),
	gsSP1Triangle(7, 4, 5, 0),
	gsSPEndDisplayList(),
};Vtx friendplayer_Head_mesh_vtx_2[7] = {
	{{{6, 46, -20},0, {624, 752},{0xD, 0x79, 0xDB, 0xFF}}},
	{{{-14, 41, -23},0, {624, 752},{0xC2, 0x66, 0xD4, 0xFF}}},
	{{{-8, 51, -9},0, {624, 752},{0xD8, 0x79, 0x1, 0xFF}}},
	{{{-18, 38, -5},0, {624, 863},{0xA1, 0x51, 0x14, 0xFF}}},
	{{{-6, 43, 9},0, {624, 1008},{0xDA, 0x6C, 0x37, 0xFF}}},
	{{{8, 46, 0},0, {624, 885},{0x15, 0x7B, 0x1A, 0xFF}}},
	{{{-8, 51, -9},0, {624, 1008},{0xD8, 0x79, 0x1, 0xFF}}},
};

Gfx friendplayer_Head_mesh_tri_2[] = {
	gsSPVertex(friendplayer_Head_mesh_vtx_2 + 0, 7, 0),
	gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
	gsSP2Triangles(2, 3, 4, 0, 4, 5, 6, 0),
	gsSP1Triangle(6, 5, 0, 0),
	gsSPEndDisplayList(),
};

Gfx friendplayer_Head_mesh[] = {
	gsSPDisplayList(mat_friendplayer_model_base_toon_f3d),
	gsSPDisplayList(friendplayer_Head_mesh_tri_0),
	gsSPDisplayList(mat_revert_friendplayer_model_base_toon_f3d),
	gsSPDisplayList(mat_friendplayer_model_shroom_placeholder_1_f3d),
	gsSPDisplayList(friendplayer_Head_mesh_tri_1),
	gsSPDisplayList(mat_friendplayer_model_shroom_placeholder_2_f3d),
	gsSPDisplayList(friendplayer_Head_mesh_tri_2),
	gsSPEndDisplayList(),
};



Vtx friendplayer_Eye_L_mesh_vtx_0[4] = {
	{{{-3, -9, -2},0, {-16, 1008},{0xC1, 0x0, 0x6E, 0xFF}}},
	{{{3, -9, 2},0, {496, 1008},{0xC1, 0x0, 0x6E, 0xFF}}},
	{{{3, 9, 2},0, {496, -16},{0xC1, 0x0, 0x6E, 0xFF}}},
	{{{-3, 9, -2},0, {-16, -16},{0xC1, 0x0, 0x6E, 0xFF}}},
};

Gfx friendplayer_Eye_L_mesh_tri_0[] = {
	gsSPVertex(friendplayer_Eye_L_mesh_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx friendplayer_Eye_L_mesh[] = {
	gsSPDisplayList(mat_friendplayer_model_eye_decal_f3d),
	gsSPDisplayList(friendplayer_Eye_L_mesh_tri_0),
	gsSPEndDisplayList(),
};



Vtx friendplayer_Eye_R_mesh_vtx_0[4] = {
	{{{-3, -9, -2},0, {-16, 1008},{0xC1, 0x0, 0x6E, 0xFF}}},
	{{{3, -9, 2},0, {496, 1008},{0xC1, 0x0, 0x6E, 0xFF}}},
	{{{3, 9, 2},0, {496, -16},{0xC1, 0x0, 0x6E, 0xFF}}},
	{{{-3, 9, -2},0, {-16, -16},{0xC1, 0x0, 0x6E, 0xFF}}},
};

Gfx friendplayer_Eye_R_mesh_tri_0[] = {
	gsSPVertex(friendplayer_Eye_R_mesh_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx friendplayer_Eye_R_mesh[] = {
	gsSPDisplayList(mat_friendplayer_model_eye_decal_f3d),
	gsSPDisplayList(friendplayer_Eye_R_mesh_tri_0),
	gsSPEndDisplayList(),
};



Vtx friendplayer_Torso_mesh_vtx_0[21] = {
	{{{24, -2, -33},0, {64, 16},{0x54, 0xFD, 0xA1, 0xFF}}},
	{{{35, 11, 2},0, {0, 32},{0x7A, 0x1F, 0xF1, 0xFF}}},
	{{{25, -23, -5},0, {64, 16},{0x56, 0xA7, 0xE5, 0xFF}}},
	{{{9, 27, -16},0, {0, 32},{0x20, 0x64, 0xB9, 0xFF}}},
	{{{-12, -4, -41},0, {64, 16},{0xDC, 0x8, 0x86, 0xFF}}},
	{{{-8, -28, -32},0, {64, 8},{0xF8, 0x9D, 0xB1, 0xFF}}},
	{{{-6, -32, -12},0, {129, 8},{0x0, 0x82, 0xF1, 0xFF}}},
	{{{25, -23, -5},0, {129, 8},{0x56, 0xA7, 0xE5, 0xFF}}},
	{{{-33, -19, -9},0, {64, 8},{0x9A, 0xBD, 0xDE, 0xFF}}},
	{{{-27, 19, -21},0, {64, 16},{0xB1, 0x49, 0xBD, 0xFF}}},
	{{{-40, 0, 2},0, {64, 8},{0x83, 0xC, 0x10, 0xFF}}},
	{{{-27, -22, 15},0, {129, 8},{0xB4, 0xB0, 0x40, 0xFF}}},
	{{{18, -25, 29},0, {192, 8},{0x2B, 0xA4, 0x4C, 0xFF}}},
	{{{25, -23, -5},0, {192, 8},{0x56, 0xA7, 0xE5, 0xFF}}},
	{{{8, 2, 41},0, {192, 8},{0xB, 0x3, 0x7E, 0xFF}}},
	{{{32, -6, 22},0, {192, 16},{0x72, 0xEF, 0x36, 0xFF}}},
	{{{25, -23, -5},0, {192, 16},{0x56, 0xA7, 0xE5, 0xFF}}},
	{{{21, 37, 15},0, {192, 16},{0x43, 0x68, 0x1D, 0xFF}}},
	{{{25, -23, -5},0, {0, 32},{0x56, 0xA7, 0xE5, 0xFF}}},
	{{{-7, 38, 17},0, {192, 16},{0xDC, 0x78, 0x16, 0xFF}}},
	{{{-14, 29, 29},0, {192, 8},{0xC2, 0x43, 0x58, 0xFF}}},
};

Gfx friendplayer_Torso_mesh_tri_0[] = {
	gsSPVertex(friendplayer_Torso_mesh_vtx_0 + 0, 21, 0),
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
};Vtx friendplayer_Torso_mesh_vtx_1[11] = {
	{{{-31, 8, 11},0, {16, -8},{0x8C, 0xFD, 0x33, 0xFF}}},
	{{{-18, -10, 22},0, {48, -8},{0xBB, 0xB6, 0x4C, 0xFF}}},
	{{{-22, 4, 32},0, {16, -8},{0xB3, 0xE8, 0x62, 0xFF}}},
	{{{-2, 7, 34},0, {80, -8},{0xF3, 0xF4, 0x7E, 0xFF}}},
	{{{-22, 4, 32},0, {48, -8},{0xB3, 0xE8, 0x62, 0xFF}}},
	{{{-6, -7, 30},0, {80, -8},{0x8B, 0xFF, 0x32, 0x0}}},
	{{{-9, 21, 31},0, {80, -8},{0xDD, 0xC5, 0x6B, 0x0}}},
	{{{-22, 4, 32},0, {80, -8},{0xB3, 0xE8, 0x62, 0xFF}}},
	{{{-35, -4, 7},0, {48, -8},{0xF3, 0x32, 0x74, 0x0}}},
	{{{-9, 21, 31},0, {16, -8},{0xDD, 0xC5, 0x6B, 0x0}}},
	{{{-16, 25, 26},0, {80, -8},{0xBB, 0x2E, 0x60, 0x63}}},
};

Gfx friendplayer_Torso_mesh_tri_1[] = {
	gsSPVertex(friendplayer_Torso_mesh_vtx_1 + 0, 11, 0),
	gsSP2Triangles(0, 1, 2, 0, 1, 3, 4, 0),
	gsSP2Triangles(5, 6, 7, 0, 8, 5, 4, 0),
	gsSP2Triangles(9, 8, 2, 0, 10, 0, 7, 0),
	gsSP1Triangle(3, 10, 7, 0),
	gsSPEndDisplayList(),
};

Gfx friendplayer_Torso_mesh[] = {
	gsSPDisplayList(mat_friendplayer_model_base_toon_f3d),
	gsSPDisplayList(friendplayer_Torso_mesh_tri_0),
	gsSPDisplayList(mat_revert_friendplayer_model_base_toon_f3d),
	gsSPDisplayList(mat_friendplayer_model_t_env_f3d),
	gsSPDisplayList(friendplayer_Torso_mesh_tri_1),
	gsSPDisplayList(mat_revert_friendplayer_model_t_env_f3d),
	gsSPEndDisplayList(),
};




BoneLayer friendplayer_model_bone2_layers[] = {
    {
		LAYER_OPA_SURF,
        friendplayer_Arm_1_mesh,
    },
};
BoneLayer friendplayer_model_bone3_layers[] = {
    {
		LAYER_OPA_SURF,
        friendplayer_Arm_2_mesh,
    },
};
BoneLayer friendplayer_model_bone4_layers[] = {
    {
		LAYER_OPA_SURF,
        friendplayer_Hand_mesh,
    },
};
BoneLayer friendplayer_model_bone5_layers[] = {
    {
		LAYER_OPA_SURF,
        friendplayer_Foot_L_mesh,
    },
};
BoneLayer friendplayer_model_bone6_layers[] = {
    {
		LAYER_OPA_SURF,
        friendplayer_Foot_R_mesh,
    },
};
BoneLayer friendplayer_model_bone7_layers[] = {
    {
		LAYER_OPA_SURF,
        friendplayer_Head_mesh,
    },
};
BoneLayer friendplayer_model_bone8_layers[] = {
    {
		LAYER_TEX_EDGE,
        friendplayer_Eye_L_mesh,
    },
};
BoneLayer friendplayer_model_bone9_layers[] = {
    {
		LAYER_TEX_EDGE,
        friendplayer_Eye_R_mesh,
    },
};
BoneLayer friendplayer_model_bone10_layers[] = {
    {
		LAYER_OPA_SURF,
        friendplayer_Torso_mesh,
    },
};

Bone friendplayer_model_bones[] = {
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
        0,
        0,
        0.04781043529510498,
        106.28129577636719,
        0.106930211186409,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        2,
        1,
        1,
        0,
        -50.57813262939453,
        -5.496072769165039,
        -27.606599807739258,
        friendplayer_model_bone2_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        3,
        1,
        1,
        0,
        -82.46212768554688,
        -5.496072769165039,
        -45.988441467285156,
        friendplayer_model_bone3_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        4,
        1,
        1,
        0,
        -115.48516082763672,
        -5.496072769165039,
        -65.02696990966797,
        friendplayer_model_bone4_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        5,
        0,
        1,
        0,
        27.13017463684082,
        0.16872116923332214,
        15.641151428222656,
        friendplayer_model_bone5_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        6,
        0,
        1,
        0,
        -27.130138397216797,
        0.1687174141407013,
        -15.64115047454834,
        friendplayer_model_bone6_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        7,
        0,
        1,
        0,
        0.7122112512588501,
        127.73494720458984,
        4.671106815338135,
        friendplayer_model_bone7_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        8,
        7,
        1,
        0,
        0.3268371522426605,
        4.263944625854492,
        21.17250633239746,
        friendplayer_model_bone8_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        9,
        7,
        1,
        0,
        -19.889333724975586,
        7.585477828979492,
        9.51487922668457,
        friendplayer_model_bone9_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        10,
        0,
        1,
        0,
        -2.3088630030088098e-07,
        68.54440307617188,
        -2.595690148154972e-06,
        friendplayer_model_bone10_layers,
        NULL,
        NULL,
        NULL,
    },
};

Model friendplayer_model = {
    11,
    0,
    friendplayer_model_bones
};

