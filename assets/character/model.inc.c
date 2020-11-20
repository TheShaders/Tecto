
Gfx character_model_shading_i4_aligner[] = {gsSPEndDisplayList()};
u8 character_model_shading_i4[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xBB, 0x77, 0x77, 
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


Gfx mat_character_model_h_env_dark[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(1, 0, ENVIRONMENT, 0, 0, 0, 0, ENVIRONMENT, 1, 0, ENVIRONMENT, 0, 0, 0, 0, ENVIRONMENT),
	gsSPSetGeometryMode(G_TEXTURE_GEN),
	gsSPTexture(447, 0, 0, 0, 1),
	gsDPSetEnvColor(138, 218, 220, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_character_model_h_env_dark[] = {
	gsDPPipeSync(),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsSPEndDisplayList(),
};


Gfx mat_character_model_h_env[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(1, 0, ENVIRONMENT, 0, 0, 0, 0, ENVIRONMENT, 1, 0, ENVIRONMENT, 0, 0, 0, 0, ENVIRONMENT),
	gsSPSetGeometryMode(G_TEXTURE_GEN),
	gsSPClearGeometryMode(G_LIGHTING),
	gsDPSetTextureFilter(G_TF_POINT),
	gsSPTexture(447, 0, 0, 0, 1),
	gsDPSetEnvColor(173, 251, 254, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_character_model_h_env[] = {
	gsDPPipeSync(),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsSPSetGeometryMode(G_LIGHTING),
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


Gfx mat_character_model_black_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1),
	gsSPTexture(65535, 65535, 0, 0, 1),
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



Vtx character_Arm_1_mesh_vtx_0[16] = {
	{{{-98, 25, 40},0, {320, 32},{0x8C, 0x1C, 0x2D, 0xFF}}},
	{{{-52, -77, 13},0, {192, 24},{0xC4, 0x92, 0x18, 0xFF}}},
	{{{-5, -22, 93},0, {192, 32},{0xFC, 0xD4, 0x77, 0xFF}}},
	{{{-50, -29, -94},0, {320, 24},{0xC4, 0xDF, 0x95, 0xFF}}},
	{{{-25, 92, -47},0, {320, 24},{0xDF, 0x6D, 0xC8, 0xFF}}},
	{{{41, -77, -42},0, {192, 16},{0x33, 0x93, 0xD7, 0xFF}}},
	{{{89, 27, -66},0, {320, 16},{0x61, 0x1F, 0xB4, 0xFF}}},
	{{{-25, 92, -47},0, {320, 16},{0xDF, 0x6D, 0xC8, 0xFF}}},
	{{{88, -22, 38},0, {192, 8},{0x6A, 0xD4, 0x37, 0xFF}}},
	{{{40, 81, 68},0, {320, 8},{0x2B, 0x5C, 0x4C, 0xFF}}},
	{{{-25, 92, -47},0, {320, 8},{0xDF, 0x6D, 0xC8, 0xFF}}},
	{{{-5, -22, 93},0, {192, 0},{0xFC, 0xD4, 0x77, 0xFF}}},
	{{{-98, 25, 40},0, {320, 0},{0x8C, 0x1C, 0x2D, 0xFF}}},
	{{{-25, 92, -47},0, {320, 0},{0xDF, 0x6D, 0xC8, 0xFF}}},
	{{{-5, -22, 93},0, {64, 8},{0xFC, 0xD4, 0x77, 0xFF}}},
	{{{-52, -77, 13},0, {64, 16},{0xC4, 0x92, 0x18, 0xFF}}},
};

Gfx character_Arm_1_mesh_tri_0[] = {
	gsSPVertex(character_Arm_1_mesh_vtx_0 + 0, 16, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(3, 0, 4, 0, 3, 5, 1, 0),
	gsSP2Triangles(3, 6, 5, 0, 6, 3, 7, 0),
	gsSP2Triangles(6, 8, 5, 0, 6, 9, 8, 0),
	gsSP2Triangles(9, 6, 10, 0, 9, 11, 8, 0),
	gsSP2Triangles(9, 12, 11, 0, 12, 9, 13, 0),
	gsSP2Triangles(5, 14, 15, 0, 5, 8, 14, 0),
	gsSPEndDisplayList(),
};

Gfx character_Arm_1_mesh[] = {
	gsSPDisplayList(mat_character_model_base_toon_f3d),
	gsSPDisplayList(character_Arm_1_mesh_tri_0),
	gsSPDisplayList(mat_revert_character_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx character_Arm_2_mesh_vtx_0[14] = {
	{{{13, 91, -43},0, {192, 16},{0x10, 0x7C, 0xE8, 0xFF}}},
	{{{59, 45, 20},0, {192, 8},{0x53, 0x3B, 0x4B, 0xFF}}},
	{{{72, 23, -67},0, {64, 8},{0x68, 0x1F, 0xBE, 0xFF}}},
	{{{-68, 34, 35},0, {320, 16},{0xB1, 0x30, 0x58, 0xFF}}},
	{{{-77, 30, -99},0, {320, 24},{0xAD, 0x1B, 0xA4, 0xFF}}},
	{{{72, 23, -67},0, {192, 24},{0x68, 0x1F, 0xBE, 0xFF}}},
	{{{51, -47, -82},0, {320, 32},{0x3E, 0xB6, 0xAE, 0xFF}}},
	{{{-69, -66, -5},0, {320, 24},{0xAE, 0xA1, 0x13, 0xFF}}},
	{{{-69, -66, -5},0, {320, 16},{0xAE, 0xA1, 0x13, 0xFF}}},
	{{{51, -47, -82},0, {320, 0},{0x3E, 0xB6, 0xAE, 0xFF}}},
	{{{47, -61, 39},0, {320, 8},{0x3B, 0xB2, 0x52, 0xFF}}},
	{{{-69, -66, -5},0, {320, 0},{0xAE, 0xA1, 0x13, 0xFF}}},
	{{{72, 23, -67},0, {192, 0},{0x68, 0x1F, 0xBE, 0xFF}}},
	{{{-69, -66, -5},0, {320, 8},{0xAE, 0xA1, 0x13, 0xFF}}},
};

Gfx character_Arm_2_mesh_tri_0[] = {
	gsSPVertex(character_Arm_2_mesh_vtx_0 + 0, 14, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
	gsSP2Triangles(4, 3, 0, 0, 4, 0, 5, 0),
	gsSP2Triangles(6, 4, 5, 0, 4, 6, 7, 0),
	gsSP2Triangles(3, 4, 8, 0, 9, 10, 11, 0),
	gsSP2Triangles(10, 9, 12, 0, 10, 12, 1, 0),
	gsSP2Triangles(3, 10, 1, 0, 10, 3, 13, 0),
	gsSPEndDisplayList(),
};

Gfx character_Arm_2_mesh[] = {
	gsSPDisplayList(mat_character_model_base_toon_f3d),
	gsSPDisplayList(character_Arm_2_mesh_tri_0),
	gsSPDisplayList(mat_revert_character_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx character_Hand_mesh_vtx_0[21] = {
	{{{105, 0, 98},0, {496, 752},{0x19, 0x91, 0xC7, 0xFF}}},
	{{{104, 0, -110},0, {496, 496},{0x35, 0xD5, 0x6B, 0xFF}}},
	{{{0, 149, -6},0, {368, 752},{0x90, 0xD3, 0x27, 0xFF}}},
	{{{-105, 0, -110},0, {496, 240},{0xE7, 0x6F, 0x39, 0xFF}}},
	{{{-104, 0, 99},0, {496, -16},{0xCB, 0x2B, 0x95, 0xFF}}},
	{{{0, 149, -6},0, {368, 240},{0x90, 0xD3, 0x27, 0xFF}}},
	{{{-104, 0, 99},0, {496, 1008},{0xCB, 0x2B, 0x95, 0xFF}}},
	{{{0, -149, -6},0, {624, 752},{0x70, 0x2D, 0xD9, 0xFF}}},
	{{{0, -149, -6},0, {624, 240},{0x70, 0x2D, 0xD9, 0xFF}}},
	{{{105, 74, -6},0, {368, 496},{0x13, 0x74, 0x31, 0xFF}}},
	{{{0, 74, -111},0, {368, 240},{0x7C, 0x11, 0x16, 0xFF}}},
	{{{-105, 74, -6},0, {112, 240},{0x40, 0xF5, 0x93, 0xFF}}},
	{{{0, 74, 99},0, {112, 496},{0xD7, 0x57, 0xAD, 0xFF}}},
	{{{-105, -74, -6},0, {624, -16},{0xED, 0x8C, 0xCF, 0xFF}}},
	{{{-105, 74, -6},0, {368, -16},{0x40, 0xF5, 0x93, 0xFF}}},
	{{{0, -74, -111},0, {624, 240},{0x29, 0xA9, 0x53, 0xFF}}},
	{{{0, -74, 99},0, {880, 496},{0x84, 0xEF, 0xEA, 0xFF}}},
	{{{-105, -74, -6},0, {880, 240},{0xED, 0x8C, 0xCF, 0xFF}}},
	{{{105, -74, -6},0, {624, 496},{0xC0, 0xB, 0x6D, 0xFF}}},
	{{{0, 74, 99},0, {368, 752},{0xD7, 0x57, 0xAD, 0xFF}}},
	{{{0, -74, 99},0, {624, 752},{0x84, 0xEF, 0xEA, 0xFF}}},
};

Gfx character_Hand_mesh_tri_0[] = {
	gsSPVertex(character_Hand_mesh_vtx_0 + 0, 21, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 0, 0, 1, 8, 3, 0),
	gsSP2Triangles(9, 10, 11, 0, 9, 11, 12, 0),
	gsSP2Triangles(13, 14, 10, 0, 13, 10, 15, 0),
	gsSP2Triangles(16, 17, 15, 0, 16, 15, 18, 0),
	gsSP2Triangles(18, 9, 19, 0, 18, 19, 20, 0),
	gsSPEndDisplayList(),
};Vtx character_Hand_mesh_vtx_1[17] = {
	{{{-104, 0, 99},0, {512, 1024},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{105, 0, 98},0, {512, 768},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, 149, -6},0, {384, 1024},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{104, 0, -110},0, {512, 512},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-105, 0, -110},0, {512, 256},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, 149, -6},0, {384, 512},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, -149, -6},0, {640, 512},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, -149, -6},0, {640, 0},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-104, 0, 99},0, {512, 0},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-105, 74, -6},0, {384, 1024},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-105, -74, -6},0, {640, 1024},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, -74, 99},0, {640, 768},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, 74, 99},0, {384, 768},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{105, 74, -6},0, {384, 512},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, -74, -111},0, {640, 256},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, 74, -111},0, {384, 256},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{105, -74, -6},0, {640, 512},{0xFF, 0xFF, 0xFF, 0xFF}}},
};

Gfx character_Hand_mesh_tri_1[] = {
	gsSPVertex(character_Hand_mesh_vtx_1 + 0, 17, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(1, 6, 3, 0, 4, 7, 8, 0),
	gsSP2Triangles(9, 10, 11, 0, 9, 11, 12, 0),
	gsSP2Triangles(13, 14, 15, 0, 13, 16, 14, 0),
	gsSPEndDisplayList(),
};

Gfx character_Hand_mesh[] = {
	gsSPDisplayList(mat_character_model_h_env_dark),
	gsSPDisplayList(character_Hand_mesh_tri_0),
	gsSPDisplayList(mat_revert_character_model_h_env_dark),
	gsSPDisplayList(mat_character_model_h_env),
	gsSPDisplayList(character_Hand_mesh_tri_1),
	gsSPDisplayList(mat_revert_character_model_h_env),
	gsSPEndDisplayList(),
};



Vtx character_Foot_L_mesh_vtx_0[17] = {
	{{{-52, 89, 109},0, {320, 32},{0xC3, 0x43, 0x59, 0xFF}}},
	{{{50, 2, 134},0, {192, 32},{0x3F, 0xCA, 0x60, 0xFF}}},
	{{{57, 123, 36},0, {320, 32},{0x59, 0x5A, 0x10, 0xFF}}},
	{{{67, 2, 38},0, {192, 24},{0x63, 0xB2, 0xF3, 0xFF}}},
	{{{17, 123, -53},0, {320, 24},{0x2F, 0x51, 0xAB, 0xFF}}},
	{{{11, 2, -75},0, {192, 16},{0x27, 0xBC, 0x9C, 0xFF}}},
	{{{-82, 123, -29},0, {320, 16},{0xA5, 0x50, 0xDB, 0xFF}}},
	{{{-100, 2, -40},0, {192, 12},{0x9F, 0xC1, 0xCC, 0xFF}}},
	{{{50, 2, 134},0, {64, 8},{0x3F, 0xCA, 0x60, 0xFF}}},
	{{{67, 2, 38},0, {64, 16},{0x63, 0xB2, 0xF3, 0xFF}}},
	{{{-60, 2, 106},0, {192, 8},{0xB6, 0xB5, 0x46, 0xFF}}},
	{{{-52, 89, 109},0, {320, 8},{0xC3, 0x43, 0x59, 0xFF}}},
	{{{50, 2, 134},0, {192, 0},{0x3F, 0xCA, 0x60, 0xFF}}},
	{{{-48, 123, 34},0, {320, 8},{0xC2, 0x6A, 0x20, 0xFF}}},
	{{{57, 123, 36},0, {448, 8},{0x59, 0x5A, 0x10, 0xFF}}},
	{{{-52, 89, 109},0, {448, 8},{0xC3, 0x43, 0x59, 0xFF}}},
	{{{17, 123, -53},0, {448, 16},{0x2F, 0x51, 0xAB, 0xFF}}},
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
	{{{31, 123, -107},0, {320, 16},{0xA, 0x46, 0x97, 0xFF}}},
	{{{58, 123, 62},0, {448, 8},{0x3F, 0x5F, 0x37, 0xFF}}},
	{{{72, 123, -36},0, {448, 16},{0x5B, 0x56, 0xEC, 0xFF}}},
	{{{-40, 123, -9},0, {320, 8},{0xB7, 0x66, 0xEE, 0xFF}}},
	{{{-57, 2, -47},0, {192, 12},{0xB2, 0xB7, 0xBA, 0xFF}}},
	{{{65, 2, -74},0, {192, 16},{0x40, 0xB1, 0xB5, 0xFF}}},
	{{{72, 123, -36},0, {320, 24},{0x5B, 0x56, 0xEC, 0xFF}}},
	{{{86, 2, 44},0, {192, 24},{0x62, 0xB5, 0x1E, 0xFF}}},
	{{{58, 123, 62},0, {320, 32},{0x3F, 0x5F, 0x37, 0xFF}}},
	{{{27, 90, 105},0, {320, 32},{0x15, 0x42, 0x6A, 0xFF}}},
	{{{-4, 2, 139},0, {192, 32},{0xFC, 0xC8, 0x72, 0xFF}}},
	{{{-4, 2, 139},0, {64, 8},{0xFC, 0xC8, 0x72, 0xFF}}},
	{{{-102, 2, 68},0, {192, 8},{0x95, 0xC9, 0x29, 0xFF}}},
	{{{-71, 90, 34},0, {320, 8},{0x9C, 0x4B, 0x16, 0xFF}}},
	{{{27, 90, 105},0, {320, 0},{0x15, 0x42, 0x6A, 0xFF}}},
	{{{-4, 2, 139},0, {192, 0},{0xFC, 0xC8, 0x72, 0xFF}}},
	{{{27, 90, 105},0, {448, 8},{0x15, 0x42, 0x6A, 0xFF}}},
	{{{86, 2, 44},0, {64, 16},{0x62, 0xB5, 0x1E, 0xFF}}},
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
	{{{-101, -73, -115},0, {64, 16},{0xD9, 0xAF, 0xA7, 0xFF}}},
	{{{-130, -73, 83},0, {64, 8},{0xCD, 0xAA, 0x4E, 0xFF}}},
	{{{-215, 30, 25},0, {64, 16},{0x82, 0x1, 0xF, 0xFF}}},
	{{{158, -73, 72},0, {192, 8},{0x39, 0xAC, 0x4C, 0xFF}}},
	{{{171, -73, -24},0, {192, 16},{0x4C, 0xA8, 0xCE, 0xFF}}},
	{{{191, 58, 87},0, {320, 8},{0x54, 0x29, 0x56, 0xFF}}},
	{{{211, 23, -51},0, {320, 16},{0x68, 0x15, 0xBB, 0xFF}}},
	{{{-101, -73, -115},0, {192, 24},{0xD9, 0xAF, 0xA7, 0xFF}}},
	{{{-101, 127, -115},0, {320, 24},{0xD9, 0x47, 0x9E, 0xFF}}},
	{{{-215, 30, 25},0, {320, 24},{0x82, 0x1, 0xF, 0xFF}}},
	{{{-17, 159, -8},0, {320, 24},{0x12, 0x7E, 0xFB, 0xFF}}},
	{{{-130, 127, 83},0, {320, 32},{0xCC, 0x52, 0x53, 0xFF}}},
	{{{-215, 30, 25},0, {320, 32},{0x82, 0x1, 0xF, 0xFF}}},
	{{{150, 104, 12},0, {320, 16},{0x3A, 0x71, 0xFB, 0xFF}}},
	{{{-130, -73, 83},0, {192, 0},{0xCD, 0xAA, 0x4E, 0xFF}}},
	{{{-130, 127, 83},0, {320, 0},{0xCC, 0x52, 0x53, 0xFF}}},
	{{{-215, 30, 25},0, {192, 0},{0x82, 0x1, 0xF, 0xFF}}},
	{{{150, 104, 12},0, {320, 8},{0x3A, 0x71, 0xFB, 0xFF}}},
	{{{-17, 159, -8},0, {320, 0},{0x12, 0x7E, 0xFB, 0xFF}}},
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
	{{{0, 185, 9},0, {624, 1008},{0x40, 0x26, 0x67, 0xFF}}},
	{{{3, 187, -37},0, {624, 752},{0x57, 0x1B, 0xA8, 0xFF}}},
	{{{-58, 255, -16},0, {624, 1008},{0xBC, 0x6B, 0x5, 0xFF}}},
	{{{-13, 137, 20},0, {624, 1008},{0x22, 0x1B, 0x77, 0xFF}}},
	{{{-53, 140, -23},0, {624, 752},{0x8C, 0x2A, 0xE0, 0xFF}}},
	{{{-36, 179, -28},0, {624, 752},{0x8E, 0x8, 0xC9, 0xFF}}},
	{{{-58, 255, -16},0, {624, 752},{0xBC, 0x6B, 0x5, 0xFF}}},
	{{{-8, 133, -32},0, {624, 752},{0x4F, 0xE4, 0xA0, 0xFF}}},
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
	{{{-25, 229, -100},0, {624, 752},{0xF9, 0x79, 0xD9, 0xFF}}},
	{{{-118, 207, -63},0, {624, 752},{0xB5, 0x66, 0xF9, 0xFF}}},
	{{{-58, 255, -16},0, {624, 752},{0xDE, 0x79, 0x15, 0xFF}}},
	{{{-93, 192, 23},0, {624, 863},{0xB8, 0x51, 0x41, 0xFF}}},
	{{{-2, 213, 56},0, {624, 1008},{0xFB, 0x6C, 0x42, 0xFF}}},
	{{{36, 231, -19},0, {624, 885},{0x1F, 0x7B, 0xC, 0xFF}}},
	{{{-58, 255, -16},0, {624, 1008},{0xDE, 0x79, 0x15, 0xFF}}},
};

Gfx character_Head_mesh_tri_2[] = {
	gsSPVertex(character_Head_mesh_vtx_2 + 0, 7, 0),
	gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
	gsSP2Triangles(2, 3, 4, 0, 4, 5, 6, 0),
	gsSP1Triangle(6, 5, 0, 0),
	gsSPEndDisplayList(),
};Vtx character_Head_mesh_vtx_3[8] = {
	{{{-79, -8, 84},0, {-16, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-45, -8, 84},0, {1008, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-45, 81, 84},0, {1008, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-79, 81, 84},0, {-16, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{39, -17, 85},0, {-16, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{69, -17, 85},0, {1008, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{69, 60, 85},0, {1008, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{39, 60, 85},0, {-16, -16},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx character_Head_mesh_tri_3[] = {
	gsSPVertex(character_Head_mesh_vtx_3 + 0, 8, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
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
	gsSPDisplayList(mat_character_model_black_f3d),
	gsSPDisplayList(character_Head_mesh_tri_3),
	gsSPEndDisplayList(),
};



Vtx character_Torso_mesh_vtx_0[21] = {
	{{{23, -12, -202},0, {64, 16},{0x1A, 0xFD, 0x84, 0xFF}}},
	{{{155, 55, -79},0, {0, 32},{0x62, 0x1F, 0xB6, 0xFF}}},
	{{{93, -113, -84},0, {64, 16},{0x3D, 0xA7, 0xBE, 0xFF}}},
	{{{1, 137, -91},0, {0, 32},{0xF8, 0x64, 0xB3, 0xFF}}},
	{{{-153, -19, -147},0, {64, 16},{0xA4, 0x8, 0xA9, 0xFF}}},
	{{{-114, -140, -117},0, {64, 8},{0xD1, 0x9D, 0xC0, 0xFF}}},
	{{{-58, -159, -37},0, {129, 8},{0xF9, 0x82, 0xF3, 0xFF}}},
	{{{93, -113, -84},0, {129, 8},{0x3D, 0xA7, 0xBE, 0xFF}}},
	{{{-166, -94, 43},0, {64, 8},{0x97, 0xBC, 0x16, 0xFF}}},
	{{{-169, 95, -24},0, {64, 16},{0x9A, 0x49, 0xEE, 0xFF}}},
	{{{-170, 2, 110},0, {64, 8},{0x9B, 0xC, 0x4C, 0xFF}}},
	{{{-80, -112, 131},0, {129, 8},{0xDE, 0xB1, 0x5D, 0xFF}}},
	{{{149, -125, 82},0, {192, 8},{0x4B, 0xA3, 0x2D, 0xFF}}},
	{{{93, -113, -84},0, {192, 8},{0x3D, 0xA7, 0xBE, 0xFF}}},
	{{{138, 12, 157},0, {192, 8},{0x48, 0x3, 0x68, 0xFF}}},
	{{{194, -28, 15},0, {192, 16},{0x7D, 0xEF, 0xF5, 0xFF}}},
	{{{93, -113, -84},0, {192, 16},{0x3D, 0xA7, 0xBE, 0xFF}}},
	{{{128, 185, 14},0, {192, 16},{0x48, 0x68, 0xF7, 0xFF}}},
	{{{93, -113, -84},0, {0, 32},{0x3D, 0xA7, 0xBE, 0xFF}}},
	{{{11, 189, 94},0, {192, 16},{0xEC, 0x78, 0x25, 0xFF}}},
	{{{10, 144, 159},0, {192, 8},{0xF7, 0x43, 0x6B, 0xFF}}},
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
	{{{-109, 38, 126},0, {16, -8},{0xB5, 0xFD, 0x66, 0xFF}}},
	{{{-25, -51, 139},0, {48, -8},{0xEA, 0xB5, 0x64, 0xFF}}},
	{{{-16, 21, 194},0, {16, -8},{0xEE, 0xE8, 0x7B, 0xFF}}},
	{{{78, 33, 153},0, {80, -8},{0x34, 0xF4, 0x73, 0xFF}}},
	{{{-16, 21, 194},0, {48, -8},{0xEE, 0xE8, 0x7B, 0xFF}}},
	{{{49, -33, 146},0, {80, -8},{0xB3, 0xFF, 0x65, 0x0}}},
	{{{41, 106, 157},0, {80, -8},{0x18, 0xC5, 0x6E, 0x0}}},
	{{{-16, 21, 194},0, {80, -8},{0xEE, 0xE8, 0x7B, 0xFF}}},
	{{{-136, -20, 118},0, {48, -8},{0x2F, 0x32, 0x6B, 0x0}}},
	{{{41, 106, 157},0, {16, -8},{0x18, 0xC5, 0x6E, 0x0}}},
	{{{-5, 127, 155},0, {80, -8},{0xF3, 0x2E, 0x76, 0x63}}},
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




BoneLayer character_model_bone2_layers[] = {
    {
        LAYER_OPA_SURF,
        character_Arm_1_mesh,
    },
};
BoneLayer character_model_bone3_layers[] = {
    {
        LAYER_OPA_SURF,
        character_Arm_2_mesh,
    },
};
BoneLayer character_model_bone4_layers[] = {
    {
        LAYER_OPA_SURF,
        character_Hand_mesh,
    },
};
BoneLayer character_model_bone5_layers[] = {
    {
        LAYER_OPA_SURF,
        character_Foot_L_mesh,
    },
};
BoneLayer character_model_bone6_layers[] = {
    {
        LAYER_OPA_SURF,
        character_Foot_R_mesh,
    },
};
BoneLayer character_model_bone7_layers[] = {
    {
        LAYER_OPA_SURF,
        character_Head_mesh,
    },
};
BoneLayer character_model_bone8_layers[] = {
    {
        LAYER_OPA_SURF,
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
        0,
        0,
        0.4741489887237549,
        531.406494140625,
        0.34378305077552795,
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
        -288.0304260253906,
        -27.480363845825195,
        6.726406574249268,
        character_model_bone2_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        3,
        2,
        1,
        0,
        -184.01644897460938,
        0.0,
        0.0,
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
        -190.59024047851562,
        0.0,
        0.0,
        character_model_bone4_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        5,
        0,
        1,
        0,
        156.5800018310547,
        0.8435964584350586,
        -4.6540062612621114e-05,
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
        -156.579833984375,
        0.8435964584350586,
        -4.6540062612621114e-05,
        character_model_bone6_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        7,
        0,
        1,
        0,
        14.750289916992188,
        638.6747436523438,
        18.45511245727539,
        character_model_bone7_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        8,
        0,
        1,
        0,
        0.0,
        342.7220153808594,
        -1.4980852938606404e-05,
        character_model_bone8_layers,
        NULL,
        NULL,
        NULL,
    },
};

Model character_model = {
    9,
    0,
    character_model_bones
};

