#ifndef __MODEL_H__
#define __MODEL_H__

#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include <types.h>

// Draw layers
#define LAYER_OPA_SURF  0
#define LAYER_OPA_DECAL 1
#define LAYER_TEX_EDGE  2
#define LAYER_XLU_SURF  3
#define LAYER_XLU_DECAL 4

typedef struct BoneLayer_t {
    u32 layer;        // Draw layer of this displaylist
    Gfx *displaylist; // Displaylist for this layer of the bone
} BoneLayer;


typedef struct Bone_t {
    u8 index;    // Not strictly needed, but helpful to save time during processing
    u8 parent;   // Index of the parent bone
    u8 numLayers;   // Number of layers this bone is present on
    u8 reserved; // For future use
    BoneLayer *layers; // Segmented pointer to the start of the displaylist array (of length layers)
    Gfx *(*beforeCb)(Bone* bone, BoneLayer *layer); // Callback before drawing a layer of this bone, can return a displaylist to prepend before the bone
    Gfx *(*afterCb) (Bone* bone, BoneLayer *layer); // Callback after drawing a layer of this bone, can return a displaylist to append after the bone
    MtxF *matrix; // Used during rendering for hierarchical rendering
} Bone;

typedef struct Model_t {
    u16 numBones; // Bone count
    u16 reserved; // For future use
    Bone* bones;  // Segmented pointer to the start of the bone array (of length numBones)
} Model;

#endif
