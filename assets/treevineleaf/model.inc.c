
Gfx treevineleaf_model_shading_i4_aligner[] = {gsSPEndDisplayList()};
u8 treevineleaf_model_shading_i4[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xBB, 0x77, 0x77, 
};


Gfx mat_treevineleaf_model_bark_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPSetGeometryMode(G_TEXTURE_GEN),
	gsDPSetTextureFilter(G_TF_POINT),
	gsSPTexture(959, 0, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 8, treevineleaf_model_shading_i4),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 30, 0),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 0),
	gsDPSetPrimColor(0, 0, 133, 107, 64, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_treevineleaf_model_bark_f3d[] = {
	gsDPPipeSync(),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetTextureFilter(G_TF_BILERP),
	gsSPEndDisplayList(),
};


Gfx mat_treevineleaf_model_leaf_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPSetGeometryMode(G_TEXTURE_GEN),
	gsDPSetTextureFilter(G_TF_POINT),
	gsSPTexture(959, 0, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 8, treevineleaf_model_shading_i4),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 30, 0),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 0),
	gsDPSetPrimColor(0, 0, 59, 136, 92, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_treevineleaf_model_leaf_f3d[] = {
	gsDPPipeSync(),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetTextureFilter(G_TF_BILERP),
	gsSPEndDisplayList(),
};



Vtx treevineleaf_Root_mesh_vtx_0[25] = {
	{{{-62, 153, -7},0, {139, 58},{0xDA, 0x79, 0xF8, 0xFF}}},
	{{{-179, 0, -90},0, {124, 63},{0xBF, 0xF, 0x94, 0xFF}}},
	{{{-485, 0, -348},0, {-38, 63},{0xE7, 0x7A, 0xE8, 0xFF}}},
	{{{-217, 0, 29},0, {74, 65},{0xB6, 0x58, 0x35, 0xFF}}},
	{{{-55, 382, -43},0, {122, 49},{0xC8, 0x64, 0x37, 0xFF}}},
	{{{-179, 0, -90},0, {79, 65},{0xBF, 0xF, 0x94, 0xFF}}},
	{{{-256, 0, 180},0, {47, 67},{0x9A, 0x47, 0x1D, 0xFF}}},
	{{{-115, 162, 156},0, {106, 60},{0xF0, 0x61, 0x50, 0xFF}}},
	{{{-6, 0, 510},0, {163, 69},{0xF, 0x74, 0x31, 0xFF}}},
	{{{5, 0, 249},0, {179, 66},{0x59, 0x50, 0x2A, 0xFF}}},
	{{{109, 0, 128},0, {226, 67},{0x6, 0x36, 0x73, 0xFF}}},
	{{{-181, 760, -17},0, {97, 35},{0x83, 0x13, 0x5, 0xFF}}},
	{{{43, 843, 70},0, {258, 32},{0x44, 0x5, 0x6B, 0xFF}}},
	{{{270, 0, -76},0, {313, 65},{0x7C, 0x1B, 0xF7, 0xFF}}},
	{{{10, 791, -113},0, {201, 33},{0x29, 0x13, 0x89, 0xFF}}},
	{{{133, 0, -220},0, {238, 63},{0x41, 0x23, 0x98, 0xFF}}},
	{{{109, 0, 128},0, {157, 64},{0x6, 0x36, 0x73, 0xFF}}},
	{{{59, 309, -146},0, {189, 50},{0xDB, 0x78, 0xEE, 0xFF}}},
	{{{-83, 0, -552},0, {163, 58},{0xE3, 0x67, 0xBC, 0xFF}}},
	{{{709, 0, 190},0, {550, 61},{0x2E, 0x75, 0x13, 0xFF}}},
	{{{133, 0, -220},0, {265, 61},{0x41, 0x23, 0x98, 0xFF}}},
	{{{4091, 6, -67},0, {192, 24},{0xB1, 0xBB, 0xB8, 0xFF}}},
	{{{4354, 6, 153},0, {192, 8},{0x51, 0xB4, 0x3F, 0xFF}}},
	{{{4163, 6, 192},0, {192, 0},{0xC8, 0xB5, 0x56, 0xFF}}},
	{{{4352, 6, -24},0, {192, 16},{0x4E, 0xB6, 0xBC, 0xFF}}},
};

Gfx treevineleaf_Root_mesh_tri_0[] = {
	gsSPVertex(treevineleaf_Root_mesh_vtx_0 + 0, 25, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
	gsSP2Triangles(4, 5, 6, 0, 7, 4, 6, 0),
	gsSP2Triangles(7, 6, 8, 0, 9, 7, 8, 0),
	gsSP2Triangles(10, 7, 9, 0, 10, 4, 7, 0),
	gsSP2Triangles(5, 10, 11, 0, 11, 10, 12, 0),
	gsSP2Triangles(10, 13, 12, 0, 14, 12, 13, 0),
	gsSP2Triangles(14, 13, 15, 0, 11, 14, 15, 0),
	gsSP2Triangles(11, 15, 5, 0, 16, 17, 18, 0),
	gsSP2Triangles(17, 16, 19, 0, 20, 17, 19, 0),
	gsSP2Triangles(17, 20, 18, 0, 21, 22, 23, 0),
	gsSP1Triangle(21, 24, 22, 0),
	gsSPEndDisplayList(),
};

Gfx treevineleaf_Root_mesh[] = {
	gsSPDisplayList(mat_treevineleaf_model_bark_f3d),
	gsSPDisplayList(treevineleaf_Root_mesh_tri_0),
	gsSPDisplayList(mat_revert_treevineleaf_model_bark_f3d),
	gsSPEndDisplayList(),
};



Vtx treevineleaf_Leaf_mesh_vtx_0[22] = {
	{{{-2, 1, -1},0, {0, 32},{0xFB, 0x30, 0x8A, 0xFF}}},
	{{{-8, 2, 6},0, {0, 32},{0xA1, 0x53, 0x9, 0xFF}}},
	{{{6, 2, 6},0, {0, 32},{0x61, 0x52, 0x2, 0xFF}}},
	{{{-13, -21, 20},0, {0, 32},{0x9D, 0x48, 0x22, 0xFF}}},
	{{{-2, -22, 8},0, {0, 32},{0xFB, 0xDF, 0x86, 0xFF}}},
	{{{11, -21, 20},0, {0, 32},{0x64, 0x4A, 0x19, 0xFF}}},
	{{{-54, -47, 34},0, {0, 32},{0x8D, 0x33, 0xF2, 0xFF}}},
	{{{-3, -52, 21},0, {0, 32},{0xFB, 0xD4, 0x89, 0xFF}}},
	{{{58, -48, 34},0, {0, 32},{0x6E, 0x3C, 0xE9, 0xFF}}},
	{{{-87, -83, 61},0, {0, 32},{0x82, 0xD, 0xFF, 0xFF}}},
	{{{-5, -90, 46},0, {0, 32},{0xF9, 0xB7, 0x98, 0xFF}}},
	{{{95, -88, 57},0, {0, 32},{0x79, 0x1C, 0xE8, 0xFF}}},
	{{{-89, -126, 101},0, {0, 32},{0x84, 0xF2, 0x15, 0xFF}}},
	{{{-5, -135, 84},0, {0, 32},{0xF9, 0x9C, 0xB2, 0xFF}}},
	{{{97, -135, 96},0, {0, 32},{0x7E, 0xF3, 0xFE, 0xFF}}},
	{{{-70, -155, 159},0, {0, 32},{0x89, 0xFB, 0x2C, 0xFF}}},
	{{{-7, -167, 153},0, {0, 32},{0xF6, 0x89, 0xD5, 0xFF}}},
	{{{72, -163, 155},0, {0, 32},{0x79, 0xEC, 0x22, 0xFF}}},
	{{{-28, -178, 216},0, {0, 32},{0x94, 0xFE, 0x43, 0xFF}}},
	{{{-2, -185, 213},0, {0, 32},{0xF6, 0x84, 0xE8, 0xFF}}},
	{{{30, -181, 215},0, {0, 32},{0x73, 0xF2, 0x34, 0xFF}}},
	{{{7, -193, 262},0, {0, 32},{0xE, 0xE3, 0x7B, 0xFF}}},
};

Gfx treevineleaf_Leaf_mesh_tri_0[] = {
	gsSPVertex(treevineleaf_Leaf_mesh_vtx_0 + 0, 22, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(0, 4, 3, 0, 2, 4, 0, 0),
	gsSP2Triangles(2, 5, 4, 0, 1, 5, 2, 0),
	gsSP2Triangles(1, 3, 5, 0, 5, 3, 6, 0),
	gsSP2Triangles(3, 7, 6, 0, 3, 4, 7, 0),
	gsSP2Triangles(4, 8, 7, 0, 4, 5, 8, 0),
	gsSP2Triangles(5, 6, 8, 0, 8, 6, 9, 0),
	gsSP2Triangles(6, 10, 9, 0, 6, 7, 10, 0),
	gsSP2Triangles(7, 11, 10, 0, 7, 8, 11, 0),
	gsSP2Triangles(8, 9, 11, 0, 11, 9, 12, 0),
	gsSP2Triangles(9, 13, 12, 0, 9, 10, 13, 0),
	gsSP2Triangles(10, 14, 13, 0, 10, 11, 14, 0),
	gsSP2Triangles(11, 12, 14, 0, 14, 12, 15, 0),
	gsSP2Triangles(12, 16, 15, 0, 12, 13, 16, 0),
	gsSP2Triangles(13, 17, 16, 0, 13, 14, 17, 0),
	gsSP2Triangles(14, 15, 17, 0, 17, 15, 18, 0),
	gsSP2Triangles(15, 19, 18, 0, 15, 16, 19, 0),
	gsSP2Triangles(16, 20, 19, 0, 16, 17, 20, 0),
	gsSP2Triangles(17, 18, 20, 0, 20, 18, 21, 0),
	gsSP2Triangles(18, 19, 21, 0, 19, 20, 21, 0),
	gsSPEndDisplayList(),
};

Gfx treevineleaf_Leaf_mesh[] = {
	gsSPDisplayList(mat_treevineleaf_model_leaf_f3d),
	gsSPDisplayList(treevineleaf_Leaf_mesh_tri_0),
	gsSPDisplayList(mat_revert_treevineleaf_model_leaf_f3d),
	gsSPEndDisplayList(),
};



Vtx treevineleaf_Tree1_mesh_vtx_0[3] = {
	{{{448, 1474, 86},0, {336, 14},{0x50, 0xF2, 0x62, 0xFF}}},
	{{{426, 1477, -92},0, {284, 8},{0x40, 0xFA, 0x93, 0xFF}}},
	{{{305, 1595, 4},0, {209, 5},{0x85, 0x20, 0x6, 0xFF}}},
};

Gfx treevineleaf_Tree1_mesh_tri_0[] = {
	gsSPVertex(treevineleaf_Tree1_mesh_vtx_0 + 0, 3, 3),
	gsSP2Triangles(1, 2, 3, 0, 0, 3, 2, 0),
	gsSP2Triangles(0, 4, 3, 0, 0, 5, 4, 0),
	gsSP2Triangles(0, 1, 5, 0, 1, 3, 5, 0),
	gsSPEndDisplayList(),
};Vtx treevineleaf_Tree1_mesh_vtx_1[13] = {
	{{{681, 1074, -50},0, {303, 13},{0xAE, 0xFB, 0x9F, 0xFF}}},
	{{{1494, 995, 79},0, {320, 8},{0x7D, 0xEA, 0xB, 0xFF}}},
	{{{682, 1040, 40},0, {302, 8},{0xA8, 0xC1, 0x42, 0xFF}}},
	{{{734, 1133, 17},0, {304, 0},{0xE7, 0x7A, 0x1B, 0xFF}}},
	{{{682, 1040, 40},0, {302, 5},{0xA8, 0xC1, 0x42, 0xFF}}},
	{{{1494, 995, 79},0, {320, 0},{0x7D, 0xEA, 0xB, 0xFF}}},
	{{{681, 1074, -50},0, {303, 16},{0xAE, 0xFB, 0x9F, 0xFF}}},
	{{{734, 1133, 17},0, {306, 20},{0xE7, 0x7A, 0x1B, 0xFF}}},
	{{{1494, 995, 79},0, {320, 16},{0x7D, 0xEA, 0xB, 0xFF}}},
	{{{363, 428, -92},0, {284, 8},{0x3F, 0xF0, 0x93, 0xFF}}},
	{{{577, 1512, 44},0, {285, -39},{0x1D, 0x7B, 0x5, 0xFF}}},
	{{{384, 422, 86},0, {336, 14},{0x4D, 0xE6, 0x62, 0xFF}}},
	{{{261, 563, 4},0, {209, 5},{0x8B, 0x32, 0x6, 0xFF}}},
};

Gfx treevineleaf_Tree1_mesh_tri_1[] = {
	gsSPVertex(treevineleaf_Tree1_mesh_vtx_1 + 0, 13, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 6, 4, 7, 0),
	gsSP2Triangles(9, 10, 11, 0, 9, 12, 10, 0),
	gsSP1Triangle(12, 11, 10, 0),
	gsSPEndDisplayList(),
};Vtx treevineleaf_Tree1_mesh_vtx_2[22] = {
	{{{1494, 995, 79},0, {326, 22},{0x7D, 0xEA, 0xB, 0xFF}}},
	{{{1259, 1216, -17},0, {326, 22},{0xF0, 0x76, 0xD4, 0xFF}}},
	{{{1184, 995, 295},0, {372, 27},{0xCD, 0xEF, 0x73, 0xFF}}},
	{{{1193, 912, -109},0, {279, 27},{0xCD, 0xB9, 0xA4, 0xFF}}},
	{{{1494, 995, 79},0, {279, 27},{0x7D, 0xEA, 0xB, 0xFF}}},
	{{{831, 925, 345},0, {346, 19},{0x2F, 0xCF, 0x6B, 0xFF}}},
	{{{591, 1221, 389},0, {266, 14},{0x21, 0xF7, 0x7A, 0xFF}}},
	{{{489, 1260, -2},0, {250, 13},{0xDD, 0x86, 0x9, 0xFF}}},
	{{{926, 1304, 7},0, {368, 8},{0x74, 0x32, 0xF, 0xFF}}},
	{{{849, 889, -291},0, {406, 18},{0x41, 0xB5, 0xB1, 0xFF}}},
	{{{594, 599, 38},0, {334, 28},{0xD2, 0x8A, 0x5, 0xFF}}},
	{{{274, 1052, -513},0, {259, 18},{0xDB, 0xF4, 0x87, 0xFF}}},
	{{{-98, 1189, -15},0, {101, 18},{0x84, 0xF3, 0xE7, 0xFF}}},
	{{{73, 727, 189},0, {163, 28},{0xE3, 0x84, 0x1, 0xFF}}},
	{{{246, 1111, 516},0, {164, 18},{0xFC, 0xE1, 0x7B, 0xFF}}},
	{{{217, 1529, 214},0, {128, 8},{0xD2, 0x65, 0x3E, 0xFF}}},
	{{{611, 1661, -22},0, {244, -4},{0x2A, 0x76, 0x12, 0xFF}}},
	{{{669, 1363, -390},0, {325, 9},{0x37, 0x38, 0x9C, 0xFF}}},
	{{{231, 1502, -262},0, {187, 9},{0xC7, 0x5B, 0xBC, 0xFF}}},
	{{{191, 606, -257},0, {251, 29},{0xDD, 0x8B, 0x25, 0xFF}}},
	{{{159, 1155, -318},0, {203, 17},{0xB6, 0x5E, 0x2A, 0xFF}}},
	{{{561, 1009, -377},0, {325, 17},{0x7E, 0x10, 0x3, 0xFF}}},
};

Gfx treevineleaf_Tree1_mesh_tri_2[] = {
	gsSPVertex(treevineleaf_Tree1_mesh_vtx_2 + 0, 22, 0),
	gsSP2Triangles(0, 1, 2, 0, 2, 1, 3, 0),
	gsSP2Triangles(4, 3, 1, 0, 2, 3, 4, 0),
	gsSP2Triangles(5, 6, 7, 0, 5, 8, 6, 0),
	gsSP2Triangles(5, 9, 8, 0, 9, 5, 10, 0),
	gsSP2Triangles(5, 7, 10, 0, 7, 9, 10, 0),
	gsSP2Triangles(7, 11, 9, 0, 7, 12, 11, 0),
	gsSP2Triangles(12, 7, 13, 0, 7, 14, 13, 0),
	gsSP2Triangles(6, 14, 7, 0, 14, 6, 15, 0),
	gsSP2Triangles(15, 6, 8, 0, 16, 15, 8, 0),
	gsSP2Triangles(8, 17, 16, 0, 9, 17, 8, 0),
	gsSP2Triangles(9, 11, 17, 0, 11, 18, 17, 0),
	gsSP2Triangles(11, 12, 18, 0, 12, 15, 18, 0),
	gsSP2Triangles(12, 14, 15, 0, 14, 12, 13, 0),
	gsSP2Triangles(18, 15, 16, 0, 17, 18, 16, 0),
	gsSP2Triangles(19, 20, 11, 0, 19, 21, 20, 0),
	gsSP2Triangles(21, 19, 11, 0, 21, 11, 20, 0),
	gsSPEndDisplayList(),
};
Vtx treevineleaf_Tree1_skinned_vtx_0[3] = {
	{{{130, 780, -113},0, {201, 33},{0x2B, 0xC, 0x89, 0xFF}}},
	{{{-64, 779, -17},0, {97, 35},{0x87, 0x26, 0x5, 0xFF}}},
	{{{170, 826, 70},0, {258, 32},{0x44, 0xFB, 0x6B, 0xFF}}},
};

Gfx treevineleaf_Tree1_skinned_tri_0[] = {
	gsSPVertex(treevineleaf_Tree1_skinned_vtx_0 + 0, 3, 0),
	gsSPEndDisplayList(),
};

Gfx treevineleaf_Tree1_mesh[] = {
	gsSPDisplayList(mat_treevineleaf_model_bark_f3d),
	gsSPDisplayList(treevineleaf_Tree1_mesh_tri_0),
	gsSPDisplayList(mat_revert_treevineleaf_model_bark_f3d),
	gsSPDisplayList(mat_treevineleaf_model_bark_f3d),
	gsSPDisplayList(treevineleaf_Tree1_mesh_tri_1),
	gsSPDisplayList(mat_revert_treevineleaf_model_bark_f3d),
	gsSPDisplayList(mat_treevineleaf_model_leaf_f3d),
	gsSPDisplayList(treevineleaf_Tree1_mesh_tri_2),
	gsSPDisplayList(mat_revert_treevineleaf_model_leaf_f3d),
	gsSPEndDisplayList(),
};


Gfx treevineleaf_Tree1_skinned[] = {
	gsSPDisplayList(mat_treevineleaf_model_bark_f3d),
	gsSPDisplayList(treevineleaf_Tree1_skinned_tri_0),
	gsSPDisplayList(mat_revert_treevineleaf_model_bark_f3d),
	gsSPEndDisplayList(),
};



Vtx treevineleaf_Tree2_mesh_vtx_0[5] = {
	{{{4229, 191, 218},0, {290, 32},{0x81, 0x4, 0xF7, 0xFF}}},
	{{{4330, 190, 111},0, {290, 24},{0x4, 0x23, 0x86, 0xFF}}},
	{{{4434, 158, 209},0, {290, 16},{0x7C, 0xF5, 0xE5, 0xFF}}},
	{{{4389, 267, 361},0, {290, 8},{0x1C, 0xDE, 0x77, 0xFF}}},
	{{{4229, 191, 218},0, {290, 0},{0x81, 0x4, 0xF7, 0xFF}}},
};

Gfx treevineleaf_Tree2_mesh_tri_0[] = {
	gsSPVertex(treevineleaf_Tree2_mesh_vtx_0 + 0, 5, 5),
	gsSP2Triangles(0, 1, 5, 0, 6, 0, 5, 0),
	gsSP2Triangles(6, 3, 0, 0, 6, 7, 3, 0),
	gsSP2Triangles(7, 4, 3, 0, 7, 8, 4, 0),
	gsSP2Triangles(2, 4, 8, 0, 9, 2, 8, 0),
	gsSPEndDisplayList(),
};Vtx treevineleaf_Tree2_mesh_vtx_1[19] = {
	{{{184, 135, 44},0, {290, 16},{0x79, 0xE5, 0xE4, 0xFF}}},
	{{{950, 1831, 1011},0, {320, 8},{0x35, 0x64, 0x3A, 0xFF}}},
	{{{153, 227, 210},0, {290, 8},{0x13, 0xC9, 0x71, 0xFF}}},
	{{{88, 198, -49},0, {295, 24},{0xC, 0x33, 0x8C, 0xFF}}},
	{{{86, 483, 156},0, {293, 32},{0xA4, 0x57, 0xF5, 0xFF}}},
	{{{950, 1831, 1011},0, {320, 24},{0x35, 0x64, 0x3A, 0xFF}}},
	{{{950, 1831, 1011},0, {320, 16},{0x35, 0x64, 0x3A, 0xFF}}},
	{{{-14, 200, 57},0, {290, 0},{0x84, 0x1A, 0xF7, 0xFF}}},
	{{{-147, 338, 154},0, {290, 0},{0x84, 0x16, 0xF, 0xFF}}},
	{{{408, 814, 461},0, {293, 32},{0xA7, 0xE2, 0x56, 0xFF}}},
	{{{342, 677, 345},0, {290, 0},{0x2, 0x88, 0xD5, 0xFF}}},
	{{{695, 566, 669},0, {293, 32},{0xE8, 0x84, 0xEF, 0xFF}}},
	{{{442, 825, 395},0, {290, 8},{0x51, 0xEA, 0xA1, 0xFF}}},
	{{{695, 566, 669},0, {290, 0},{0xE8, 0x84, 0xEF, 0xFF}}},
	{{{86, 483, 156},0, {293, 0},{0xA4, 0x57, 0xF5, 0xFF}}},
	{{{950, 1831, 1011},0, {320, 0},{0x35, 0x64, 0x3A, 0xFF}}},
	{{{-147, 338, 154},0, {290, 8},{0x84, 0x16, 0xF, 0xFF}}},
	{{{88, 198, -49},0, {290, 24},{0xC, 0x33, 0x8C, 0xFF}}},
	{{{-147, 338, 154},0, {293, 32},{0x84, 0x16, 0xF, 0xFF}}},
};

Gfx treevineleaf_Tree2_mesh_tri_1[] = {
	gsSPVertex(treevineleaf_Tree2_mesh_vtx_1 + 0, 19, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(0, 3, 6, 0, 7, 2, 8, 0),
	gsSP2Triangles(9, 10, 11, 0, 10, 12, 13, 0),
	gsSP2Triangles(14, 2, 15, 0, 2, 14, 16, 0),
	gsSP2Triangles(17, 7, 4, 0, 4, 7, 18, 0),
	gsSPEndDisplayList(),
};Vtx treevineleaf_Tree2_mesh_vtx_2[58] = {
	{{{857, 1622, 922},0, {288, 18},{0xD9, 0x88, 0xF2, 0xFF}}},
	{{{824, 559, 1529},0, {320, 16},{0xCB, 0xA7, 0x4A, 0xFF}}},
	{{{60, 1201, 971},0, {192, 16},{0x8E, 0xD9, 0x29, 0xFF}}},
	{{{398, 1339, 1106},0, {320, 16},{0xD4, 0x56, 0xAD, 0xFF}}},
	{{{808, 957, 1367},0, {320, 22},{0x71, 0xC9, 0x15, 0xFF}}},
	{{{147, 594, 1197},0, {320, 16},{0xB4, 0x9B, 0xEF, 0xFF}}},
	{{{622, 1393, 1481},0, {256, 4},{0x1F, 0x61, 0x4B, 0xFF}}},
	{{{398, 1339, 1106},0, {192, 0},{0xD4, 0x56, 0xAD, 0xFF}}},
	{{{147, 594, 1197},0, {256, 4},{0xB4, 0x9B, 0xEF, 0xFF}}},
	{{{1331, 1634, 1196},0, {192, 32},{0x65, 0x39, 0x34, 0xFF}}},
	{{{933, 1974, 984},0, {320, 32},{0x17, 0x7D, 0x0, 0xFF}}},
	{{{428, 1594, 1350},0, {320, 24},{0xB6, 0x49, 0x49, 0xFF}}},
	{{{777, 1243, 1659},0, {192, 24},{0xFB, 0x12, 0x7E, 0xFF}}},
	{{{1249, 550, 1088},0, {192, 6},{0x2B, 0xB6, 0xA2, 0xFF}}},
	{{{1437, 547, 892},0, {192, 8},{0x4C, 0x9E, 0x1C, 0xFF}}},
	{{{1331, 1634, 1196},0, {320, 8},{0x65, 0x39, 0x34, 0xFF}}},
	{{{1265, 485, 1265},0, {221, 6},{0x6C, 0xD0, 0x2E, 0xFF}}},
	{{{777, 1243, 1659},0, {320, 0},{0xFB, 0x12, 0x7E, 0xFF}}},
	{{{849, -30, 1185},0, {192, 6},{0xCC, 0x8E, 0xE9, 0xFF}}},
	{{{857, 1622, 922},0, {222, 22},{0xD9, 0x88, 0xF2, 0xFF}}},
	{{{614, 744, 87},0, {192, 24},{0xAE, 0xC8, 0xB1, 0xFF}}},
	{{{1437, 547, 892},0, {320, 24},{0x4C, 0x9E, 0x1C, 0xFF}}},
	{{{901, 791, 193},0, {253, 24},{0x12, 0xC9, 0x8F, 0xFF}}},
	{{{878, 87, 116},0, {320, 24},{0xD4, 0x92, 0xD1, 0xFF}}},
	{{{857, 1622, 922},0, {225, 18},{0xD9, 0x88, 0xF2, 0xFF}}},
	{{{359, 1158, 436},0, {192, 19},{0x17, 0xAF, 0xA1, 0xFF}}},
	{{{-69, 909, 652},0, {192, 19},{0xB3, 0x9B, 0xFA, 0xFF}}},
	{{{857, 1622, 922},0, {290, 22},{0xD9, 0x88, 0xF2, 0xFF}}},
	{{{1249, 550, 1088},0, {320, 22},{0x2B, 0xB6, 0xA2, 0xFF}}},
	{{{849, -30, 1185},0, {320, 16},{0xCC, 0x8E, 0xE9, 0xFF}}},
	{{{824, 559, 1529},0, {192, 16},{0xCB, 0xA7, 0x4A, 0xFF}}},
	{{{777, 1243, 1659},0, {320, 16},{0xFB, 0x12, 0x7E, 0xFF}}},
	{{{428, 1594, 1350},0, {320, 8},{0xB6, 0x49, 0x49, 0xFF}}},
	{{{60, 1201, 971},0, {192, 8},{0x8E, 0xD9, 0x29, 0xFF}}},
	{{{1265, 485, 1265},0, {256, 4},{0x6C, 0xD0, 0x2E, 0xFF}}},
	{{{777, 1243, 1659},0, {320, 0},{0xFB, 0x12, 0x7E, 0xFF}}},
	{{{824, 559, 1529},0, {192, 0},{0xCB, 0xA7, 0x4A, 0xFF}}},
	{{{849, -30, 1185},0, {256, 4},{0xCC, 0x8E, 0xE9, 0xFF}}},
	{{{60, 1201, 971},0, {320, 16},{0x8E, 0xD9, 0x29, 0xFF}}},
	{{{428, 1594, 1350},0, {448, 16},{0xB6, 0x49, 0x49, 0xFF}}},
	{{{933, 1974, 984},0, {448, 8},{0x17, 0x7D, 0x0, 0xFF}}},
	{{{226, 1481, 466},0, {342, 13},{0xCC, 0x4C, 0xA9, 0xFF}}},
	{{{359, 1158, 436},0, {320, 13},{0x17, 0xAF, 0xA1, 0xFF}}},
	{{{614, 744, 87},0, {320, 8},{0xAE, 0xC8, 0xB1, 0xFF}}},
	{{{-69, 909, 652},0, {342, 13},{0xB3, 0x9B, 0xFA, 0xFF}}},
	{{{-69, 909, 652},0, {320, 16},{0xB3, 0x9B, 0xFA, 0xFF}}},
	{{{1287, 1102, 258},0, {131, 13},{0x4B, 0x2A, 0xA2, 0xFF}}},
	{{{1437, 547, 892},0, {64, 8},{0x4C, 0x9E, 0x1C, 0xFF}}},
	{{{878, 87, 116},0, {131, 13},{0xD4, 0x92, 0xD1, 0xFF}}},
	{{{1331, 1634, 1196},0, {192, 8},{0x65, 0x39, 0x34, 0xFF}}},
	{{{933, 1974, 984},0, {192, 16},{0x17, 0x7D, 0x0, 0xFF}}},
	{{{614, 744, 87},0, {64, 16},{0xAE, 0xC8, 0xB1, 0xFF}}},
	{{{901, 791, 193},0, {64, 16},{0x12, 0xC9, 0x8F, 0xFF}}},
	{{{878, 87, 116},0, {64, 16},{0xD4, 0x92, 0xD1, 0xFF}}},
	{{{622, 1393, 1481},0, {221, 6},{0x1F, 0x61, 0x4B, 0xFF}}},
	{{{808, 957, 1367},0, {192, 6},{0x71, 0xC9, 0x15, 0xFF}}},
	{{{398, 1339, 1106},0, {320, 16},{0xD4, 0x56, 0xAD, 0xFF}}},
	{{{147, 594, 1197},0, {192, 6},{0xB4, 0x9B, 0xEF, 0xFF}}},
};

Gfx treevineleaf_Tree2_mesh_tri_2[] = {
	gsSPVertex(treevineleaf_Tree2_mesh_vtx_2 + 0, 30, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
	gsSP2Triangles(9, 11, 12, 0, 13, 14, 15, 0),
	gsSP2Triangles(16, 13, 15, 0, 16, 15, 17, 0),
	gsSP2Triangles(13, 16, 18, 0, 19, 20, 21, 0),
	gsSP2Triangles(22, 21, 20, 0, 21, 22, 23, 0),
	gsSP2Triangles(24, 25, 20, 0, 25, 24, 2, 0),
	gsSP2Triangles(25, 2, 26, 0, 27, 21, 28, 0),
	gsSP2Triangles(27, 28, 1, 0, 1, 28, 29, 0),
	gsSPVertex(treevineleaf_Tree2_mesh_vtx_2 + 30, 28, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(11, 10, 12, 0, 12, 10, 13, 0),
	gsSP2Triangles(11, 12, 14, 0, 8, 11, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 19, 17, 0),
	gsSP2Triangles(16, 20, 19, 0, 21, 20, 16, 0),
	gsSP2Triangles(21, 16, 22, 0, 22, 16, 23, 0),
	gsSP2Triangles(24, 25, 26, 0, 25, 24, 27, 0),
	gsSPEndDisplayList(),
};
Vtx treevineleaf_Tree2_skinned_vtx_0[5] = {
	{{{4038, -657, -67},0, {192, 24},{0xA8, 0xD4, 0xAF, 0xFF}}},
	{{{4103, -706, 190},0, {192, 32},{0xBB, 0xB4, 0x4B, 0xFF}}},
	{{{4103, -706, 190},0, {192, 0},{0xBB, 0xB4, 0x4B, 0xFF}}},
	{{{4295, -706, -24},0, {192, 16},{0x43, 0xB5, 0xB2, 0xFF}}},
	{{{4292, -732, 151},0, {192, 8},{0x42, 0xA0, 0x33, 0xFF}}},
};

Gfx treevineleaf_Tree2_skinned_tri_0[] = {
	gsSPVertex(treevineleaf_Tree2_skinned_vtx_0 + 0, 5, 0),
	gsSPEndDisplayList(),
};

Gfx treevineleaf_Tree2_mesh[] = {
	gsSPDisplayList(mat_treevineleaf_model_bark_f3d),
	gsSPDisplayList(treevineleaf_Tree2_mesh_tri_0),
	gsSPDisplayList(mat_revert_treevineleaf_model_bark_f3d),
	gsSPDisplayList(mat_treevineleaf_model_bark_f3d),
	gsSPDisplayList(treevineleaf_Tree2_mesh_tri_1),
	gsSPDisplayList(mat_revert_treevineleaf_model_bark_f3d),
	gsSPDisplayList(mat_treevineleaf_model_leaf_f3d),
	gsSPDisplayList(treevineleaf_Tree2_mesh_tri_2),
	gsSPDisplayList(mat_revert_treevineleaf_model_leaf_f3d),
	gsSPEndDisplayList(),
};


Gfx treevineleaf_Tree2_skinned[] = {
	gsSPDisplayList(mat_treevineleaf_model_bark_f3d),
	gsSPDisplayList(treevineleaf_Tree2_skinned_tri_0),
	gsSPDisplayList(mat_revert_treevineleaf_model_bark_f3d),
	gsSPEndDisplayList(),
};



Vtx treevineleaf_Vine1_mesh_vtx_0[6] = {
	{{{-420, 1020, -186},0, {0, 32},{0x9, 0xF1, 0x82, 0xFF}}},
	{{{-24, -8, 49},0, {0, 32},{0xCA, 0xD0, 0x69, 0xFF}}},
	{{{-412, 1057, -89},0, {0, 32},{0x15, 0x1A, 0x7B, 0xFF}}},
	{{{-44, -5, -31},0, {0, 32},{0xC4, 0xC4, 0xA2, 0xFF}}},
	{{{-411, 1126, -151},0, {0, 32},{0x77, 0x2C, 0xFF, 0xFF}}},
	{{{6, 37, 22},0, {0, 32},{0x62, 0x50, 0x4, 0xFF}}},
};

Gfx treevineleaf_Vine1_mesh_tri_0[] = {
	gsSPVertex(treevineleaf_Vine1_mesh_vtx_0 + 0, 6, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(4, 3, 0, 0, 4, 5, 3, 0),
	gsSP2Triangles(2, 5, 4, 0, 2, 1, 5, 0),
	gsSPEndDisplayList(),
};

Gfx treevineleaf_Vine1_mesh[] = {
	gsSPDisplayList(mat_treevineleaf_model_leaf_f3d),
	gsSPDisplayList(treevineleaf_Vine1_mesh_tri_0),
	gsSPDisplayList(mat_revert_treevineleaf_model_leaf_f3d),
	gsSPEndDisplayList(),
};



Vtx treevineleaf_Vine2_mesh_vtx_0[3] = {
	{{{1586, 840, 185},0, {0, 32},{0xE7, 0xC4, 0x6D, 0xFF}}},
	{{{1564, 831, 106},0, {0, 32},{0xF5, 0xB5, 0x9A, 0xFF}}},
	{{{1605, 893, 155},0, {0, 32},{0x20, 0x7B, 0x7, 0xFF}}},
};

Gfx treevineleaf_Vine2_mesh_tri_0[] = {
	gsSPVertex(treevineleaf_Vine2_mesh_vtx_0 + 0, 3, 3),
	gsSP2Triangles(1, 0, 3, 0, 0, 4, 3, 0),
	gsSP2Triangles(0, 2, 4, 0, 2, 5, 4, 0),
	gsSP2Triangles(2, 1, 5, 0, 1, 3, 5, 0),
	gsSPEndDisplayList(),
};
Vtx treevineleaf_Vine2_skinned_vtx_0[3] = {
	{{{792, 1189, 87},0, {0, 32},{0xCA, 0xD0, 0x69, 0xFF}}},
	{{{823, 1235, 60},0, {0, 32},{0x62, 0x50, 0x4, 0xFF}}},
	{{{772, 1193, 6},0, {0, 32},{0xC4, 0xC4, 0xA2, 0xFF}}},
};

Gfx treevineleaf_Vine2_skinned_tri_0[] = {
	gsSPVertex(treevineleaf_Vine2_skinned_vtx_0 + 0, 3, 0),
	gsSPEndDisplayList(),
};

Gfx treevineleaf_Vine2_mesh[] = {
	gsSPDisplayList(mat_treevineleaf_model_leaf_f3d),
	gsSPDisplayList(treevineleaf_Vine2_mesh_tri_0),
	gsSPDisplayList(mat_revert_treevineleaf_model_leaf_f3d),
	gsSPEndDisplayList(),
};


Gfx treevineleaf_Vine2_skinned[] = {
	gsSPDisplayList(mat_treevineleaf_model_leaf_f3d),
	gsSPDisplayList(treevineleaf_Vine2_skinned_tri_0),
	gsSPDisplayList(mat_revert_treevineleaf_model_leaf_f3d),
	gsSPEndDisplayList(),
};



Vtx treevineleaf_Vine3_mesh_vtx_0[3] = {
	{{{2580, 730, 277},0, {0, 32},{0x3, 0xBF, 0x6D, 0xFF}}},
	{{{2560, 720, 220},0, {0, 32},{0xE, 0xB2, 0x9D, 0xFF}}},
	{{{2582, 770, 254},0, {0, 32},{0xF1, 0x7E, 0x2, 0xFF}}},
};

Gfx treevineleaf_Vine3_mesh_tri_0[] = {
	gsSPVertex(treevineleaf_Vine3_mesh_vtx_0 + 0, 3, 3),
	gsSP2Triangles(1, 0, 3, 0, 0, 4, 3, 0),
	gsSP2Triangles(0, 2, 4, 0, 2, 5, 4, 0),
	gsSP2Triangles(2, 1, 5, 0, 1, 3, 5, 0),
	gsSPEndDisplayList(),
};
Vtx treevineleaf_Vine3_skinned_vtx_0[3] = {
	{{{1586, 840, 185},0, {0, 32},{0xE7, 0xC4, 0x6D, 0xFF}}},
	{{{1605, 893, 155},0, {0, 32},{0x20, 0x7B, 0x7, 0xFF}}},
	{{{1564, 831, 106},0, {0, 32},{0xF5, 0xB5, 0x9A, 0xFF}}},
};

Gfx treevineleaf_Vine3_skinned_tri_0[] = {
	gsSPVertex(treevineleaf_Vine3_skinned_vtx_0 + 0, 3, 0),
	gsSPEndDisplayList(),
};

Gfx treevineleaf_Vine3_mesh[] = {
	gsSPDisplayList(mat_treevineleaf_model_leaf_f3d),
	gsSPDisplayList(treevineleaf_Vine3_mesh_tri_0),
	gsSPDisplayList(mat_revert_treevineleaf_model_leaf_f3d),
	gsSPEndDisplayList(),
};


Gfx treevineleaf_Vine3_skinned[] = {
	gsSPDisplayList(mat_treevineleaf_model_leaf_f3d),
	gsSPDisplayList(treevineleaf_Vine3_skinned_tri_0),
	gsSPDisplayList(mat_revert_treevineleaf_model_leaf_f3d),
	gsSPEndDisplayList(),
};



Vtx treevineleaf_Vine4_mesh_vtx_0[3] = {
	{{{3300, 939, 329},0, {0, 32},{0x14, 0xC8, 0x70, 0xFF}}},
	{{{3282, 927, 280},0, {0, 32},{0x21, 0xBE, 0x99, 0xFF}}},
	{{{3298, 976, 304},0, {0, 32},{0xCE, 0x75, 0xFF, 0xFF}}},
};

Gfx treevineleaf_Vine4_mesh_tri_0[] = {
	gsSPVertex(treevineleaf_Vine4_mesh_vtx_0 + 0, 3, 3),
	gsSP2Triangles(1, 0, 3, 0, 0, 4, 3, 0),
	gsSP2Triangles(0, 2, 4, 0, 2, 5, 4, 0),
	gsSP2Triangles(2, 1, 5, 0, 1, 3, 5, 0),
	gsSPEndDisplayList(),
};
Vtx treevineleaf_Vine4_skinned_vtx_0[3] = {
	{{{2580, 730, 277},0, {0, 32},{0x3, 0xBF, 0x6D, 0xFF}}},
	{{{2582, 770, 254},0, {0, 32},{0xF1, 0x7E, 0x2, 0xFF}}},
	{{{2560, 720, 220},0, {0, 32},{0xE, 0xB2, 0x9D, 0xFF}}},
};

Gfx treevineleaf_Vine4_skinned_tri_0[] = {
	gsSPVertex(treevineleaf_Vine4_skinned_vtx_0 + 0, 3, 0),
	gsSPEndDisplayList(),
};

Gfx treevineleaf_Vine4_mesh[] = {
	gsSPDisplayList(mat_treevineleaf_model_leaf_f3d),
	gsSPDisplayList(treevineleaf_Vine4_mesh_tri_0),
	gsSPDisplayList(mat_revert_treevineleaf_model_leaf_f3d),
	gsSPEndDisplayList(),
};


Gfx treevineleaf_Vine4_skinned[] = {
	gsSPDisplayList(mat_treevineleaf_model_leaf_f3d),
	gsSPDisplayList(treevineleaf_Vine4_skinned_tri_0),
	gsSPDisplayList(mat_revert_treevineleaf_model_leaf_f3d),
	gsSPEndDisplayList(),
};



Vtx treevineleaf_Vine5_mesh_vtx_0[3] = {
	{{{4007, 1304, 356},0, {0, 32},{0x22, 0xCA, 0x6E, 0xFF}}},
	{{{3997, 1289, 306},0, {0, 32},{0x3B, 0xBE, 0xA4, 0xFF}}},
	{{{3974, 1333, 334},0, {0, 32},{0xA8, 0x5B, 0xF7, 0xFF}}},
};

Gfx treevineleaf_Vine5_mesh_tri_0[] = {
	gsSPVertex(treevineleaf_Vine5_mesh_vtx_0 + 0, 3, 3),
	gsSP2Triangles(1, 0, 3, 0, 0, 4, 3, 0),
	gsSP2Triangles(0, 2, 4, 0, 2, 5, 4, 0),
	gsSP2Triangles(2, 1, 5, 0, 1, 3, 5, 0),
	gsSPEndDisplayList(),
};Vtx treevineleaf_Vine5_mesh_vtx_1[6] = {
	{{{28, -17, 35},0, {0, 32},{0x22, 0xCA, 0x6E, 0xFF}}},
	{{{18, -32, -15},0, {0, 32},{0x3B, 0xBE, 0xA4, 0xFF}}},
	{{{606, 994, 247},0, {0, 32},{0x4E, 0xF0, 0x9D, 0xFF}}},
	{{{507, 1067, 311},0, {0, 32},{0x92, 0x3C, 0xEC, 0xFF}}},
	{{{-5, 13, 14},0, {0, 32},{0xA8, 0x5B, 0xF7, 0xFF}}},
	{{{538, 1015, 334},0, {0, 32},{0x0, 0xDB, 0x7A, 0xFF}}},
};

Gfx treevineleaf_Vine5_mesh_tri_1[] = {
	gsSPVertex(treevineleaf_Vine5_mesh_vtx_1 + 0, 6, 0),
	gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
	gsSP2Triangles(1, 4, 3, 0, 4, 5, 3, 0),
	gsSP2Triangles(4, 0, 5, 0, 0, 2, 5, 0),
	gsSPEndDisplayList(),
};
Vtx treevineleaf_Vine5_skinned_vtx_0[3] = {
	{{{3300, 939, 329},0, {0, 32},{0x14, 0xC8, 0x70, 0xFF}}},
	{{{3298, 976, 304},0, {0, 32},{0xCE, 0x75, 0xFF, 0xFF}}},
	{{{3282, 927, 280},0, {0, 32},{0x21, 0xBE, 0x99, 0xFF}}},
};

Gfx treevineleaf_Vine5_skinned_tri_0[] = {
	gsSPVertex(treevineleaf_Vine5_skinned_vtx_0 + 0, 3, 0),
	gsSPEndDisplayList(),
};

Gfx treevineleaf_Vine5_mesh[] = {
	gsSPDisplayList(mat_treevineleaf_model_leaf_f3d),
	gsSPDisplayList(treevineleaf_Vine5_mesh_tri_0),
	gsSPDisplayList(mat_revert_treevineleaf_model_leaf_f3d),
	gsSPDisplayList(mat_treevineleaf_model_leaf_f3d),
	gsSPDisplayList(treevineleaf_Vine5_mesh_tri_1),
	gsSPDisplayList(mat_revert_treevineleaf_model_leaf_f3d),
	gsSPEndDisplayList(),
};


Gfx treevineleaf_Vine5_skinned[] = {
	gsSPDisplayList(mat_treevineleaf_model_leaf_f3d),
	gsSPDisplayList(treevineleaf_Vine5_skinned_tri_0),
	gsSPDisplayList(mat_revert_treevineleaf_model_leaf_f3d),
	gsSPEndDisplayList(),
};




BoneLayer treevineleaf_model_bone0_layers[] = {
    {
        1,
        treevineleaf_Root_mesh,
    },
};
BoneLayer treevineleaf_model_bone1_layers[] = {
    {
        1,
        treevineleaf_Leaf_mesh,
    },
};
BoneLayer treevineleaf_model_bone2_layers[] = {
    {
        1,
        treevineleaf_Tree1_mesh,
    },
};
BoneLayer treevineleaf_model_bone3_layers[] = {
    {
        1,
        treevineleaf_Tree2_mesh,
    },
};
BoneLayer treevineleaf_model_bone4_layers[] = {
    {
        1,
        treevineleaf_Vine1_mesh,
    },
};
BoneLayer treevineleaf_model_bone5_layers[] = {
    {
        1,
        treevineleaf_Vine2_mesh,
    },
};
BoneLayer treevineleaf_model_bone6_layers[] = {
    {
        1,
        treevineleaf_Vine3_mesh,
    },
};
BoneLayer treevineleaf_model_bone7_layers[] = {
    {
        1,
        treevineleaf_Vine4_mesh,
    },
};
BoneLayer treevineleaf_model_bone8_layers[] = {
    {
        1,
        treevineleaf_Vine5_mesh,
    },
};

Bone treevineleaf_model_bones[] = {
    {
        0,
        255,
        1,
        0,
        0.0,
        0.0,
        0.0,
        treevineleaf_model_bone0_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        1,
        0,
        1,
        0,
        2559.030029296875,
        734.6309204101562,
        235.5033416748047,
        treevineleaf_model_bone1_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        2,
        0,
        1,
        0,
        -20.357229232788086,
        1007.5534057617188,
        -1.182957839773735e-05,
        treevineleaf_model_bone2_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        3,
        0,
        1,
        0,
        4218.75244140625,
        713.84375,
        87.02826690673828,
        treevineleaf_model_bone3_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        4,
        0,
        1,
        0,
        816.10107421875,
        1197.62158203125,
        37.88567352294922,
        treevineleaf_model_bone4_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        5,
        4,
        1,
        0,
        788.5389404296875,
        -343.6300354003906,
        101.99479675292969,
        treevineleaf_model_bone5_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        6,
        5,
        1,
        0,
        954.57666015625,
        -96.39997863769531,
        102.1692123413086,
        treevineleaf_model_bone6_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        7,
        6,
        1,
        0,
        737.9462890625,
        186.49215698242188,
        44.104339599609375,
        treevineleaf_model_bone7_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        8,
        7,
        1,
        0,
        682.2887573242188,
        376.6232604980469,
        34.62047576904297,
        treevineleaf_model_bone8_layers,
        NULL,
        NULL,
        NULL,
    },
};

Model treevineleaf_model = {
    9,
    0,
    treevineleaf_model_bones
};

