s16 treevineleaf_anim_tvleaf_shrinkBone1Tables[] = {
    // RotX
    0xDFB8, 0xDFB8, 0xDFC4, 0xDFE7, 0xE01F, 0xE06D, 0xE0CE, 0xE142, 0xE1C8, 0xE25F, 0xE306, 0xE3BC, 0xE480, 0xE551, 0xE62E, 0xE716, 
    0xE807, 0xE902, 0xEA04, 0xEB0C, 0xEC1A, 0xED2C, 0xEE41, 0xEF57, 0xF06E, 0xF185, 0xF29A, 0xF3AB, 0xF4B8, 0xF5C0, 0xF6C1, 0xF7BB, 
    0xF8AC, 0xF993, 0xFA6F, 0xFB3F, 0xFC02, 0xFCB7, 0xFD5D, 0xFDF3, 0xFE78, 0xFEEB, 0xFF4C, 0xFF99, 0xFFD1, 0xFFF3, 0x0000, 
    // RotY
    0xFDEE, 0xFDEE, 0xFDEF, 0xFDEF, 0xFDF0, 0xFDF2, 0xFDF4, 0xFDF6, 0xFDF9, 0xFDFD, 0xFE01, 0xFE07, 0xFE0D, 0xFE14, 0xFE1C, 0xFE25, 
    0xFE2F, 0xFE3A, 0xFE46, 0xFE53, 0xFE62, 0xFE71, 0xFE82, 0xFE93, 0xFEA6, 0xFEB9, 0xFECC, 0xFEE1, 0xFEF6, 0xFF0B, 0xFF20, 0xFF35, 
    0xFF4A, 0xFF5F, 0xFF73, 0xFF86, 0xFF99, 0xFFAA, 0xFFBB, 0xFFC9, 0xFFD7, 0xFFE3, 0xFFEC, 0xFFF4, 0xFFFA, 0xFFFE, 0x0000, 
    // RotZ
    0x0386, 0x0386, 0x0384, 0x0380, 0x0378, 0x036E, 0x0362, 0x0353, 0x0342, 0x032F, 0x031A, 0x0303, 0x02EA, 0x02D0, 0x02B4, 0x0298, 
    0x027A, 0x025B, 0x023C, 0x021D, 0x01FD, 0x01DD, 0x01BD, 0x019D, 0x017E, 0x015F, 0x0141, 0x0124, 0x0108, 0x00ED, 0x00D3, 0x00BB, 
    0x00A3, 0x008E, 0x0079, 0x0066, 0x0055, 0x0045, 0x0037, 0x002A, 0x001F, 0x0016, 0x000E, 0x0008, 0x0004, 0x0001, 0x0000, 
    // ScaleX
    0x0504, 0x0504, 0x0503, 0x0501, 0x04FE, 0x04FA, 0x04F4, 0x04EC, 0x04E4, 0x04D9, 0x04CE, 0x04C0, 0x04B1, 0x04A0, 0x048E, 0x0479, 
    0x0463, 0x044B, 0x0431, 0x0415, 0x03F8, 0x03D8, 0x03B7, 0x0394, 0x0370, 0x034A, 0x0323, 0x02FB, 0x02D2, 0x02A9, 0x0280, 0x0258, 
    0x0230, 0x0209, 0x01E4, 0x01C1, 0x01A1, 0x0182, 0x0167, 0x014F, 0x013A, 0x0128, 0x0119, 0x010E, 0x0106, 0x0102, 0x0100, 
    // ScaleY
    0x0504, 0x0504, 0x0502, 0x04FE, 0x04F6, 0x04ED, 0x04E0, 0x04D2, 0x04C1, 0x04AE, 0x0499, 0x0482, 0x0469, 0x044F, 0x0434, 0x0417, 
    0x03F9, 0x03DA, 0x03BA, 0x039A, 0x0379, 0x0357, 0x0335, 0x0313, 0x02F1, 0x02CE, 0x02AD, 0x028B, 0x026A, 0x0249, 0x0229, 0x020A, 
    0x01EC, 0x01D0, 0x01B4, 0x019A, 0x0182, 0x016B, 0x0156, 0x0143, 0x0132, 0x0123, 0x0117, 0x010D, 0x0106, 0x0102, 0x0100, 
    // ScaleZ
    0x0504, 0x0504, 0x0502, 0x04FE, 0x04F6, 0x04ED, 0x04E0, 0x04D2, 0x04C1, 0x04AE, 0x0499, 0x0482, 0x0469, 0x044F, 0x0434, 0x0417, 
    0x03F9, 0x03DA, 0x03BA, 0x039A, 0x0379, 0x0357, 0x0335, 0x0313, 0x02F1, 0x02CE, 0x02AD, 0x028B, 0x026A, 0x0249, 0x0229, 0x020A, 
    0x01EC, 0x01D0, 0x01B4, 0x019A, 0x0182, 0x016B, 0x0156, 0x0143, 0x0132, 0x0123, 0x0117, 0x010D, 0x0106, 0x0102, 0x0100, 

};
BoneTable treevineleaf_anim_tvleaf_shrinkTables[] = {
    {
        0,
        NULL
    },
    {
        CHANNEL_ROT_X | CHANNEL_ROT_Y | CHANNEL_ROT_Z | CHANNEL_SCALE_X | CHANNEL_SCALE_Y | CHANNEL_SCALE_Z,
        treevineleaf_anim_tvleaf_shrinkBone1Tables
    },
};

Animation treevineleaf_anim_tvleaf_shrink = {
    47, // frame count
    2, // bone count
    ANIM_LOOP, // flags
    treevineleaf_anim_tvleaf_shrinkTables, // bone table array pointer
    NULL, // trigger array pointer
};
