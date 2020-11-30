#ifndef __TYPES_H__
#define __TYPES_H__

#include <PR/ultratypes.h>

// Prototypes for model structs
typedef struct BoneLayer_t BoneLayer;
typedef struct Bone_t Bone;
typedef struct Model_t Model;

// Prototypes for animation structs
typedef struct Animation_t Animation;
typedef struct BoneTable_t BoneTable;
typedef struct AnimTrigger_t AnimTrigger;
typedef struct AnimState_t AnimState;

// Prototypes for collision structs
typedef struct AABB_t AABB;
typedef struct ColTri_t ColTri;
typedef struct BVHNode_t BVHNodeBase;
typedef struct BVHTree_t BVHTree;

typedef float MtxF[4][4];
typedef float Vec3[3];
typedef s16 Vec3s[4];

// Prototypes for entity component system
typedef struct Entity_t Entity;
typedef u32 archetype_t;
typedef struct MultiArrayListBlock_t MultiArrayListBlock;
typedef struct MultiArrayList_t MultiArrayList;
typedef struct BehaviorParams_t BehaviorParams;

// Prototypes for input structs
typedef struct InputData_t InputData;

// Prototypes for camera structs
typedef struct Camera_t Camera;

// Components
// #define COMPONENT(Name, Type) typedef Type Name;
// #include "components.inc.h"
// #undef COMPONENT

#endif