
Gfx character_arm_model_shading_i4_aligner[] = {gsSPEndDisplayList()};
u8 character_arm_model_shading_i4[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xBB, 0x77, 0x77, 
};


Gfx mat_character_arm_model_base_toon_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, ENVIRONMENT, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, ENVIRONMENT),
	gsSPSetGeometryMode(G_TEXTURE_GEN),
	gsDPSetTextureFilter(G_TF_POINT),
	gsSPTexture(959, 0, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 8, character_arm_model_shading_i4),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 30, 0),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 0, 0, G_TX_CLAMP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 0),
	gsDPSetPrimColor(0, 0, 227, 222, 211, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_character_arm_model_base_toon_f3d[] = {
	gsDPPipeSync(),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetTextureFilter(G_TF_BILERP),
	gsSPEndDisplayList(),
};


Gfx mat_character_arm_model_h_env_dark[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(1, 0, ENVIRONMENT, 0, 0, 0, 0, ENVIRONMENT, 1, 0, ENVIRONMENT, 0, 0, 0, 0, ENVIRONMENT),
	gsSPSetGeometryMode(G_TEXTURE_GEN),
	gsSPTexture(447, 0, 0, 0, 1),
	gsDPSetEnvColor(138, 218, 220, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_character_arm_model_h_env_dark[] = {
	gsDPPipeSync(),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsSPEndDisplayList(),
};


Gfx mat_character_arm_model_h_env[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(1, 0, ENVIRONMENT, 0, 0, 0, 0, ENVIRONMENT, 1, 0, ENVIRONMENT, 0, 0, 0, 0, ENVIRONMENT),
	gsSPSetGeometryMode(G_TEXTURE_GEN),
	gsSPClearGeometryMode(G_LIGHTING),
	gsDPSetTextureFilter(G_TF_POINT),
	gsSPTexture(447, 0, 0, 0, 1),
	gsDPSetEnvColor(173, 251, 254, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_character_arm_model_h_env[] = {
	gsDPPipeSync(),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsSPSetGeometryMode(G_LIGHTING),
	gsDPSetTextureFilter(G_TF_BILERP),
	gsSPEndDisplayList(),
};



Vtx character_arm_Arm_1_mesh_vtx_0[16] = {
	{{{-20, 5, 8},0, {320, 32},{0x8C, 0x1C, 0x2D, 0xFF}}},
	{{{-10, -15, 3},0, {192, 24},{0xC4, 0x92, 0x18, 0xFF}}},
	{{{-1, -4, 19},0, {192, 32},{0xFC, 0xD4, 0x77, 0xFF}}},
	{{{-10, -6, -19},0, {320, 24},{0xC4, 0xDF, 0x95, 0xFF}}},
	{{{-5, 18, -9},0, {320, 24},{0xDF, 0x6D, 0xC8, 0xFF}}},
	{{{8, -15, -8},0, {192, 16},{0x33, 0x93, 0xD7, 0xFF}}},
	{{{18, 5, -13},0, {320, 16},{0x61, 0x1F, 0xB4, 0xFF}}},
	{{{-5, 18, -9},0, {320, 16},{0xDF, 0x6D, 0xC8, 0xFF}}},
	{{{18, -4, 8},0, {192, 8},{0x6A, 0xD4, 0x37, 0xFF}}},
	{{{8, 16, 14},0, {320, 8},{0x2B, 0x5C, 0x4C, 0xFF}}},
	{{{-5, 18, -9},0, {320, 8},{0xDF, 0x6D, 0xC8, 0xFF}}},
	{{{-1, -4, 19},0, {192, 0},{0xFC, 0xD4, 0x77, 0xFF}}},
	{{{-20, 5, 8},0, {320, 0},{0x8C, 0x1C, 0x2D, 0xFF}}},
	{{{-5, 18, -9},0, {320, 0},{0xDF, 0x6D, 0xC8, 0xFF}}},
	{{{-1, -4, 19},0, {64, 8},{0xFC, 0xD4, 0x77, 0xFF}}},
	{{{-10, -15, 3},0, {64, 16},{0xC4, 0x92, 0x18, 0xFF}}},
};

Gfx character_arm_Arm_1_mesh_tri_0[] = {
	gsSPVertex(character_arm_Arm_1_mesh_vtx_0 + 0, 16, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
	gsSP2Triangles(3, 0, 4, 0, 3, 5, 1, 0),
	gsSP2Triangles(3, 6, 5, 0, 6, 3, 7, 0),
	gsSP2Triangles(6, 8, 5, 0, 6, 9, 8, 0),
	gsSP2Triangles(9, 6, 10, 0, 9, 11, 8, 0),
	gsSP2Triangles(9, 12, 11, 0, 12, 9, 13, 0),
	gsSP2Triangles(5, 14, 15, 0, 5, 8, 14, 0),
	gsSPEndDisplayList(),
};

Gfx character_arm_Arm_1_mesh[] = {
	gsSPDisplayList(mat_character_arm_model_base_toon_f3d),
	gsSPDisplayList(character_arm_Arm_1_mesh_tri_0),
	gsSPDisplayList(mat_revert_character_arm_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx character_arm_Arm_2_mesh_vtx_0[14] = {
	{{{3, 18, -9},0, {192, 16},{0x10, 0x7C, 0xE8, 0xFF}}},
	{{{12, 9, 4},0, {192, 8},{0x53, 0x3B, 0x4B, 0xFF}}},
	{{{14, 5, -13},0, {64, 8},{0x68, 0x1F, 0xBE, 0xFF}}},
	{{{-14, 7, 7},0, {320, 16},{0xB1, 0x30, 0x58, 0xFF}}},
	{{{-15, 6, -20},0, {320, 24},{0xAD, 0x1B, 0xA4, 0xFF}}},
	{{{14, 5, -13},0, {192, 24},{0x68, 0x1F, 0xBE, 0xFF}}},
	{{{10, -9, -16},0, {320, 32},{0x3E, 0xB6, 0xAE, 0xFF}}},
	{{{-14, -13, -1},0, {320, 24},{0xAE, 0xA1, 0x13, 0xFF}}},
	{{{-14, -13, -1},0, {320, 16},{0xAE, 0xA1, 0x13, 0xFF}}},
	{{{10, -9, -16},0, {320, 0},{0x3E, 0xB6, 0xAE, 0xFF}}},
	{{{9, -12, 8},0, {320, 8},{0x3B, 0xB2, 0x52, 0xFF}}},
	{{{-14, -13, -1},0, {320, 0},{0xAE, 0xA1, 0x13, 0xFF}}},
	{{{14, 5, -13},0, {192, 0},{0x68, 0x1F, 0xBE, 0xFF}}},
	{{{-14, -13, -1},0, {320, 8},{0xAE, 0xA1, 0x13, 0xFF}}},
};

Gfx character_arm_Arm_2_mesh_tri_0[] = {
	gsSPVertex(character_arm_Arm_2_mesh_vtx_0 + 0, 14, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
	gsSP2Triangles(4, 3, 0, 0, 4, 0, 5, 0),
	gsSP2Triangles(6, 4, 5, 0, 4, 6, 7, 0),
	gsSP2Triangles(3, 4, 8, 0, 9, 10, 11, 0),
	gsSP2Triangles(10, 9, 12, 0, 10, 12, 1, 0),
	gsSP2Triangles(3, 10, 1, 0, 10, 3, 13, 0),
	gsSPEndDisplayList(),
};

Gfx character_arm_Arm_2_mesh[] = {
	gsSPDisplayList(mat_character_arm_model_base_toon_f3d),
	gsSPDisplayList(character_arm_Arm_2_mesh_tri_0),
	gsSPDisplayList(mat_revert_character_arm_model_base_toon_f3d),
	gsSPEndDisplayList(),
};



Vtx character_arm_Hand_mesh_vtx_0[21] = {
	{{{21, 0, 20},0, {496, 752},{0x19, 0x91, 0xC7, 0xFF}}},
	{{{21, 0, -22},0, {496, 496},{0x35, 0xD5, 0x6B, 0xFF}}},
	{{{0, 30, -1},0, {368, 752},{0x90, 0xD3, 0x27, 0xFF}}},
	{{{-21, 0, -22},0, {496, 240},{0xE7, 0x6F, 0x39, 0xFF}}},
	{{{-21, 0, 20},0, {496, -16},{0xCB, 0x2B, 0x95, 0xFF}}},
	{{{0, 30, -1},0, {368, 240},{0x90, 0xD3, 0x27, 0xFF}}},
	{{{-21, 0, 20},0, {496, 1008},{0xCB, 0x2B, 0x95, 0xFF}}},
	{{{0, -30, -1},0, {624, 752},{0x70, 0x2D, 0xD9, 0xFF}}},
	{{{0, -30, -1},0, {624, 240},{0x70, 0x2D, 0xD9, 0xFF}}},
	{{{21, 15, -1},0, {368, 496},{0x13, 0x74, 0x31, 0xFF}}},
	{{{0, 15, -22},0, {368, 240},{0x7C, 0x11, 0x16, 0xFF}}},
	{{{-21, 15, -1},0, {112, 240},{0x40, 0xF5, 0x93, 0xFF}}},
	{{{0, 15, 20},0, {112, 496},{0xD7, 0x57, 0xAD, 0xFF}}},
	{{{-21, -15, -1},0, {624, -16},{0xED, 0x8C, 0xCF, 0xFF}}},
	{{{-21, 15, -1},0, {368, -16},{0x40, 0xF5, 0x93, 0xFF}}},
	{{{0, -15, -22},0, {624, 240},{0x29, 0xA9, 0x53, 0xFF}}},
	{{{0, -15, 20},0, {880, 496},{0x84, 0xEF, 0xEA, 0xFF}}},
	{{{-21, -15, -1},0, {880, 240},{0xED, 0x8C, 0xCF, 0xFF}}},
	{{{21, -15, -1},0, {624, 496},{0xC0, 0xB, 0x6D, 0xFF}}},
	{{{0, 15, 20},0, {368, 752},{0xD7, 0x57, 0xAD, 0xFF}}},
	{{{0, -15, 20},0, {624, 752},{0x84, 0xEF, 0xEA, 0xFF}}},
};

Gfx character_arm_Hand_mesh_tri_0[] = {
	gsSPVertex(character_arm_Hand_mesh_vtx_0 + 0, 21, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 0, 0, 1, 8, 3, 0),
	gsSP2Triangles(9, 10, 11, 0, 9, 11, 12, 0),
	gsSP2Triangles(13, 14, 10, 0, 13, 10, 15, 0),
	gsSP2Triangles(16, 17, 15, 0, 16, 15, 18, 0),
	gsSP2Triangles(18, 9, 19, 0, 18, 19, 20, 0),
	gsSPEndDisplayList(),
};Vtx character_arm_Hand_mesh_vtx_1[17] = {
	{{{-21, 0, 20},0, {512, 1024},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{21, 0, 20},0, {512, 768},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, 30, -1},0, {384, 1024},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{21, 0, -22},0, {512, 512},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-21, 0, -22},0, {512, 256},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, 30, -1},0, {384, 512},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, -30, -1},0, {640, 512},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, -30, -1},0, {640, 0},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-21, 0, 20},0, {512, 0},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-21, 15, -1},0, {384, 1024},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{-21, -15, -1},0, {640, 1024},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, -15, 20},0, {640, 768},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, 15, 20},0, {384, 768},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{21, 15, -1},0, {384, 512},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, -15, -22},0, {640, 256},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{0, 15, -22},0, {384, 256},{0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{21, -15, -1},0, {640, 512},{0xFF, 0xFF, 0xFF, 0xFF}}},
};

Gfx character_arm_Hand_mesh_tri_1[] = {
	gsSPVertex(character_arm_Hand_mesh_vtx_1 + 0, 17, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
	gsSP2Triangles(1, 6, 3, 0, 4, 7, 8, 0),
	gsSP2Triangles(9, 10, 11, 0, 9, 11, 12, 0),
	gsSP2Triangles(13, 14, 15, 0, 13, 16, 14, 0),
	gsSPEndDisplayList(),
};

Gfx character_arm_Hand_mesh[] = {
	gsSPDisplayList(mat_character_arm_model_h_env_dark),
	gsSPDisplayList(character_arm_Hand_mesh_tri_0),
	gsSPDisplayList(mat_revert_character_arm_model_h_env_dark),
	gsSPDisplayList(mat_character_arm_model_h_env),
	gsSPDisplayList(character_arm_Hand_mesh_tri_1),
	gsSPDisplayList(mat_revert_character_arm_model_h_env),
	gsSPEndDisplayList(),
};




BoneLayer character_arm_model_bone1_layers[] = {
    {
        0,
        character_arm_Arm_1_mesh,
    },
};
BoneLayer character_arm_model_bone2_layers[] = {
    {
        0,
        character_arm_Arm_2_mesh,
    },
};
BoneLayer character_arm_model_bone3_layers[] = {
    {
        0,
        character_arm_Hand_mesh,
    },
};

Bone character_arm_model_bones[] = {
    {
        0,
        255,
        0,
        0,
        0.09482979774475098,
        106.28129577636719,
        0.06875661015510559,
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
        -57.60608673095703,
        -5.496072769165039,
        1.3452813625335693,
        character_arm_model_bone1_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        2,
        0,
        1,
        0,
        -94.40937042236328,
        -5.496072769165039,
        1.3452813625335693,
        character_arm_model_bone2_layers,
        NULL,
        NULL,
        NULL,
    },
    {
        3,
        0,
        1,
        0,
        -132.52743530273438,
        -5.496072769165039,
        1.3452813625335693,
        character_arm_model_bone3_layers,
        NULL,
        NULL,
        NULL,
    },
};

Model character_arm_model = {
    4,
    0,
    character_arm_model_bones
};

