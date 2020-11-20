#ifndef __TYPES_H__
#define __TYPES_H__

// Prototypes for model structs
typedef struct BoneLayer_t BoneLayer;
typedef struct Bone_t Bone;
typedef struct Model_t Model;

// Prototypes for animation structs
typedef struct Animation_t Animation;
typedef struct BoneTable_t BoneTable;
typedef struct AnimTrigger_t AnimTrigger;

// Prototypes for collision structs
typedef struct AABB_t AABB;
typedef struct ColTri_t ColTri;
typedef struct BVHNodeBase_t BVHNodeBase;
typedef struct BVHParentNode_t BVHParentNode;
typedef struct BVHLeafNode_t BVHLeafNode;

typedef float MtxF[4][4];
typedef float Vec3[3];

#endif