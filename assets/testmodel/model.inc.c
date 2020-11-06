Gfx testmodelBone0LayerOpa[] = {
	gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetFillColor(GPACK_RGBA5551(0xFF, 0x00, 0x00, 1) << 16 | GPACK_RGBA5551(0xFF, 0x00, 0x00, 1)),
    gsDPFillRectangle(10, 10, 20, 20),
	gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
	gsSPEndDisplayList(),
};

BoneLayer testmodelBone0Layers[] = {
    {
        LAYER_OPA_SURF, // layer
        testmodelBone0LayerOpa, // displaylist
    }
};

Bone testmodelBones[] = {
    {
        0, // index
        0xFF, // parent
        1, // number of layers
        0, // reserved
        testmodelBone0Layers,
        NULL,
    }
};

Model testmodel = {
    1, // numBones
    0, // reserved
    testmodelBones,
};
