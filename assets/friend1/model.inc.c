
Gfx friend1_model_shading_i4_aligner[] = {gsSPEndDisplayList()};
u8 friend1_model_shading_i4[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xBB, 0x77, 0x77, 
};

Gfx friend1_model_eyecut_I4_i8_aligner[] = {gsSPEndDisplayList()};
u8 friend1_model_eyecut_I4_i8[] = {
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


Gfx mat_friend1_model_base_toon_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, ENVIRONMENT, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, ENVIRONMENT),
	gsSPSetGeometryMode(G_TEXTURE_GEN),
	gsDPSetTextureFilter(G_TF_POINT),
	gsSPTexture(959, 0, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 8, friend1_model_shading_i4),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 30, 0),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 0),
	gsDPSetPrimColor(0, 0, 227, 222, 211, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_friend1_model_base_toon_f3d[] = {
	gsDPPipeSync(),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetTextureFilter(G_TF_BILERP),
	gsSPEndDisplayList(),
};


Gfx mat_friend1_model_eye_decal_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, 0, 0, 0, 0, TEXEL0, 0, 0, 0, 0, 0, 0, 0, TEXEL0),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 8, friend1_model_eyecut_I4_i8),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_WRAP | G_TX_MIRROR, 4, 0, G_TX_WRAP | G_TX_MIRROR, 3, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 28, 60),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 0, 0, G_TX_WRAP | G_TX_MIRROR, 4, 0, G_TX_WRAP | G_TX_MIRROR, 3, 0),
	gsDPSetTileSize(0, 0, 0, 28, 60),
	gsSPEndDisplayList(),
};



Vtx friend1_Arm_1_mesh_vtx_0[16] = {
	{{{-17, 7, 25},0, {320, 32},{0xB8, 0x1C, 0x65, 0xFF}}},
	{{{-11, -22, 11},0, {192, 24},{0xDB, 0x93, 0x35, 0xFF}}},
	{{{13, -6, 23},0, {192, 32},{0x3E, 0xD4, 0x66, 0xFF}}},
	{{{-27, -8, -14},0, {320, 24},{0x93, 0xDF, 0xC8, 0xFF}}},
	{{{-13, 26, -7},0, {320, 24},{0xC6, 0x6D, 0xE3, 0xFF}}},
	{{{3, -22, -16},0, {192, 16},{0x14, 0x93, 0xC2, 0xFF}}},
	{{{11, 8, -29},0, {320, 16},{0x29, 0x1F, 0x8C, 0xFF}}},
	{{{-13, 26, -7},0, {320, 16},{0xC6, 0x6D, 0xE3, 0xFF}}},
	{{{27, -6, -4},0, {192, 8},{0x76, 0xD4, 0xF3, 0xFF}}},
	{{{20, 23, 10},0, {320, 8},{0x4D, 0x5C, 0x2A, 0xFF}}},
	{{{-13, 26, -7},0, {320, 8},{0xC6, 0x6D, 0xE3, 0xFF}}},
	{{{13, -6, 23},0, {192, 0},{0x3E, 0xD4, 0x66, 0xFF}}},
	{{{-17, 7, 25},0, {320, 0},{0xB8, 0x1C, 0x65, 0xFF}}},
	{{{-13, 26, -7},0, {320, 0},{0xC6, 0x6D, 0xE3, 0xFF}}},
	{{{13, -6, 23},0, {64, 8},{0x3E, 0xD4, 0x66, 0xFF}}},
	{{{-11, -22, 11},0, {64, 16},{0xDB, 0x93, 0x35, 0xFF}}},
};

Gfx friend1_Arm_1_mesh_tri_0[] = {
	gsSPVertex(friend1_Arm_1_mesh_vtx_0 + 0, 16, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(3, 0, 4, 0, 3, 5, 1, 0),
	gsSP2Triangles(3, 6, 5, 0, 6, 3, 7, 0),
	gsSP2Triangles(6, 8, 5, 0, 6, 9, 8, 0),
	gsSP2Triangles(9, 6, 10, 0, 9, 11, 8, 0),
	gsSP2Triangles(9, 12, 11, 0, 12, 9, 13, 0),
	gsSP2Triangles(5, 14, 15, 0, 5, 8, 14, 0),
	gsSPEndDisplayList(),
};

Gfx friend1_Arm_1_mesh[] = {
	gsSPDisplayList(mat_friend1_model_base_toon_f3d),
	gsSPDisplayList(friend1_Arm_1_mesh_tri_0),
	gsSPDisplayList(mat_revert_friend1_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx friend1_Arm_2_mesh_vtx_0[14] = {
	{{{-2, 18, -9},0, {192, 16},{0x1, 0x7C, 0xE3, 0xFF}}},
	{{{12, 9, -3},0, {192, 8},{0x6F, 0x3C, 0x12, 0xFF}}},
	{{{5, 5, -19},0, {64, 8},{0x34, 0x1F, 0x90, 0xFF}}},
	{{{-7, 7, 13},0, {320, 16},{0xEE, 0x30, 0x74, 0xFF}}},
	{{{-24, 6, -8},0, {320, 24},{0x88, 0x1B, 0xE0, 0xFF}}},
	{{{5, 5, -19},0, {192, 24},{0x34, 0x1F, 0x90, 0xFF}}},
	{{{0, -9, -19},0, {320, 32},{0x6, 0xB6, 0x99, 0xFF}}},
	{{{-12, -13, 7},0, {320, 24},{0xC6, 0xA1, 0x3D, 0xFF}}},
	{{{-12, -13, 7},0, {320, 16},{0xC6, 0xA1, 0x3D, 0xFF}}},
	{{{0, -9, -19},0, {320, 0},{0x6, 0xB6, 0x99, 0xFF}}},
	{{{12, -12, 2},0, {320, 8},{0x5E, 0xB3, 0x24, 0xFF}}},
	{{{-12, -13, 7},0, {320, 0},{0xC6, 0xA1, 0x3D, 0xFF}}},
	{{{5, 5, -19},0, {192, 0},{0x34, 0x1F, 0x90, 0xFF}}},
	{{{-12, -13, 7},0, {320, 8},{0xC6, 0xA1, 0x3D, 0xFF}}},
};

Gfx friend1_Arm_2_mesh_tri_0[] = {
	gsSPVertex(friend1_Arm_2_mesh_vtx_0 + 0, 14, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
	gsSP2Triangles(4, 3, 0, 0, 4, 0, 5, 0),
	gsSP2Triangles(6, 4, 5, 0, 4, 6, 7, 0),
	gsSP2Triangles(3, 4, 8, 0, 9, 10, 11, 0),
	gsSP2Triangles(10, 9, 12, 0, 10, 12, 1, 0),
	gsSP2Triangles(3, 10, 1, 0, 10, 3, 13, 0),
	gsSPEndDisplayList(),
};

Gfx friend1_Arm_2_mesh[] = {
	gsSPDisplayList(mat_friend1_model_base_toon_f3d),
	gsSPDisplayList(friend1_Arm_2_mesh_tri_0),
	gsSPDisplayList(mat_revert_friend1_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx friend1_Arm2_1_mesh_vtx_0[16] = {
	{{{16, -3, -27},0, {320, 32},{0x47, 0xB, 0x97, 0xFF}}},
	{{{11, -28, -8},0, {192, 24},{0x2C, 0x8D, 0xE3, 0xFF}}},
	{{{-13, -17, -23},0, {192, 32},{0xC6, 0xBC, 0xA6, 0xFF}}},
	{{{26, -9, 14},0, {320, 24},{0x6E, 0xF3, 0x3D, 0xFF}}},
	{{{11, 23, 0},0, {320, 24},{0x33, 0x74, 0x5, 0xFF}}},
	{{{-2, -24, 19},0, {192, 16},{0xF3, 0xA1, 0x53, 0xFF}}},
	{{{-12, 8, 26},0, {320, 16},{0xD4, 0x34, 0x6C, 0xFF}}},
	{{{11, 23, 0},0, {320, 16},{0x33, 0x74, 0x5, 0xFF}}},
	{{{-27, -12, 4},0, {192, 8},{0x8D, 0xD0, 0x17, 0xFF}}},
	{{{-22, 14, -16},0, {320, 8},{0xAD, 0x4C, 0xC5, 0xFF}}},
	{{{11, 23, 0},0, {320, 8},{0x33, 0x74, 0x5, 0xFF}}},
	{{{-13, -17, -23},0, {192, 0},{0xC6, 0xBC, 0xA6, 0xFF}}},
	{{{16, -3, -27},0, {320, 0},{0x47, 0xB, 0x97, 0xFF}}},
	{{{11, 23, 0},0, {320, 0},{0x33, 0x74, 0x5, 0xFF}}},
	{{{-13, -17, -23},0, {64, 8},{0xC6, 0xBC, 0xA6, 0xFF}}},
	{{{11, -28, -8},0, {64, 16},{0x2C, 0x8D, 0xE3, 0xFF}}},
};

Gfx friend1_Arm2_1_mesh_tri_0[] = {
	gsSPVertex(friend1_Arm2_1_mesh_vtx_0 + 0, 16, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(3, 0, 4, 0, 3, 5, 1, 0),
	gsSP2Triangles(3, 6, 5, 0, 6, 3, 7, 0),
	gsSP2Triangles(6, 8, 5, 0, 6, 9, 8, 0),
	gsSP2Triangles(9, 6, 10, 0, 9, 11, 8, 0),
	gsSP2Triangles(9, 12, 11, 0, 12, 9, 13, 0),
	gsSP2Triangles(5, 14, 15, 0, 5, 8, 14, 0),
	gsSPEndDisplayList(),
};

Gfx friend1_Arm2_1_mesh[] = {
	gsSPDisplayList(mat_friend1_model_base_toon_f3d),
	gsSPDisplayList(friend1_Arm2_1_mesh_tri_0),
	gsSPDisplayList(mat_revert_friend1_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx friend1_Arm2_2_mesh_vtx_0[14] = {
	{{{-1, 12, 0},0, {192, 16},{0xF7, 0x7F, 0x2, 0xFF}}},
	{{{-15, 1, -3},0, {192, 8},{0x8E, 0x2F, 0xE3, 0xFF}}},
	{{{-8, 1, 13},0, {64, 8},{0xC9, 0x32, 0x67, 0xFF}}},
	{{{5, -3, -19},0, {320, 16},{0x10, 0x17, 0x84, 0xFF}}},
	{{{21, 2, 2},0, {320, 24},{0x76, 0x29, 0x19, 0xFF}}},
	{{{-8, 1, 13},0, {192, 24},{0xC9, 0x32, 0x67, 0xFF}}},
	{{{-2, -12, 16},0, {320, 32},{0xFE, 0xCD, 0x74, 0xFF}}},
	{{{10, -21, -8},0, {320, 24},{0x40, 0x9A, 0xD8, 0xFF}}},
	{{{10, -21, -8},0, {320, 16},{0x40, 0x9A, 0xD8, 0xFF}}},
	{{{-2, -12, 16},0, {320, 0},{0xFE, 0xCD, 0x74, 0xFF}}},
	{{{-14, -20, -3},0, {320, 8},{0xA7, 0xA7, 0xEE, 0xFF}}},
	{{{10, -21, -8},0, {320, 0},{0x40, 0x9A, 0xD8, 0xFF}}},
	{{{-8, 1, 13},0, {192, 0},{0xC9, 0x32, 0x67, 0xFF}}},
	{{{10, -21, -8},0, {320, 8},{0x40, 0x9A, 0xD8, 0xFF}}},
};

Gfx friend1_Arm2_2_mesh_tri_0[] = {
	gsSPVertex(friend1_Arm2_2_mesh_vtx_0 + 0, 14, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
	gsSP2Triangles(4, 3, 0, 0, 4, 0, 5, 0),
	gsSP2Triangles(6, 4, 5, 0, 4, 6, 7, 0),
	gsSP2Triangles(3, 4, 8, 0, 9, 10, 11, 0),
	gsSP2Triangles(10, 9, 12, 0, 10, 12, 1, 0),
	gsSP2Triangles(3, 10, 1, 0, 10, 3, 13, 0),
	gsSPEndDisplayList(),
};

Gfx friend1_Arm2_2_mesh[] = {
	gsSPDisplayList(mat_friend1_model_base_toon_f3d),
	gsSPDisplayList(friend1_Arm2_2_mesh_tri_0),
	gsSPDisplayList(mat_revert_friend1_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx friend1_Hand_mesh_vtx_0[22] = {
	{{{-7, -33, 4},0, {419, 32},{0x0, 0x81, 0x0, 0xFF}}},
	{{{22, -15, 5},0, {372, 27},{0x71, 0xC7, 0x6, 0xFF}}},
	{{{1, -15, 31},0, {465, 27},{0x1E, 0xC8, 0x6E, 0xFF}}},
	{{{15, 14, 22},0, {419, 22},{0x58, 0x39, 0x48, 0xFF}}},
	{{{17, 14, -12},0, {326, 22},{0x5F, 0x38, 0xC2, 0xFF}}},
	{{{3, -15, -23},0, {279, 27},{0x29, 0xC7, 0x96, 0xFF}}},
	{{{-7, -33, 4},0, {326, 32},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-14, 14, -24},0, {233, 22},{0xE2, 0x38, 0x92, 0xFF}}},
	{{{-29, -15, -14},0, {186, 27},{0xA8, 0xC7, 0xB8, 0xFF}}},
	{{{-7, -33, 4},0, {233, 32},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-35, 14, 2},0, {140, 22},{0x8F, 0x39, 0xFA, 0xFF}}},
	{{{-31, -15, 19},0, {93, 27},{0xA1, 0xC8, 0x3E, 0xFF}}},
	{{{-7, -33, 4},0, {140, 32},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-17, 14, 30},0, {47, 22},{0xD7, 0x39, 0x6A, 0xFF}}},
	{{{1, -15, 31},0, {0, 27},{0x1E, 0xC8, 0x6E, 0xFF}}},
	{{{-7, -33, 4},0, {47, 32},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-7, 31, 4},0, {93, 17},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-7, 31, 4},0, {372, 17},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-7, 31, 4},0, {186, 17},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-7, 31, 4},0, {279, 17},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-17, 14, 30},0, {512, 22},{0xD7, 0x39, 0x6A, 0xFF}}},
	{{{-7, 31, 4},0, {465, 17},{0x0, 0x7F, 0x0, 0xFF}}},
};

Gfx friend1_Hand_mesh_tri_0[] = {
	gsSPVertex(friend1_Hand_mesh_vtx_0 + 0, 22, 0),
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

Gfx friend1_Hand_mesh[] = {
	gsSPDisplayList(mat_friend1_model_base_toon_f3d),
	gsSPDisplayList(friend1_Hand_mesh_tri_0),
	gsSPDisplayList(mat_revert_friend1_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx friend1_Hand2_mesh_vtx_0[22] = {
	{{{7, -40, 2},0, {419, 32},{0x8, 0x84, 0x1A, 0xFF}}},
	{{{-22, -25, -3},0, {372, 27},{0x93, 0xC0, 0x7, 0xFF}}},
	{{{-1, -29, -28},0, {465, 27},{0xE7, 0xB0, 0xA1, 0xFF}}},
	{{{-18, 0, -25},0, {419, 22},{0xA5, 0x22, 0xAF, 0xFF}}},
	{{{-20, 7, 8},0, {326, 22},{0x9D, 0x3E, 0x32, 0xFF}}},
	{{{-4, -18, 25},0, {279, 27},{0xDA, 0xDC, 0x74, 0xFF}}},
	{{{7, -40, 2},0, {326, 32},{0x8, 0x84, 0x1A, 0xFF}}},
	{{{12, 11, 20},0, {233, 22},{0x19, 0x50, 0x5F, 0xFF}}},
	{{{28, -18, 16},0, {186, 27},{0x5B, 0xDE, 0x51, 0xFF}}},
	{{{7, -40, 2},0, {233, 32},{0x8, 0x84, 0x1A, 0xFF}}},
	{{{33, 7, -6},0, {140, 22},{0x6D, 0x40, 0xF9, 0xFF}}},
	{{{30, -25, -17},0, {93, 27},{0x63, 0xC2, 0xCE, 0xFF}}},
	{{{7, -40, 2},0, {140, 32},{0x8, 0x84, 0x1A, 0xFF}}},
	{{{15, 0, -34},0, {47, 22},{0x26, 0x24, 0x8C, 0xFF}}},
	{{{-1, -29, -28},0, {0, 27},{0xE7, 0xB0, 0xA1, 0xFF}}},
	{{{7, -40, 2},0, {47, 32},{0x8, 0x84, 0x1A, 0xFF}}},
	{{{3, 22, -11},0, {93, 17},{0xF8, 0x7C, 0xE6, 0xFF}}},
	{{{3, 22, -11},0, {372, 17},{0xF8, 0x7C, 0xE6, 0xFF}}},
	{{{3, 22, -11},0, {186, 17},{0xF8, 0x7C, 0xE6, 0xFF}}},
	{{{3, 22, -11},0, {279, 17},{0xF8, 0x7C, 0xE6, 0xFF}}},
	{{{15, 0, -34},0, {512, 22},{0x26, 0x24, 0x8C, 0xFF}}},
	{{{3, 22, -11},0, {465, 17},{0xF8, 0x7C, 0xE6, 0xFF}}},
};

Gfx friend1_Hand2_mesh_tri_0[] = {
	gsSPVertex(friend1_Hand2_mesh_vtx_0 + 0, 22, 0),
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

Gfx friend1_Hand2_mesh[] = {
	gsSPDisplayList(mat_friend1_model_base_toon_f3d),
	gsSPDisplayList(friend1_Hand2_mesh_tri_0),
	gsSPDisplayList(mat_revert_friend1_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx friend1_Foot_L_mesh_vtx_0[17] = {
	{{{3, 18, 24},0, {320, 32},{0xFE, 0x42, 0x6C, 0xFF}}},
	{{{23, 0, 17},0, {192, 32},{0x69, 0xC9, 0x2E, 0xFF}}},
	{{{13, 25, 0},0, {320, 32},{0x53, 0x59, 0xDC, 0xFF}}},
	{{{15, 0, -1},0, {192, 24},{0x4C, 0xB2, 0xC0, 0xFF}}},
	{{{-3, 25, -11},0, {320, 24},{0xF9, 0x51, 0x9F, 0xFF}}},
	{{{-6, 0, -14},0, {192, 16},{0xEA, 0xBC, 0x97, 0xFF}}},
	{{{-17, 25, 4},0, {320, 16},{0xA0, 0x50, 0x13, 0xFF}}},
	{{{-21, 0, 4},0, {192, 12},{0x93, 0xC0, 0xA, 0xFF}}},
	{{{23, 0, 17},0, {64, 8},{0x69, 0xC9, 0x2E, 0xFF}}},
	{{{15, 0, -1},0, {64, 16},{0x4C, 0xB2, 0xC0, 0xFF}}},
	{{{1, 0, 24},0, {192, 8},{0xE8, 0xB5, 0x63, 0xFF}}},
	{{{3, 18, 24},0, {320, 8},{0xFE, 0x42, 0x6C, 0xFF}}},
	{{{23, 0, 17},0, {192, 0},{0x69, 0xC9, 0x2E, 0xFF}}},
	{{{-4, 25, 11},0, {320, 8},{0xDE, 0x6A, 0x3D, 0xFF}}},
	{{{13, 25, 0},0, {448, 8},{0x53, 0x59, 0xDC, 0xFF}}},
	{{{3, 18, 24},0, {448, 8},{0xFE, 0x42, 0x6C, 0xFF}}},
	{{{-3, 25, -11},0, {448, 16},{0xF9, 0x51, 0x9F, 0xFF}}},
};

Gfx friend1_Foot_L_mesh_tri_0[] = {
	gsSPVertex(friend1_Foot_L_mesh_vtx_0 + 0, 17, 0),
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

Gfx friend1_Foot_L_mesh[] = {
	gsSPDisplayList(mat_friend1_model_base_toon_f3d),
	gsSPDisplayList(friend1_Foot_L_mesh_tri_0),
	gsSPDisplayList(mat_revert_friend1_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx friend1_Foot_R_mesh_vtx_0[18] = {
	{{{-6, 25, -21},0, {320, 16},{0xCE, 0x46, 0xA3, 0xFF}}},
	{{{17, 25, 4},0, {448, 8},{0x53, 0x5F, 0xC, 0xFF}}},
	{{{8, 25, -14},0, {448, 16},{0x41, 0x56, 0xBE, 0xFF}}},
	{{{-8, 25, 3},0, {320, 8},{0xB9, 0x66, 0x19, 0xFF}}},
	{{{-15, 0, -2},0, {192, 12},{0x99, 0xB8, 0xF0, 0xFF}}},
	{{{3, 0, -19},0, {192, 16},{0xC, 0xB1, 0x9E, 0xFF}}},
	{{{8, 25, -14},0, {320, 24},{0x41, 0x56, 0xBE, 0xFF}}},
	{{{19, 0, -2},0, {192, 24},{0x63, 0xB5, 0xE3, 0xFF}}},
	{{{17, 25, 4},0, {320, 32},{0x53, 0x5F, 0xC, 0xFF}}},
	{{{16, 18, 15},0, {320, 32},{0x4B, 0x43, 0x4D, 0xFF}}},
	{{{14, 0, 24},0, {192, 32},{0x3B, 0xC8, 0x61, 0xFF}}},
	{{{14, 0, 24},0, {64, 8},{0x3B, 0xC8, 0x61, 0xFF}}},
	{{{-10, 0, 23},0, {192, 8},{0xBC, 0xCA, 0x5C, 0xFF}}},
	{{{-8, 18, 13},0, {320, 8},{0xB8, 0x4A, 0x49, 0xFF}}},
	{{{16, 18, 15},0, {320, 0},{0x4B, 0x43, 0x4D, 0xFF}}},
	{{{14, 0, 24},0, {192, 0},{0x3B, 0xC8, 0x61, 0xFF}}},
	{{{16, 18, 15},0, {448, 8},{0x4B, 0x43, 0x4D, 0xFF}}},
	{{{19, 0, -2},0, {64, 16},{0x63, 0xB5, 0xE3, 0xFF}}},
};

Gfx friend1_Foot_R_mesh_tri_0[] = {
	gsSPVertex(friend1_Foot_R_mesh_vtx_0 + 0, 18, 0),
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

Gfx friend1_Foot_R_mesh[] = {
	gsSPDisplayList(mat_friend1_model_base_toon_f3d),
	gsSPDisplayList(friend1_Foot_R_mesh_tri_0),
	gsSPDisplayList(mat_revert_friend1_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx friend1_Head_mesh_vtx_0[31] = {
	{{{-30, -15, -8},0, {64, 16},{0xC9, 0x9F, 0xC3, 0xFF}}},
	{{{-13, -15, 28},0, {64, 8},{0x0, 0xAB, 0x5E, 0xFF}}},
	{{{-44, 6, 19},0, {64, 16},{0xDF, 0xB5, 0x61, 0xFF}}},
	{{{35, -15, -4},0, {192, 8},{0x5A, 0xAF, 0x25, 0xFF}}},
	{{{26, -15, -23},0, {192, 16},{0x25, 0xA9, 0xAC, 0xFF}}},
	{{{41, 12, -7},0, {320, 8},{0x74, 0x26, 0x25, 0xFF}}},
	{{{30, 5, -32},0, {320, 16},{0x33, 0xDC, 0x91, 0xFF}}},
	{{{-30, -15, -8},0, {192, 24},{0xC9, 0x9F, 0xC3, 0xFF}}},
	{{{-30, 25, -8},0, {320, 24},{0xE2, 0x47, 0x9B, 0xFF}}},
	{{{-46, 16, -4},0, {320, 24},{0xB2, 0xFD, 0x9C, 0xFF}}},
	{{{-44, 6, 19},0, {192, 24},{0xDF, 0xB5, 0x61, 0xFF}}},
	{{{-55, 23, 3},0, {320, 24},{0x89, 0x21, 0xE4, 0xFF}}},
	{{{-44, 6, 19},0, {320, 24},{0xDF, 0xB5, 0x61, 0xFF}}},
	{{{-42, 36, 0},0, {320, 24},{0xDA, 0x72, 0xD6, 0xFF}}},
	{{{-44, 6, 19},0, {320, 32},{0xDF, 0xB5, 0x61, 0xFF}}},
	{{{-24, 35, 36},0, {320, 32},{0x16, 0x56, 0x5A, 0xFF}}},
	{{{-13, 25, 28},0, {320, 32},{0x42, 0x40, 0x58, 0xFF}}},
	{{{-4, 32, 1},0, {320, 24},{0xA, 0x7B, 0x20, 0xFF}}},
	{{{15, 32, -19},0, {320, 24},{0x28, 0x77, 0xE9, 0xFF}}},
	{{{-11, 32, -20},0, {320, 24},{0xC4, 0x47, 0xAA, 0xFF}}},
	{{{26, 19, -35},0, {320, 16},{0x19, 0x10, 0x84, 0xFF}}},
	{{{15, 32, -19},0, {320, 16},{0x28, 0x77, 0xE9, 0xFF}}},
	{{{40, 26, -21},0, {320, 8},{0x54, 0x5E, 0xEE, 0xFF}}},
	{{{15, 32, -19},0, {320, 8},{0x28, 0x77, 0xE9, 0xFF}}},
	{{{26, 21, -14},0, {320, 8},{0x2B, 0x6F, 0x2C, 0xFF}}},
	{{{-13, 25, 28},0, {320, 0},{0x42, 0x40, 0x58, 0xFF}}},
	{{{-4, 32, 1},0, {320, 0},{0xA, 0x7B, 0x20, 0xFF}}},
	{{{15, 32, -19},0, {320, 0},{0x28, 0x77, 0xE9, 0xFF}}},
	{{{-13, -15, 28},0, {192, 0},{0x0, 0xAB, 0x5E, 0xFF}}},
	{{{-44, 6, 19},0, {192, 0},{0xDF, 0xB5, 0x61, 0xFF}}},
	{{{-24, 35, 36},0, {320, 0},{0x16, 0x56, 0x5A, 0xFF}}},
};

Gfx friend1_Head_mesh_tri_0[] = {
	gsSPVertex(friend1_Head_mesh_vtx_0 + 0, 31, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(0, 4, 3, 0, 4, 5, 3, 0),
	gsSP2Triangles(4, 6, 5, 0, 7, 6, 4, 0),
	gsSP2Triangles(7, 8, 6, 0, 8, 7, 9, 0),
	gsSP2Triangles(7, 10, 9, 0, 8, 9, 11, 0),
	gsSP2Triangles(9, 12, 11, 0, 8, 11, 13, 0),
	gsSP2Triangles(14, 13, 11, 0, 15, 13, 14, 0),
	gsSP2Triangles(16, 13, 15, 0, 16, 8, 13, 0),
	gsSP2Triangles(8, 16, 17, 0, 8, 17, 18, 0),
	gsSP2Triangles(8, 18, 19, 0, 6, 8, 19, 0),
	gsSP2Triangles(6, 19, 20, 0, 20, 19, 21, 0),
	gsSP2Triangles(5, 6, 20, 0, 5, 20, 22, 0),
	gsSP2Triangles(22, 20, 23, 0, 24, 22, 23, 0),
	gsSP2Triangles(24, 5, 22, 0, 25, 5, 24, 0),
	gsSP2Triangles(25, 24, 26, 0, 26, 24, 27, 0),
	gsSP2Triangles(3, 5, 25, 0, 3, 25, 28, 0),
	gsSP2Triangles(28, 25, 29, 0, 29, 25, 30, 0),
	gsSPEndDisplayList(),
};

Gfx friend1_Head_mesh[] = {
	gsSPDisplayList(mat_friend1_model_base_toon_f3d),
	gsSPDisplayList(friend1_Head_mesh_tri_0),
	gsSPDisplayList(mat_revert_friend1_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx friend1_Eye_mesh_vtx_0[4] = {
	{{{-5, -12, 3},0, {-16, 1008},{0x46, 0x0, 0x6A, 0xFF}}},
	{{{5, -12, -3},0, {496, 1008},{0x46, 0x0, 0x6A, 0xFF}}},
	{{{5, 14, -3},0, {496, -16},{0x46, 0x0, 0x6A, 0xFF}}},
	{{{-5, 14, 3},0, {-16, -16},{0x46, 0x0, 0x6A, 0xFF}}},
};

Gfx friend1_Eye_mesh_tri_0[] = {
	gsSPVertex(friend1_Eye_mesh_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx friend1_Eye_mesh[] = {
	gsSPDisplayList(mat_friend1_model_eye_decal_f3d),
	gsSPDisplayList(friend1_Eye_mesh_tri_0),
	gsSPEndDisplayList(),
};



Vtx friend1_Torso_mesh_vtx_0[21] = {
	{{{-18, 0, -36},0, {64, 16},{0xD1, 0xFF, 0x8A, 0xFF}}},
	{{{-10, 26, -23},0, {0, 32},{0xE5, 0x56, 0xA7, 0xFF}}},
	{{{25, 3, -24},0, {64, 16},{0x44, 0xD, 0x95, 0xFF}}},
	{{{-37, 18, 5},0, {0, 32},{0x87, 0x28, 0xFD, 0xFF}}},
	{{{-33, -35, -5},0, {64, 16},{0xA3, 0xAC, 0xE8, 0xFF}}},
	{{{12, -31, -13},0, {64, 8},{0xFD, 0xB0, 0x9E, 0xFF}}},
	{{{29, -28, -15},0, {129, 8},{0x59, 0xBA, 0xC5, 0xFF}}},
	{{{25, 3, -24},0, {129, 8},{0x44, 0xD, 0x95, 0xFF}}},
	{{{5, -49, 3},0, {64, 8},{0x10, 0x82, 0x3, 0xFF}}},
	{{{-22, -17, 29},0, {64, 16},{0xC3, 0xDE, 0x6A, 0xFF}}},
	{{{-2, -26, 28},0, {64, 8},{0x6, 0xBE, 0x6C, 0xFF}}},
	{{{24, -23, 14},0, {129, 8},{0x60, 0xCC, 0x42, 0xFF}}},
	{{{37, 16, -6},0, {192, 8},{0x77, 0x29, 0xEE, 0xFF}}},
	{{{25, 3, -24},0, {192, 8},{0x44, 0xD, 0x95, 0xFF}}},
	{{{28, 17, 15},0, {192, 8},{0x64, 0x32, 0x3C, 0xFF}}},
	{{{19, 34, -10},0, {192, 16},{0x35, 0x6E, 0xDD, 0xFF}}},
	{{{25, 3, -24},0, {192, 16},{0x44, 0xD, 0x95, 0xFF}}},
	{{{-21, 38, 12},0, {192, 16},{0xCD, 0x72, 0x17, 0xFF}}},
	{{{25, 3, -24},0, {0, 32},{0x44, 0xD, 0x95, 0xFF}}},
	{{{-27, 11, 26},0, {192, 16},{0xA7, 0xD, 0x59, 0xFF}}},
	{{{5, 24, 43},0, {192, 8},{0x1A, 0x3A, 0x6E, 0xFF}}},
};

Gfx friend1_Torso_mesh_tri_0[] = {
	gsSPVertex(friend1_Torso_mesh_vtx_0 + 0, 21, 0),
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
};

Gfx friend1_Torso_mesh[] = {
	gsSPDisplayList(mat_friend1_model_base_toon_f3d),
	gsSPDisplayList(friend1_Torso_mesh_tri_0),
	gsSPDisplayList(mat_revert_friend1_model_base_toon_f3d),
	gsSPEndDisplayList(),
};




BoneLayer friend1_model_bone2_layers[] = {
    {
        LAYER_OPA_SURF,
        friend1_Arm_1_mesh,
    },
};
BoneLayer friend1_model_bone3_layers[] = {
    {
        LAYER_OPA_SURF,
        friend1_Arm_2_mesh,
    },
};
BoneLayer friend1_model_bone4_layers[] = {
    {
        LAYER_OPA_SURF,
        friend1_Arm2_1_mesh,
    },
};
BoneLayer friend1_model_bone5_layers[] = {
    {
        LAYER_OPA_SURF,
        friend1_Arm2_2_mesh,
    },
};
BoneLayer friend1_model_bone6_layers[] = {
    {
        LAYER_OPA_SURF,
        friend1_Hand_mesh,
    },
};
BoneLayer friend1_model_bone7_layers[] = {
    {
        LAYER_OPA_SURF,
        friend1_Hand2_mesh,
    },
};
BoneLayer friend1_model_bone8_layers[] = {
    {
        LAYER_OPA_SURF,
        friend1_Foot_L_mesh,
    },
};
BoneLayer friend1_model_bone9_layers[] = {
    {
        LAYER_OPA_SURF,
        friend1_Foot_R_mesh,
    },
};
BoneLayer friend1_model_bone10_layers[] = {
    {
        LAYER_OPA_SURF,
        friend1_Head_mesh,
    },
};
BoneLayer friend1_model_bone11_layers[] = {
    {
        LAYER_TEX_EDGE,
        friend1_Eye_mesh,
    },
};
BoneLayer friend1_model_bone12_layers[] = {
    {
        LAYER_OPA_SURF,
        friend1_Torso_mesh,
    },
};

Bone friend1_model_bones[] = {
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
        0.1169910654425621,
        106.28129577636719,
        0.005827760323882103,
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
        -47.527435302734375,
        -5.496072769165039,
        32.579349517822266,
        friend1_model_bone2_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        3,
        1,
        1,
        0,
        -78.36095428466797,
        -5.496072769165039,
        52.67353820800781,
        friend1_model_bone3_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        4,
        1,
        1,
        0,
        47.16864776611328,
        -0.627593994140625,
        -29.705318450927734,
        friend1_model_bone4_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        5,
        1,
        1,
        0,
        79.92265319824219,
        0.5945491790771484,
        -46.443397521972656,
        friend1_model_bone5_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        6,
        1,
        1,
        0,
        -110.29595947265625,
        -5.496072769165039,
        73.4855728149414,
        friend1_model_bone6_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        7,
        1,
        1,
        0,
        111.0268325805664,
        2.1135902404785156,
        -70.6742935180664,
        friend1_model_bone7_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        8,
        0,
        1,
        0,
        26.23630142211914,
        0.16871854662895203,
        -17.098194122314453,
        friend1_model_bone8_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        9,
        0,
        1,
        0,
        -26.236286163330078,
        0.1687200367450714,
        17.098163604736328,
        friend1_model_bone9_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        10,
        0,
        1,
        0,
        4.486797332763672,
        127.73494720458984,
        1.4816118478775024,
        friend1_model_bone10_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        11,
        10,
        1,
        0,
        11.015148162841797,
        3.4678077697753906,
        14.657587051391602,
        friend1_model_bone11_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        12,
        0,
        1,
        0,
        3.1672692557549453e-07,
        68.54440307617188,
        -2.510168997105211e-06,
        friend1_model_bone12_layers,
        NULL,
        NULL,
        NULL,
    },
};

Model friend1_model = {
    13,
    0,
    friend1_model_bones
};

