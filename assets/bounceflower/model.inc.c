
Gfx bounceflower_model_shading_i4_aligner[] = {gsSPEndDisplayList()};
u8 bounceflower_model_shading_i4[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xBB, 0x77, 0x77, 
};

Gfx bounceflower_model_billball_I4_i4_aligner[] = {gsSPEndDisplayList()};
u8 bounceflower_model_billball_I4_i4[] = {
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
	0x0, 0x17, 0xCE, 0xEC, 0x71, 0x0, 0x0, 0x0, 0x4, 
	0xEF, 0xFF, 0xFF, 0xFE, 0x40, 0x0, 0x0, 0x4F, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xF4, 0x0, 0x1, 0xEF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFE, 0x10, 0x7, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0x70, 0xC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xC0, 0xE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xE0, 0xF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 
	0xC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x8, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x1, 0xEF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x10, 0x0, 0x5F, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xF5, 0x0, 0x0, 0x5, 0xEF, 0xFF, 
	0xFF, 0xFE, 0x50, 0x0, 0x0, 0x0, 0x18, 0xCF, 0xFC, 
	0x81, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
	0x0, 0x0, 
};


Gfx mat_bounceflower_model_bounceyellow[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPSetGeometryMode(G_TEXTURE_GEN),
	gsDPSetTextureFilter(G_TF_POINT),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(959, 0, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 8, bounceflower_model_shading_i4),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 30, 0),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 0),
	gsDPSetPrimColor(0, 0, 250, 254, 41, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_bounceflower_model_bounceyellow[] = {
	gsDPPipeSync(),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsDPSetTextureFilter(G_TF_BILERP),
	gsSPEndDisplayList(),
};


Gfx mat_bounceflower_model_bounceorange[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPSetGeometryMode(G_TEXTURE_GEN),
	gsDPSetTextureFilter(G_TF_POINT),
	gsSPTexture(959, 0, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 8, bounceflower_model_shading_i4),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 30, 0),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 0),
	gsDPSetPrimColor(0, 0, 254, 151, 108, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_bounceflower_model_bounceorange[] = {
	gsDPPipeSync(),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetTextureFilter(G_TF_BILERP),
	gsSPEndDisplayList(),
};


Gfx mat_bounceflower_model_extensions_2side[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, PRIMITIVE, 0, 0, 0, ENVIRONMENT),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 171, 50, 52, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_bounceflower_model_extensions_2side[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};


Gfx mat_bounceflower_model_extensions_billboard[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, ENVIRONMENT, 0),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 8, bounceflower_model_billball_I4_i4),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 30, 60),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 60),
	gsDPSetPrimColor(0, 0, 254, 194, 169, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_bounceflower_model_extensions_billboard[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};



Vtx bounceflower_Root_mesh_vtx_0[31] = {
	{{{5, 3, 33},0, {-16, 16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-5, 3, 33},0, {-16, 16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, 2, 35},0, {-16, 16},{0x0, 0x73, 0x36, 0xFF}}},
	{{{10, 2, 26},0, {-16, 16},{0x0, 0x7D, 0xEA, 0xFF}}},
	{{{-10, 2, 26},0, {-16, 16},{0x0, 0x7D, 0xEA, 0xFF}}},
	{{{12, 0, 16},0, {-16, 16},{0xFD, 0x7F, 0xFC, 0xFF}}},
	{{{-12, 0, 16},0, {-16, 16},{0x3, 0x7F, 0xFC, 0xFF}}},
	{{{0, 4, 0},0, {-16, 16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{19, 0, -6},0, {-16, 16},{0xFB, 0x7F, 0x2, 0xFF}}},
	{{{22, 2, 18},0, {-16, 16},{0xEB, 0x7D, 0xF9, 0xFF}}},
	{{{28, 2, -2},0, {-16, 16},{0xEB, 0x7D, 0xF9, 0xFF}}},
	{{{30, 3, 15},0, {-16, 16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{33, 3, 6},0, {-16, 16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{33, 2, 11},0, {-16, 16},{0x33, 0x73, 0x11, 0xFF}}},
	{{{0, 0, -20},0, {-16, 16},{0x0, 0x7F, 0x5, 0xFF}}},
	{{{24, 2, -15},0, {-16, 16},{0xF3, 0x7D, 0x12, 0xFF}}},
	{{{7, 2, -27},0, {-16, 16},{0xF3, 0x7D, 0x12, 0xFF}}},
	{{{23, 3, -24},0, {-16, 16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{15, 3, -29},0, {-16, 16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{20, 2, -28},0, {-16, 16},{0x20, 0x73, 0xD4, 0xFF}}},
	{{{-19, 0, -6},0, {-16, 16},{0x5, 0x7F, 0x2, 0xFF}}},
	{{{-7, 2, -27},0, {-16, 16},{0xD, 0x7D, 0x12, 0xFF}}},
	{{{-24, 2, -15},0, {-16, 16},{0xD, 0x7D, 0x12, 0xFF}}},
	{{{-15, 3, -29},0, {-16, 16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-23, 3, -24},0, {-16, 16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-20, 2, -28},0, {-16, 16},{0xE0, 0x73, 0xD4, 0xFF}}},
	{{{-28, 2, -2},0, {-16, 16},{0x15, 0x7D, 0xF9, 0xFF}}},
	{{{-22, 2, 18},0, {-16, 16},{0x15, 0x7D, 0xF9, 0xFF}}},
	{{{-33, 3, 6},0, {-16, 16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-30, 3, 15},0, {-16, 16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-33, 2, 11},0, {-16, 16},{0xCD, 0x73, 0x11, 0xFF}}},
};

Gfx bounceflower_Root_mesh_tri_0[] = {
	gsSPVertex(bounceflower_Root_mesh_vtx_0 + 0, 31, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
	gsSP2Triangles(3, 4, 1, 0, 5, 4, 3, 0),
	gsSP2Triangles(5, 6, 4, 0, 6, 5, 7, 0),
	gsSP2Triangles(5, 8, 7, 0, 8, 5, 9, 0),
	gsSP2Triangles(8, 9, 10, 0, 10, 9, 11, 0),
	gsSP2Triangles(10, 11, 12, 0, 12, 11, 13, 0),
	gsSP2Triangles(8, 14, 7, 0, 14, 8, 15, 0),
	gsSP2Triangles(14, 15, 16, 0, 16, 15, 17, 0),
	gsSP2Triangles(16, 17, 18, 0, 18, 17, 19, 0),
	gsSP2Triangles(14, 20, 7, 0, 20, 14, 21, 0),
	gsSP2Triangles(20, 21, 22, 0, 22, 21, 23, 0),
	gsSP2Triangles(22, 23, 24, 0, 24, 23, 25, 0),
	gsSP2Triangles(20, 6, 7, 0, 6, 20, 26, 0),
	gsSP2Triangles(6, 26, 27, 0, 27, 26, 28, 0),
	gsSP2Triangles(27, 28, 29, 0, 29, 28, 30, 0),
	gsSPEndDisplayList(),
};

Gfx bounceflower_Root_mesh[] = {
	gsSPDisplayList(mat_bounceflower_model_bounceyellow),
	gsSPDisplayList(bounceflower_Root_mesh_tri_0),
	gsSPDisplayList(mat_revert_bounceflower_model_bounceyellow),
	gsSPEndDisplayList(),
};



Vtx bounceflower_Base_mesh_vtx_0[16] = {
	{{{-14, -3, -5},0, {-16, 16},{0xA7, 0xAB, 0xE1, 0xFF}}},
	{{{-9, -3, 12},0, {-16, 16},{0xC9, 0xA8, 0x4A, 0xFF}}},
	{{{-16, 12, 23},0, {-16, 16},{0xB7, 0xE8, 0x65, 0xFF}}},
	{{{17, 12, 23},0, {-16, 16},{0x49, 0xE8, 0x65, 0xFF}}},
	{{{9, -3, 12},0, {-16, 16},{0x37, 0xA8, 0x4A, 0xFF}}},
	{{{27, 12, -8},0, {-16, 16},{0x77, 0xE9, 0xDA, 0xFF}}},
	{{{14, -3, -5},0, {-16, 16},{0x59, 0xAA, 0xE1, 0xFF}}},
	{{{0, 12, -28},0, {-16, 16},{0x0, 0xE9, 0x83, 0xFF}}},
	{{{0, -3, -15},0, {-16, 16},{0x0, 0xAC, 0xA1, 0xFF}}},
	{{{-27, 12, -8},0, {-16, 16},{0x89, 0xE9, 0xDA, 0xFF}}},
	{{{-13, 31, 18},0, {-16, 16},{0xC4, 0x4A, 0x53, 0xFF}}},
	{{{13, 31, 18},0, {-16, 16},{0x3C, 0x4A, 0x53, 0xFF}}},
	{{{21, 31, -7},0, {-16, 16},{0x62, 0x4A, 0xDF, 0xFF}}},
	{{{0, 31, -22},0, {-16, 16},{0x0, 0x4A, 0x99, 0xFF}}},
	{{{-21, 31, -7},0, {-16, 16},{0x9E, 0x4A, 0xDF, 0xFF}}},
	{{{0, 42, 0},0, {-16, 16},{0x0, 0x7F, 0x0, 0xFF}}},
};

Gfx bounceflower_Base_mesh_tri_0[] = {
	gsSPVertex(bounceflower_Base_mesh_vtx_0 + 0, 16, 0),
	gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
	gsSP2Triangles(1, 4, 3, 0, 4, 5, 3, 0),
	gsSP2Triangles(4, 6, 5, 0, 6, 7, 5, 0),
	gsSP2Triangles(6, 8, 7, 0, 8, 9, 7, 0),
	gsSP2Triangles(8, 0, 9, 0, 0, 2, 9, 0),
	gsSP2Triangles(9, 2, 10, 0, 2, 11, 10, 0),
	gsSP2Triangles(2, 3, 11, 0, 3, 12, 11, 0),
	gsSP2Triangles(3, 5, 12, 0, 5, 13, 12, 0),
	gsSP2Triangles(5, 7, 13, 0, 7, 14, 13, 0),
	gsSP2Triangles(7, 9, 14, 0, 9, 10, 14, 0),
	gsSP2Triangles(14, 10, 15, 0, 10, 11, 15, 0),
	gsSP2Triangles(11, 12, 15, 0, 12, 13, 15, 0),
	gsSP1Triangle(13, 14, 15, 0),
	gsSPEndDisplayList(),
};Vtx bounceflower_Base_mesh_vtx_1[54] = {
	{{{1, 21, 28},0, {-16, 1008},{0x81, 0x0, 0x1, 0xFF}}},
	{{{1, 26, 27},0, {-16, 1008},{0x81, 0x0, 0x1, 0xFF}}},
	{{{0, 20, 12},0, {-16, 1008},{0x81, 0x0, 0x1, 0xFF}}},
	{{{28, 21, 8},0, {-16, 1008},{0xD9, 0x0, 0x79, 0xFF}}},
	{{{27, 26, 7},0, {-16, 1008},{0xD9, 0x0, 0x79, 0xFF}}},
	{{{12, 20, 3},0, {-16, 1008},{0xD9, 0x0, 0x79, 0xFF}}},
	{{{17, 21, -25},0, {-16, 1008},{0x67, 0x0, 0x4A, 0xFF}}},
	{{{16, 26, -24},0, {-16, 1008},{0x67, 0x0, 0x4A, 0xFF}}},
	{{{7, 20, -12},0, {-16, 1008},{0x67, 0x0, 0x4A, 0xFF}}},
	{{{-18, 21, -24},0, {-16, 1008},{0x66, 0x0, 0xB5, 0xFF}}},
	{{{-17, 26, -23},0, {-16, 1008},{0x66, 0x0, 0xB5, 0xFF}}},
	{{{-8, 20, -11},0, {-16, 1008},{0x66, 0x0, 0xB5, 0xFF}}},
	{{{-28, 21, 9},0, {-16, 1008},{0xD7, 0x0, 0x88, 0xFF}}},
	{{{-26, 26, 8},0, {-16, 1008},{0xD7, 0x0, 0x88, 0xFF}}},
	{{{-12, 20, 4},0, {-16, 1008},{0xD7, 0x0, 0x88, 0xFF}}},
	{{{21, 11, 27},0, {-16, 1008},{0x9A, 0x1, 0x4B, 0xFF}}},
	{{{21, 16, 26},0, {-16, 1008},{0x9A, 0x1, 0x4B, 0xFF}}},
	{{{9, 14, 11},0, {-16, 1008},{0x9A, 0x1, 0x4B, 0xFF}}},
	{{{33, 11, -12},0, {-16, 1008},{0x29, 0x1, 0x78, 0xFF}}},
	{{{32, 16, -12},0, {-16, 1008},{0x29, 0x1, 0x78, 0xFF}}},
	{{{14, 14, -6},0, {-16, 1008},{0x29, 0x1, 0x78, 0xFF}}},
	{{{-1, 11, -36},0, {-16, 1008},{0x7F, 0x1, 0xFF, 0xFF}}},
	{{{-1, 16, -35},0, {-16, 1008},{0x7F, 0x1, 0xFF, 0xFF}}},
	{{{-1, 14, -16},0, {-16, 1008},{0x7F, 0x1, 0xFF, 0xFF}}},
	{{{-33, 11, -11},0, {-16, 1008},{0x26, 0x1, 0x87, 0xFF}}},
	{{{-33, 16, -11},0, {-16, 1008},{0x26, 0x1, 0x87, 0xFF}}},
	{{{-15, 14, -5},0, {-16, 1008},{0x26, 0x1, 0x87, 0xFF}}},
	{{{-20, 11, 28},0, {-16, 1008},{0x99, 0x1, 0xB6, 0xFF}}},
	{{{-20, 16, 27},0, {-16, 1008},{0x99, 0x1, 0xB6, 0xFF}}},
	{{{-9, 14, 12},0, {-16, 1008},{0x99, 0x1, 0xB6, 0xFF}}},
	{{{13, 36, 19},0, {-16, 1008},{0x95, 0xFF, 0x44, 0xFF}}},
	{{{10, 40, 15},0, {-16, 1008},{0x95, 0xFF, 0x44, 0xFF}}},
	{{{6, 28, 8},0, {-16, 1008},{0x95, 0xFF, 0x44, 0xFF}}},
	{{{23, 36, -7},0, {-16, 1008},{0x20, 0xFF, 0x7B, 0xFF}}},
	{{{18, 40, -6},0, {-16, 1008},{0x20, 0xFF, 0x7B, 0xFF}}},
	{{{10, 28, -4},0, {-16, 1008},{0x20, 0xFF, 0x7B, 0xFF}}},
	{{{1, 36, -25},0, {-16, 1008},{0x7F, 0xFF, 0x7, 0xFF}}},
	{{{1, 40, -20},0, {-16, 1008},{0x7F, 0xFF, 0x7, 0xFF}}},
	{{{0, 28, -11},0, {-16, 1008},{0x7F, 0xFF, 0x7, 0xFF}}},
	{{{-23, 36, -9},0, {-16, 1008},{0x2E, 0xFF, 0x8A, 0xFF}}},
	{{{-18, 40, -8},0, {-16, 1008},{0x2E, 0xFF, 0x8A, 0xFF}}},
	{{{-10, 28, -4},0, {-16, 1008},{0x2E, 0xFF, 0x8A, 0xFF}}},
	{{{-15, 36, 18},0, {-16, 1008},{0x9E, 0xFF, 0xB0, 0xFF}}},
	{{{-12, 40, 14},0, {-16, 1008},{0x9E, 0xFF, 0xB0, 0xFF}}},
	{{{-7, 28, 8},0, {-16, 1008},{0x9E, 0xFF, 0xB0, 0xFF}}},
	{{{0, 35, 0},0, {-16, 1008},{0x0, 0xF8, 0x7F, 0xFF}}},
	{{{2, 48, 1},0, {-16, 1008},{0x0, 0xF8, 0x7F, 0xFF}}},
	{{{-2, 48, 1},0, {-16, 1008},{0x0, 0xF8, 0x7F, 0xFF}}},
	{{{0, 35, 0},0, {-16, 1008},{0x6C, 0xF6, 0xBE, 0xFF}}},
	{{{0, 48, -2},0, {-16, 1008},{0x6C, 0xF6, 0xBE, 0xFF}}},
	{{{2, 48, 1},0, {-16, 1008},{0x6C, 0xF6, 0xBE, 0xFF}}},
	{{{0, 35, 0},0, {-16, 1008},{0x8F, 0xF4, 0xC7, 0xFF}}},
	{{{-2, 48, 1},0, {-16, 1008},{0x8F, 0xF4, 0xC7, 0xFF}}},
	{{{0, 48, -2},0, {-16, 1008},{0x8F, 0xF4, 0xC7, 0xFF}}},
};

Gfx bounceflower_Base_mesh_tri_1[] = {
	gsSPVertex(bounceflower_Base_mesh_vtx_1 + 0, 30, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 15, 16, 17, 0),
	gsSP2Triangles(18, 19, 20, 0, 21, 22, 23, 0),
	gsSP2Triangles(24, 25, 26, 0, 27, 28, 29, 0),
	gsSPVertex(bounceflower_Base_mesh_vtx_1 + 30, 24, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 9, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 15, 16, 17, 0),
	gsSP2Triangles(18, 19, 20, 0, 21, 22, 23, 0),
	gsSPEndDisplayList(),
};

Gfx bounceflower_Base_mesh[] = {
	gsSPDisplayList(mat_bounceflower_model_bounceorange),
	gsSPDisplayList(bounceflower_Base_mesh_tri_0),
	gsSPDisplayList(mat_revert_bounceflower_model_bounceorange),
	gsSPDisplayList(mat_bounceflower_model_extensions_2side),
	gsSPDisplayList(bounceflower_Base_mesh_tri_1),
	gsSPDisplayList(mat_revert_bounceflower_model_extensions_2side),
	gsSPEndDisplayList(),
};



Vtx bounceflower_Ext_mesh_vtx_0[3] = {
	{{{-6, -3, 2},0, {-182, 470},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{7, -3, 2},0, {662, 479},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{0, 8, 2},0, {240, -281},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx bounceflower_Ext_mesh_tri_0[] = {
	gsSPVertex(bounceflower_Ext_mesh_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};

Gfx bounceflower_Ext_mesh[] = {
	gsSPDisplayList(mat_bounceflower_model_extensions_billboard),
	gsSPDisplayList(bounceflower_Ext_mesh_tri_0),
	gsSPDisplayList(mat_revert_bounceflower_model_extensions_billboard),
	gsSPEndDisplayList(),
};



Vtx bounceflower_Ext_001_mesh_vtx_0[3] = {
	{{{-7, -3, 2},0, {-182, 470},{0x3, 0x0, 0x7F, 0xFF}}},
	{{{7, -3, 2},0, {662, 479},{0x3, 0x0, 0x7F, 0xFF}}},
	{{{0, 8, 2},0, {240, -281},{0x3, 0x0, 0x7F, 0xFF}}},
};

Gfx bounceflower_Ext_001_mesh_tri_0[] = {
	gsSPVertex(bounceflower_Ext_001_mesh_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};

Gfx bounceflower_Ext_001_mesh[] = {
	gsSPDisplayList(mat_bounceflower_model_extensions_billboard),
	gsSPDisplayList(bounceflower_Ext_001_mesh_tri_0),
	gsSPDisplayList(mat_revert_bounceflower_model_extensions_billboard),
	gsSPEndDisplayList(),
};



Vtx bounceflower_Ext_002_mesh_vtx_0[3] = {
	{{{-6, -3, 1},0, {-182, 470},{0xF8, 0x0, 0x7F, 0xFF}}},
	{{{7, -3, 2},0, {662, 479},{0xF8, 0x0, 0x7F, 0xFF}}},
	{{{0, 8, 2},0, {240, -281},{0xF8, 0x0, 0x7F, 0xFF}}},
};

Gfx bounceflower_Ext_002_mesh_tri_0[] = {
	gsSPVertex(bounceflower_Ext_002_mesh_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};

Gfx bounceflower_Ext_002_mesh[] = {
	gsSPDisplayList(mat_bounceflower_model_extensions_billboard),
	gsSPDisplayList(bounceflower_Ext_002_mesh_tri_0),
	gsSPDisplayList(mat_revert_bounceflower_model_extensions_billboard),
	gsSPEndDisplayList(),
};



Vtx bounceflower_Ext_003_mesh_vtx_0[3] = {
	{{{-7, -3, 3},0, {-182, 470},{0x14, 0x0, 0x7D, 0xFF}}},
	{{{7, -3, 1},0, {662, 479},{0x14, 0x0, 0x7D, 0xFF}}},
	{{{0, 8, 2},0, {240, -281},{0x14, 0x0, 0x7D, 0xFF}}},
};

Gfx bounceflower_Ext_003_mesh_tri_0[] = {
	gsSPVertex(bounceflower_Ext_003_mesh_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};

Gfx bounceflower_Ext_003_mesh[] = {
	gsSPDisplayList(mat_bounceflower_model_extensions_billboard),
	gsSPDisplayList(bounceflower_Ext_003_mesh_tri_0),
	gsSPDisplayList(mat_revert_bounceflower_model_extensions_billboard),
	gsSPEndDisplayList(),
};



Vtx bounceflower_Ext_004_mesh_vtx_0[3] = {
	{{{-6, -3, 2},0, {-182, 470},{0x1, 0x0, 0x7F, 0xFF}}},
	{{{7, -3, 2},0, {662, 479},{0x1, 0x0, 0x7F, 0xFF}}},
	{{{0, 8, 2},0, {240, -281},{0x1, 0x0, 0x7F, 0xFF}}},
};

Gfx bounceflower_Ext_004_mesh_tri_0[] = {
	gsSPVertex(bounceflower_Ext_004_mesh_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};

Gfx bounceflower_Ext_004_mesh[] = {
	gsSPDisplayList(mat_bounceflower_model_extensions_billboard),
	gsSPDisplayList(bounceflower_Ext_004_mesh_tri_0),
	gsSPDisplayList(mat_revert_bounceflower_model_extensions_billboard),
	gsSPEndDisplayList(),
};



Vtx bounceflower_Ext_005_mesh_vtx_0[3] = {
	{{{-7, -3, 2},0, {-182, 470},{0x4, 0x0, 0x7F, 0xFF}}},
	{{{7, -3, 2},0, {662, 479},{0x4, 0x0, 0x7F, 0xFF}}},
	{{{0, 8, 2},0, {240, -281},{0x4, 0x0, 0x7F, 0xFF}}},
};

Gfx bounceflower_Ext_005_mesh_tri_0[] = {
	gsSPVertex(bounceflower_Ext_005_mesh_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};

Gfx bounceflower_Ext_005_mesh[] = {
	gsSPDisplayList(mat_bounceflower_model_extensions_billboard),
	gsSPDisplayList(bounceflower_Ext_005_mesh_tri_0),
	gsSPDisplayList(mat_revert_bounceflower_model_extensions_billboard),
	gsSPEndDisplayList(),
};



Vtx bounceflower_Ext_007_mesh_vtx_0[3] = {
	{{{-7, -3, 2},0, {-182, 470},{0xFD, 0x0, 0x7F, 0xFF}}},
	{{{6, -3, 2},0, {662, 479},{0xFD, 0x0, 0x7F, 0xFF}}},
	{{{0, 8, 2},0, {240, -281},{0xFD, 0x0, 0x7F, 0xFF}}},
};

Gfx bounceflower_Ext_007_mesh_tri_0[] = {
	gsSPVertex(bounceflower_Ext_007_mesh_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};

Gfx bounceflower_Ext_007_mesh[] = {
	gsSPDisplayList(mat_bounceflower_model_extensions_billboard),
	gsSPDisplayList(bounceflower_Ext_007_mesh_tri_0),
	gsSPDisplayList(mat_revert_bounceflower_model_extensions_billboard),
	gsSPEndDisplayList(),
};



Vtx bounceflower_Ext_008_mesh_vtx_0[3] = {
	{{{-6, -3, 2},0, {-182, 470},{0x2, 0x0, 0x7F, 0xFF}}},
	{{{7, -3, 2},0, {662, 479},{0x2, 0x0, 0x7F, 0xFF}}},
	{{{0, 8, 2},0, {240, -281},{0x2, 0x0, 0x7F, 0xFF}}},
};

Gfx bounceflower_Ext_008_mesh_tri_0[] = {
	gsSPVertex(bounceflower_Ext_008_mesh_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};

Gfx bounceflower_Ext_008_mesh[] = {
	gsSPDisplayList(mat_bounceflower_model_extensions_billboard),
	gsSPDisplayList(bounceflower_Ext_008_mesh_tri_0),
	gsSPDisplayList(mat_revert_bounceflower_model_extensions_billboard),
	gsSPEndDisplayList(),
};



Vtx bounceflower_Ext_009_mesh_vtx_0[3] = {
	{{{-7, -3, 2},0, {-182, 470},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{7, -3, 2},0, {662, 479},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{0, 8, 2},0, {240, -281},{0x0, 0x0, 0x7F, 0xFF}}},
};

Gfx bounceflower_Ext_009_mesh_tri_0[] = {
	gsSPVertex(bounceflower_Ext_009_mesh_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};

Gfx bounceflower_Ext_009_mesh[] = {
	gsSPDisplayList(mat_bounceflower_model_extensions_billboard),
	gsSPDisplayList(bounceflower_Ext_009_mesh_tri_0),
	gsSPDisplayList(mat_revert_bounceflower_model_extensions_billboard),
	gsSPEndDisplayList(),
};



Vtx bounceflower_Ext_010_mesh_vtx_0[3] = {
	{{{-6, -3, 2},0, {-182, 470},{0xFD, 0x0, 0x7F, 0xFF}}},
	{{{7, -3, 2},0, {662, 479},{0xFD, 0x0, 0x7F, 0xFF}}},
	{{{0, 8, 2},0, {240, -281},{0xFD, 0x0, 0x7F, 0xFF}}},
};

Gfx bounceflower_Ext_010_mesh_tri_0[] = {
	gsSPVertex(bounceflower_Ext_010_mesh_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};

Gfx bounceflower_Ext_010_mesh[] = {
	gsSPDisplayList(mat_bounceflower_model_extensions_billboard),
	gsSPDisplayList(bounceflower_Ext_010_mesh_tri_0),
	gsSPDisplayList(mat_revert_bounceflower_model_extensions_billboard),
	gsSPEndDisplayList(),
};



Vtx bounceflower_Ext_011_mesh_vtx_0[3] = {
	{{{-7, -4, 3},0, {-182, 470},{0xF7, 0x0, 0x7F, 0xFF}}},
	{{{6, -4, 4},0, {662, 479},{0xF7, 0x0, 0x7F, 0xFF}}},
	{{{0, 8, 4},0, {240, -281},{0xF7, 0x0, 0x7F, 0xFF}}},
};

Gfx bounceflower_Ext_011_mesh_tri_0[] = {
	gsSPVertex(bounceflower_Ext_011_mesh_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};

Gfx bounceflower_Ext_011_mesh[] = {
	gsSPDisplayList(mat_bounceflower_model_extensions_billboard),
	gsSPDisplayList(bounceflower_Ext_011_mesh_tri_0),
	gsSPDisplayList(mat_revert_bounceflower_model_extensions_billboard),
	gsSPEndDisplayList(),
};



Vtx bounceflower_Ext_012_mesh_vtx_0[3] = {
	{{{-7, -4, 3},0, {-182, 470},{0xFB, 0x0, 0x7F, 0xFF}}},
	{{{6, -4, 4},0, {662, 479},{0xFB, 0x0, 0x7F, 0xFF}}},
	{{{0, 8, 4},0, {240, -281},{0xFB, 0x0, 0x7F, 0xFF}}},
};

Gfx bounceflower_Ext_012_mesh_tri_0[] = {
	gsSPVertex(bounceflower_Ext_012_mesh_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};

Gfx bounceflower_Ext_012_mesh[] = {
	gsSPDisplayList(mat_bounceflower_model_extensions_billboard),
	gsSPDisplayList(bounceflower_Ext_012_mesh_tri_0),
	gsSPDisplayList(mat_revert_bounceflower_model_extensions_billboard),
	gsSPEndDisplayList(),
};



Vtx bounceflower_Ext_013_mesh_vtx_0[3] = {
	{{{-7, -4, 3},0, {-182, 470},{0xF1, 0x0, 0x7E, 0xFF}}},
	{{{6, -4, 4},0, {662, 479},{0xF1, 0x0, 0x7E, 0xFF}}},
	{{{-1, 8, 4},0, {240, -281},{0xF1, 0x0, 0x7E, 0xFF}}},
};

Gfx bounceflower_Ext_013_mesh_tri_0[] = {
	gsSPVertex(bounceflower_Ext_013_mesh_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};

Gfx bounceflower_Ext_013_mesh[] = {
	gsSPDisplayList(mat_bounceflower_model_extensions_billboard),
	gsSPDisplayList(bounceflower_Ext_013_mesh_tri_0),
	gsSPDisplayList(mat_revert_bounceflower_model_extensions_billboard),
	gsSPEndDisplayList(),
};



Vtx bounceflower_Ext_014_mesh_vtx_0[3] = {
	{{{-7, -4, 3},0, {-182, 470},{0xF1, 0x0, 0x7E, 0xFF}}},
	{{{6, -4, 4},0, {662, 479},{0xF1, 0x0, 0x7E, 0xFF}}},
	{{{-1, 8, 4},0, {240, -281},{0xF1, 0x0, 0x7E, 0xFF}}},
};

Gfx bounceflower_Ext_014_mesh_tri_0[] = {
	gsSPVertex(bounceflower_Ext_014_mesh_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};

Gfx bounceflower_Ext_014_mesh[] = {
	gsSPDisplayList(mat_bounceflower_model_extensions_billboard),
	gsSPDisplayList(bounceflower_Ext_014_mesh_tri_0),
	gsSPDisplayList(mat_revert_bounceflower_model_extensions_billboard),
	gsSPEndDisplayList(),
};



Vtx bounceflower_Ext_015_mesh_vtx_0[3] = {
	{{{-7, -4, 3},0, {-182, 470},{0xF9, 0x0, 0x7F, 0xFF}}},
	{{{6, -4, 4},0, {662, 479},{0xF9, 0x0, 0x7F, 0xFF}}},
	{{{0, 8, 4},0, {240, -281},{0xF9, 0x0, 0x7F, 0xFF}}},
};

Gfx bounceflower_Ext_015_mesh_tri_0[] = {
	gsSPVertex(bounceflower_Ext_015_mesh_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};

Gfx bounceflower_Ext_015_mesh[] = {
	gsSPDisplayList(mat_bounceflower_model_extensions_billboard),
	gsSPDisplayList(bounceflower_Ext_015_mesh_tri_0),
	gsSPDisplayList(mat_revert_bounceflower_model_extensions_billboard),
	gsSPEndDisplayList(),
};



Vtx bounceflower_Ext_016_mesh_vtx_0[3] = {
	{{{-6, -3, 3},0, {-182, 470},{0xFF, 0x0, 0x7F, 0xFF}}},
	{{{6, -4, 3},0, {662, 479},{0xFF, 0x0, 0x7F, 0xFF}}},
	{{{0, 8, 3},0, {240, -281},{0xFF, 0x0, 0x7F, 0xFF}}},
};

Gfx bounceflower_Ext_016_mesh_tri_0[] = {
	gsSPVertex(bounceflower_Ext_016_mesh_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};

Gfx bounceflower_Ext_016_mesh[] = {
	gsSPDisplayList(mat_bounceflower_model_extensions_billboard),
	gsSPDisplayList(bounceflower_Ext_016_mesh_tri_0),
	gsSPDisplayList(mat_revert_bounceflower_model_extensions_billboard),
	gsSPEndDisplayList(),
};




BoneLayer bounceflower_model_bone0_layers[] = {
    {
        0,
        bounceflower_Root_mesh,
    },
};
BoneLayer bounceflower_model_bone1_layers[] = {
    {
        0,
        bounceflower_Base_mesh,
    },
};
BoneLayer bounceflower_model_bone2_layers[] = {
    {
        3,
        bounceflower_Ext_mesh,
    },
};
BoneLayer bounceflower_model_bone3_layers[] = {
    {
        3,
        bounceflower_Ext_001_mesh,
    },
};
BoneLayer bounceflower_model_bone4_layers[] = {
    {
        3,
        bounceflower_Ext_002_mesh,
    },
};
BoneLayer bounceflower_model_bone5_layers[] = {
    {
        3,
        bounceflower_Ext_003_mesh,
    },
};
BoneLayer bounceflower_model_bone6_layers[] = {
    {
        3,
        bounceflower_Ext_004_mesh,
    },
};
BoneLayer bounceflower_model_bone7_layers[] = {
    {
        3,
        bounceflower_Ext_005_mesh,
    },
};
BoneLayer bounceflower_model_bone8_layers[] = {
    {
        3,
        bounceflower_Ext_007_mesh,
    },
};
BoneLayer bounceflower_model_bone9_layers[] = {
    {
        3,
        bounceflower_Ext_008_mesh,
    },
};
BoneLayer bounceflower_model_bone10_layers[] = {
    {
        3,
        bounceflower_Ext_009_mesh,
    },
};
BoneLayer bounceflower_model_bone11_layers[] = {
    {
        3,
        bounceflower_Ext_010_mesh,
    },
};
BoneLayer bounceflower_model_bone12_layers[] = {
    {
        3,
        bounceflower_Ext_011_mesh,
    },
};
BoneLayer bounceflower_model_bone13_layers[] = {
    {
        3,
        bounceflower_Ext_012_mesh,
    },
};
BoneLayer bounceflower_model_bone14_layers[] = {
    {
        3,
        bounceflower_Ext_013_mesh,
    },
};
BoneLayer bounceflower_model_bone15_layers[] = {
    {
        3,
        bounceflower_Ext_014_mesh,
    },
};
BoneLayer bounceflower_model_bone16_layers[] = {
    {
        3,
        bounceflower_Ext_015_mesh,
    },
};
BoneLayer bounceflower_model_bone17_layers[] = {
    {
        3,
        bounceflower_Ext_016_mesh,
    },
};

Bone bounceflower_model_bones[] = {
    {
        0,
        255,
        1,
        0,
        0.0,
        0.0,
        0.0,
        bounceflower_model_bone0_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        1,
        0,
        1,
        0,
        0.0,
        3.6391024589538574,
        -1.5907022543615312e-07,
        bounceflower_model_bone1_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        2,
        1,
        1,
        0,
        -0.771531343460083,
        13.191165924072266,
        -35.45782470703125,
        bounceflower_model_bone2_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        3,
        1,
        1,
        0,
        -17.82448387145996,
        23.51617431640625,
        -23.424348831176758,
        bounceflower_model_bone3_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        4,
        1,
        1,
        0,
        -33.25010681152344,
        13.191167831420898,
        -10.92103385925293,
        bounceflower_model_bone4_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        5,
        1,
        1,
        0,
        -27.075241088867188,
        23.51617431640625,
        9.015835762023926,
        bounceflower_model_bone5_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        6,
        1,
        1,
        0,
        -19.950660705566406,
        13.191170692443848,
        27.55021858215332,
        bounceflower_model_bone6_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        7,
        1,
        1,
        0,
        0.9185671806335449,
        23.516176223754883,
        27.83839988708496,
        bounceflower_model_bone7_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        8,
        1,
        1,
        0,
        27.4704532623291,
        23.51617431640625,
        7.031193733215332,
        bounceflower_model_bone8_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        9,
        1,
        1,
        0,
        20.74742889404297,
        13.191170692443848,
        26.789960861206055,
        bounceflower_model_bone9_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        10,
        1,
        1,
        0,
        15.88660717010498,
        23.51617431640625,
        -24.65092658996582,
        bounceflower_model_bone10_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        11,
        1,
        1,
        0,
        32.60078048706055,
        13.191167831420898,
        -12.151156425476074,
        bounceflower_model_bone11_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        12,
        1,
        1,
        0,
        0.6020684242248535,
        37.8428955078125,
        -22.373380661010742,
        bounceflower_model_bone12_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        13,
        1,
        1,
        0,
        -20.381587982177734,
        37.8428955078125,
        -8.184087753295898,
        bounceflower_model_bone13_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        14,
        1,
        1,
        0,
        -13.371084213256836,
        37.8428955078125,
        16.157291412353516,
        bounceflower_model_bone14_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        15,
        1,
        1,
        0,
        11.9453125,
        37.8428955078125,
        17.011796951293945,
        bounceflower_model_bone15_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        16,
        1,
        1,
        0,
        20.581195831298828,
        37.8428955078125,
        -6.801467418670654,
        bounceflower_model_bone16_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        17,
        1,
        1,
        0,
        -0.03601888194680214,
        48.7005615234375,
        -0.24824075400829315,
        bounceflower_model_bone17_layers,
        NULL,
        NULL,
        NULL,
    },
};

Model bounceflower_model = {
    18,
    0,
    bounceflower_model_bones
};

