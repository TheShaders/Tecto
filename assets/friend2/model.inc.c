
Gfx friend2_model_shading_i4_aligner[] = {gsSPEndDisplayList()};
u8 friend2_model_shading_i4[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xBB, 0x77, 0x77, 
};

Gfx friend2_model_eyecut_I4_i8_aligner[] = {gsSPEndDisplayList()};
u8 friend2_model_eyecut_I4_i8[] = {
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


Gfx mat_friend2_model_base_toon_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, ENVIRONMENT, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, ENVIRONMENT),
	gsSPSetGeometryMode(G_TEXTURE_GEN),
	gsDPSetTextureFilter(G_TF_POINT),
	gsSPTexture(959, 0, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 8, friend2_model_shading_i4),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 30, 0),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 0),
	gsDPSetPrimColor(0, 0, 227, 222, 211, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_friend2_model_base_toon_f3d[] = {
	gsDPPipeSync(),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetTextureFilter(G_TF_BILERP),
	gsSPEndDisplayList(),
};


Gfx mat_friend2_model_eye_decal_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, 0, 0, 0, 0, TEXEL0, 0, 0, 0, 0, 0, 0, 0, TEXEL0),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 8, friend2_model_eyecut_I4_i8),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_WRAP | G_TX_MIRROR, 4, 0, G_TX_WRAP | G_TX_MIRROR, 3, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 28, 60),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 0, 0, G_TX_WRAP | G_TX_MIRROR, 4, 0, G_TX_WRAP | G_TX_MIRROR, 3, 0),
	gsDPSetTileSize(0, 0, 0, 28, 60),
	gsSPEndDisplayList(),
};



Vtx friend2_Foot_L_mesh_vtx_0[17] = {
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

Gfx friend2_Foot_L_mesh_tri_0[] = {
	gsSPVertex(friend2_Foot_L_mesh_vtx_0 + 0, 17, 0),
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

Gfx friend2_Foot_L_mesh[] = {
	gsSPDisplayList(mat_friend2_model_base_toon_f3d),
	gsSPDisplayList(friend2_Foot_L_mesh_tri_0),
	gsSPDisplayList(mat_revert_friend2_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx friend2_Foot_R_mesh_vtx_0[18] = {
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

Gfx friend2_Foot_R_mesh_tri_0[] = {
	gsSPVertex(friend2_Foot_R_mesh_vtx_0 + 0, 18, 0),
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

Gfx friend2_Foot_R_mesh[] = {
	gsSPDisplayList(mat_friend2_model_base_toon_f3d),
	gsSPDisplayList(friend2_Foot_R_mesh_tri_0),
	gsSPDisplayList(mat_revert_friend2_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx friend2_Head_mesh_vtx_0[39] = {
	{{{-26, -15, 16},0, {192, 0},{0x11, 0xA6, 0x57, 0xFF}}},
	{{{-47, 20, 14},0, {320, 0},{0xF0, 0x4F, 0x62, 0xFF}}},
	{{{-47, -11, 14},0, {192, 0},{0xD5, 0xA9, 0x52, 0xFF}}},
	{{{-26, 25, 16},0, {320, 0},{0xCA, 0x4, 0x73, 0xFF}}},
	{{{32, -15, 16},0, {192, 8},{0xA, 0x94, 0x42, 0xFF}}},
	{{{38, 12, 16},0, {320, 8},{0x43, 0x40, 0x56, 0xFF}}},
	{{{31, 25, 10},0, {320, 8},{0x29, 0x4B, 0x5E, 0xFF}}},
	{{{45, 20, -4},0, {320, 16},{0x58, 0x54, 0xDC, 0xFF}}},
	{{{58, 5, -5},0, {320, 16},{0x78, 0xF6, 0xD8, 0xFF}}},
	{{{50, -15, 1},0, {192, 16},{0x5C, 0xAA, 0xF3, 0xFF}}},
	{{{32, -15, 16},0, {192, 8},{0xA, 0x94, 0x42, 0xFF}}},
	{{{13, -15, -34},0, {128, 16},{0x16, 0xA1, 0xAF, 0xFF}}},
	{{{-20, -15, -23},0, {64, 16},{0xB, 0xAE, 0xA0, 0xFF}}},
	{{{-26, -15, 16},0, {64, 8},{0x11, 0xA6, 0x57, 0xFF}}},
	{{{-47, -11, 14},0, {64, 8},{0xD5, 0xA9, 0x52, 0xFF}}},
	{{{-43, -11, -17},0, {64, 16},{0xAC, 0xDA, 0xA9, 0xFF}}},
	{{{-50, -7, 9},0, {102, 11},{0x9F, 0xCC, 0x3F, 0xFF}}},
	{{{-50, 15, 9},0, {282, 22},{0x90, 0x3B, 0xC, 0xFF}}},
	{{{-47, 20, 14},0, {320, 24},{0xF0, 0x4F, 0x62, 0xFF}}},
	{{{-47, 15, -13},0, {282, 23},{0x9C, 0x2B, 0xBF, 0xFF}}},
	{{{-43, 20, -17},0, {320, 24},{0xD0, 0x35, 0x97, 0xFF}}},
	{{{-20, 33, 9},0, {320, 24},{0x1B, 0x7C, 0xFF, 0xFF}}},
	{{{-17, 33, -15},0, {320, 24},{0xD7, 0x74, 0xE1, 0xFF}}},
	{{{-20, 25, -23},0, {320, 24},{0xCA, 0x1B, 0x90, 0xFF}}},
	{{{17, 15, -37},0, {320, 20},{0x16, 0x10, 0x84, 0xFF}}},
	{{{17, 27, -26},0, {320, 20},{0x2F, 0x65, 0xC3, 0xFF}}},
	{{{-20, 33, 9},0, {320, 0},{0x1B, 0x7C, 0xFF, 0xFF}}},
	{{{13, -15, -34},0, {192, 20},{0x16, 0xA1, 0xAF, 0xFF}}},
	{{{-20, -15, -23},0, {192, 24},{0xB, 0xAE, 0xA0, 0xFF}}},
	{{{-43, -11, -17},0, {192, 24},{0xAC, 0xDA, 0xA9, 0xFF}}},
	{{{-69, 4, -2},0, {102, 11},{0xB3, 0xB4, 0x42, 0xFF}}},
	{{{-69, 4, -2},0, {282, 22},{0xB3, 0xB4, 0x42, 0xFF}}},
	{{{-47, 15, -13},0, {282, 23},{0x9C, 0x2B, 0xBF, 0xFF}}},
	{{{-47, -7, -13},0, {102, 16},{0xA5, 0xE1, 0xAD, 0xFF}}},
	{{{-69, 4, -2},0, {282, 23},{0xB3, 0xB4, 0x42, 0xFF}}},
	{{{-43, 20, -17},0, {320, 24},{0xD0, 0x35, 0x97, 0xFF}}},
	{{{-43, -11, -17},0, {64, 16},{0xAC, 0xDA, 0xA9, 0xFF}}},
	{{{-50, -7, 9},0, {102, 11},{0x9F, 0xCC, 0x3F, 0xFF}}},
	{{{-69, 4, -2},0, {102, 16},{0xB3, 0xB4, 0x42, 0xFF}}},
};

Gfx friend2_Head_mesh_tri_0[] = {
	gsSPVertex(friend2_Head_mesh_vtx_0 + 0, 32, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(4, 3, 0, 0, 4, 5, 3, 0),
	gsSP2Triangles(3, 5, 6, 0, 5, 7, 6, 0),
	gsSP2Triangles(5, 8, 7, 0, 9, 8, 5, 0),
	gsSP2Triangles(9, 5, 10, 0, 11, 9, 10, 0),
	gsSP2Triangles(12, 11, 10, 0, 12, 10, 13, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 15, 14, 0, 17, 16, 14, 0),
	gsSP2Triangles(17, 14, 18, 0, 19, 17, 18, 0),
	gsSP2Triangles(19, 18, 20, 0, 20, 18, 21, 0),
	gsSP2Triangles(20, 21, 22, 0, 23, 20, 22, 0),
	gsSP2Triangles(24, 23, 22, 0, 24, 22, 25, 0),
	gsSP2Triangles(26, 25, 22, 0, 26, 6, 25, 0),
	gsSP2Triangles(3, 6, 26, 0, 1, 3, 26, 0),
	gsSP2Triangles(6, 7, 25, 0, 8, 25, 7, 0),
	gsSP2Triangles(8, 24, 25, 0, 27, 24, 8, 0),
	gsSP2Triangles(27, 8, 9, 0, 28, 24, 27, 0),
	gsSP2Triangles(28, 23, 24, 0, 23, 28, 29, 0),
	gsSP2Triangles(23, 29, 20, 0, 16, 17, 30, 0),
	gsSP1Triangle(17, 19, 31, 0),
	gsSPVertex(friend2_Head_mesh_vtx_0 + 32, 7, 0),
	gsSP2Triangles(0, 1, 2, 0, 1, 0, 3, 0),
	gsSP2Triangles(1, 3, 4, 0, 5, 1, 4, 0),
	gsSP1Triangle(1, 5, 6, 0),
	gsSPEndDisplayList(),
};

Gfx friend2_Head_mesh[] = {
	gsSPDisplayList(mat_friend2_model_base_toon_f3d),
	gsSPDisplayList(friend2_Head_mesh_tri_0),
	gsSPDisplayList(mat_revert_friend2_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx friend2_Eye_L_mesh_vtx_0[4] = {
	{{{-5, -13, 0},0, {-16, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{5, -13, 0},0, {496, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{5, 13, 0},0, {496, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-5, 13, 0},0, {-16, -16},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx friend2_Eye_L_mesh_tri_0[] = {
	gsSPVertex(friend2_Eye_L_mesh_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx friend2_Eye_L_mesh[] = {
	gsSPDisplayList(mat_friend2_model_eye_decal_f3d),
	gsSPDisplayList(friend2_Eye_L_mesh_tri_0),
	gsSPEndDisplayList(),
};



Vtx friend2_Eye_R_mesh_vtx_0[4] = {
	{{{-5, -13, 0},0, {-16, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{5, -13, 0},0, {496, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{5, 12, 0},0, {496, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-5, 12, 0},0, {-16, -16},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx friend2_Eye_R_mesh_tri_0[] = {
	gsSPVertex(friend2_Eye_R_mesh_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx friend2_Eye_R_mesh[] = {
	gsSPDisplayList(mat_friend2_model_eye_decal_f3d),
	gsSPDisplayList(friend2_Eye_R_mesh_tri_0),
	gsSPEndDisplayList(),
};



Vtx friend2_Torso_mesh_vtx_0[29] = {
	{{{3, 28, 26},0, {128, 12},{0xF4, 0x5D, 0x55, 0xFF}}},
	{{{4, 46, 7},0, {128, 8},{0x34, 0x72, 0x14, 0xFF}}},
	{{{-40, 18, 8},0, {0, 12},{0xC1, 0x17, 0x6C, 0xFF}}},
	{{{45, 49, 19},0, {256, 12},{0x65, 0x47, 0x1E, 0xFF}}},
	{{{43, 6, 5},0, {256, 16},{0x7D, 0xEC, 0xFC, 0xFF}}},
	{{{13, 6, 45},0, {128, 16},{0xC2, 0x29, 0x67, 0xFF}}},
	{{{-40, 18, 8},0, {0, 16},{0xC1, 0x17, 0x6C, 0xFF}}},
	{{{-22, -4, 37},0, {128, 16},{0x29, 0x5C, 0x4D, 0xFF}}},
	{{{42, -15, 9},0, {256, 20},{0x72, 0xC9, 0xF7, 0xFF}}},
	{{{-7, -14, -35},0, {384, 20},{0xF4, 0xCE, 0x8C, 0xFF}}},
	{{{-10, -40, -11},0, {384, 24},{0xE9, 0x99, 0xB9, 0xFF}}},
	{{{33, -32, 13},0, {256, 24},{0x4E, 0x9D, 0x11, 0xFF}}},
	{{{7, -21, 37},0, {128, 24},{0x52, 0xC9, 0x4F, 0xFF}}},
	{{{15, -40, 13},0, {256, 28},{0x46, 0x99, 0x19, 0xFF}}},
	{{{0, -48, 16},0, {128, 28},{0xF6, 0x82, 0x8, 0xFF}}},
	{{{-24, -33, 12},0, {0, 24},{0xAC, 0xAC, 0x2F, 0xFF}}},
	{{{0, -48, 16},0, {384, 28},{0xF6, 0x82, 0x8, 0xFF}}},
	{{{-40, 18, 8},0, {512, 12},{0xC1, 0x17, 0x6C, 0xFF}}},
	{{{4, 46, 7},0, {384, 12},{0x34, 0x72, 0x14, 0xFF}}},
	{{{10, 27, -34},0, {384, 16},{0x5F, 0x5, 0xAB, 0xFF}}},
	{{{-40, 18, 8},0, {512, 16},{0xC1, 0x17, 0x6C, 0xFF}}},
	{{{-38, -15, 14},0, {512, 20},{0xB1, 0x18, 0x60, 0xFF}}},
	{{{-24, -33, 12},0, {512, 24},{0xAC, 0xAC, 0x2F, 0xFF}}},
	{{{0, -48, 16},0, {512, 28},{0xF6, 0x82, 0x8, 0xFF}}},
	{{{-22, -4, 37},0, {512, 16},{0x29, 0x5C, 0x4D, 0xFF}}},
	{{{7, -21, 37},0, {128, 20},{0x52, 0xC9, 0x4F, 0xFF}}},
	{{{-22, -4, 37},0, {128, 20},{0x29, 0x5C, 0x4D, 0xFF}}},
	{{{-38, -15, 14},0, {0, 20},{0xB1, 0x18, 0x60, 0xFF}}},
	{{{-22, -4, 37},0, {0, 20},{0x29, 0x5C, 0x4D, 0xFF}}},
};

Gfx friend2_Torso_mesh_tri_0[] = {
	gsSPVertex(friend2_Torso_mesh_vtx_0 + 0, 29, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
	gsSP2Triangles(4, 3, 0, 0, 4, 0, 5, 0),
	gsSP2Triangles(5, 0, 6, 0, 5, 6, 7, 0),
	gsSP2Triangles(8, 4, 5, 0, 9, 4, 8, 0),
	gsSP2Triangles(10, 9, 8, 0, 10, 8, 11, 0),
	gsSP2Triangles(11, 8, 12, 0, 13, 11, 12, 0),
	gsSP2Triangles(13, 12, 14, 0, 14, 12, 15, 0),
	gsSP2Triangles(10, 11, 13, 0, 16, 10, 13, 0),
	gsSP2Triangles(17, 18, 19, 0, 19, 18, 3, 0),
	gsSP2Triangles(19, 3, 4, 0, 9, 19, 4, 0),
	gsSP2Triangles(9, 20, 19, 0, 9, 21, 20, 0),
	gsSP2Triangles(22, 21, 9, 0, 22, 9, 10, 0),
	gsSP2Triangles(23, 22, 10, 0, 20, 21, 24, 0),
	gsSP2Triangles(8, 5, 25, 0, 25, 5, 26, 0),
	gsSP2Triangles(27, 25, 28, 0, 25, 27, 15, 0),
	gsSPEndDisplayList(),
};

Gfx friend2_Torso_mesh[] = {
	gsSPDisplayList(mat_friend2_model_base_toon_f3d),
	gsSPDisplayList(friend2_Torso_mesh_tri_0),
	gsSPDisplayList(mat_revert_friend2_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx friend2_Torso2_mesh_vtx_0[22] = {
	{{{1, -12, 1},0, {419, 32},{0x14, 0x83, 0xFC, 0xFF}}},
	{{{46, -5, -16},0, {372, 27},{0x71, 0xC8, 0xF2, 0xFF}}},
	{{{17, -11, 35},0, {465, 27},{0x44, 0xBB, 0x51, 0xFF}}},
	{{{34, 19, 13},0, {419, 22},{0x59, 0x49, 0x36, 0xFF}}},
	{{{34, 20, -36},0, {326, 22},{0x40, 0x4B, 0xAF, 0xFF}}},
	{{{17, -8, -43},0, {279, 27},{0xC, 0xBB, 0x96, 0xFF}}},
	{{{1, -12, 1},0, {326, 32},{0x14, 0x83, 0xFC, 0xFF}}},
	{{{-14, 13, -31},0, {233, 22},{0xB9, 0x35, 0xA5, 0xFF}}},
	{{{-31, -17, -8},0, {186, 27},{0xB3, 0xA8, 0xCD, 0xFF}}},
	{{{1, -12, 1},0, {233, 32},{0x14, 0x83, 0xFC, 0xFF}}},
	{{{-43, 7, 20},0, {140, 22},{0x8A, 0x2C, 0x10, 0xFF}}},
	{{{-30, -18, 40},0, {93, 27},{0xC5, 0xAC, 0x4C, 0xFF}}},
	{{{1, -12, 1},0, {140, 32},{0x14, 0x83, 0xFC, 0xFF}}},
	{{{-13, 10, 47},0, {47, 22},{0xF4, 0x39, 0x71, 0xFF}}},
	{{{17, -11, 35},0, {0, 27},{0x44, 0xBB, 0x51, 0xFF}}},
	{{{1, -12, 1},0, {47, 32},{0x14, 0x83, 0xFC, 0xFF}}},
	{{{-3, 30, 3},0, {93, 17},{0xEC, 0x7D, 0x4, 0xFF}}},
	{{{-3, 30, 3},0, {372, 17},{0xEC, 0x7D, 0x4, 0xFF}}},
	{{{-3, 30, 3},0, {186, 17},{0xEC, 0x7D, 0x4, 0xFF}}},
	{{{-3, 30, 3},0, {279, 17},{0xEC, 0x7D, 0x4, 0xFF}}},
	{{{-13, 10, 47},0, {512, 22},{0xF4, 0x39, 0x71, 0xFF}}},
	{{{-3, 30, 3},0, {465, 17},{0xEC, 0x7D, 0x4, 0xFF}}},
};

Gfx friend2_Torso2_mesh_tri_0[] = {
	gsSPVertex(friend2_Torso2_mesh_vtx_0 + 0, 22, 0),
	gsSP2Triangles(0, 1, 2, 0, 2, 1, 3, 0),
	gsSP2Triangles(1, 4, 3, 0, 1, 5, 4, 0),
	gsSP2Triangles(1, 6, 5, 0, 5, 7, 4, 0),
	gsSP2Triangles(5, 8, 7, 0, 9, 8, 5, 0),
	gsSP2Triangles(8, 10, 7, 0, 8, 11, 10, 0),
	gsSP2Triangles(12, 11, 8, 0, 11, 13, 10, 0),
	gsSP2Triangles(11, 14, 13, 0, 15, 14, 11, 0),
	gsSP2Triangles(10, 13, 16, 0, 3, 4, 17, 0),
	gsSP2Triangles(7, 10, 18, 0, 4, 7, 19, 0),
	gsSP2Triangles(2, 3, 20, 0, 20, 3, 21, 0),
	gsSPEndDisplayList(),
};

Gfx friend2_Torso2_mesh[] = {
	gsSPDisplayList(mat_friend2_model_base_toon_f3d),
	gsSPDisplayList(friend2_Torso2_mesh_tri_0),
	gsSPDisplayList(mat_revert_friend2_model_base_toon_f3d),
	gsSPEndDisplayList(),
};




BoneLayer friend2_model_bone1_layers[] = {
    {
        LAYER_OPA_SURF,
        friend2_Foot_L_mesh,
    },
};
BoneLayer friend2_model_bone2_layers[] = {
    {
        LAYER_OPA_SURF,
        friend2_Foot_R_mesh,
    },
};
BoneLayer friend2_model_bone3_layers[] = {
    {
        LAYER_OPA_SURF,
        friend2_Head_mesh,
    },
};
BoneLayer friend2_model_bone4_layers[] = {
    {
        LAYER_TEX_EDGE,
        friend2_Eye_L_mesh,
    },
};
BoneLayer friend2_model_bone5_layers[] = {
    {
        LAYER_TEX_EDGE,
        friend2_Eye_R_mesh,
    },
};
BoneLayer friend2_model_bone6_layers[] = {
    {
        LAYER_OPA_SURF,
        friend2_Torso_mesh,
    },
};
BoneLayer friend2_model_bone7_layers[] = {
    {
        LAYER_OPA_SURF,
        friend2_Torso2_mesh,
    },
};

Bone friend2_model_bones[] = {
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
        friend2_model_bone1_layers,
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
        friend2_model_bone2_layers,
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
        177.73495483398438,
        3.6910202503204346,
        friend2_model_bone3_layers,
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
        4.263954162597656,
        18.17925453186035,
        friend2_model_bone4_layers,
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
        4.202079772949219,
        18.177051544189453,
        friend2_model_bone5_layers,
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
        friend2_model_bone6_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        7,
        0,
        1,
        0,
        0.0,
        131.52825927734375,
        -5.749283445766196e-06,
        friend2_model_bone7_layers,
        NULL,
        NULL,
        NULL,
    },
};

Model friend2_model = {
    8,
    0,
    friend2_model_bones
};

