#ifndef __MODEL_H__
#define __MODEL_H__

#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include <types.h>

///////////////////
// Model defines //
///////////////////

typedef struct BoneLayer_t {
    u32 layer;        // Draw layer of this displaylist
    Gfx *displaylist; // Displaylist for this layer of the bone
} BoneLayer;

typedef struct Bone_t {
    u8 index;    // Not strictly needed, but helpful to save time during processing
    u8 parent;   // Index of the parent bone
    u8 numLayers;   // Number of layers this bone is present on
    u8 reserved; // For future use
    float posX; // Base positional offset x component (float to save conversion time later on)
    float posY; // Base positional offset y component
    float posZ; // Base positional offset y component
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

///////////////////////
// Animation defines //
///////////////////////

// Animation flags
#define ANIM_LOOP (1 << 0)
#define ANIM_HAS_TRIGGERS (1 << 1)

// Bone table flags
#define CHANNEL_POS_X (1 << 0)
#define CHANNEL_POS_Y (1 << 1)
#define CHANNEL_POS_Z (1 << 2)
#define CHANNEL_ROT_X (1 << 3)
#define CHANNEL_ROT_Y (1 << 4)
#define CHANNEL_ROT_Z (1 << 5)
#define CHANNEL_SCALE_X (1 << 6)
#define CHANNEL_SCALE_Y (1 << 7)
#define CHANNEL_SCALE_Z (1 << 8)

typedef struct Animation_t {
    u16 frameCount; // The number of frames of data this animation has
    u8 boneCount; // Number of bones this animation has data for
    u8 flags; // Flags for this animation
    BoneTable *boneTables; // Segmented pointer to the array of bone animation tables
    AnimTrigger *triggers; // Segmented pointer to the array of triggers for this animation
} Animation;

typedef struct BoneTable_t {
    u32 flags; // Flags to specify which channels are encoded in this bone's animation data
    s16 *channels; // Segmented pointer to the array of all channel data
} BoneTable;

typedef struct AnimTrigger_t {
    u32 frame; // The frame at which this trigger should run
    void (*triggerCb)(Model* model, u32 frame); // The callback to run at the specified frame
} AnimTrigger;

#endif
