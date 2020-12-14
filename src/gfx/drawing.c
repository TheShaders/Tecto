#include <types.h>
#include <ecs.h>
#include <gfx.h>
#include <model.h>
#include <resize.h>
#include <mem.h>

void drawAnimatedModels(size_t count, UNUSED void *arg, void **componentArrays)
{
    // Components: Position, Rotation, Model
    Vec3 *curPos = componentArrays[COMPONENT_INDEX(Position, ARCHETYPE_ANIM_MODEL)];
    Vec3s *curRot = componentArrays[COMPONENT_INDEX(Rotation, ARCHETYPE_ANIM_MODEL)];
    Model **curModel = componentArrays[COMPONENT_INDEX(Model, ARCHETYPE_ANIM_MODEL)];
    AnimState *curAnimState = componentArrays[COMPONENT_INDEX(AnimState, ARCHETYPE_ANIM_MODEL)];

    while (count)
    {
        Animation *anim = (Animation *)segmentedToVirtual(curAnimState->anim);

        gfxPushMat();
         gfxTranslate((*curPos)[0], (*curPos)[1], (*curPos)[2]);
         gfxRotateEulerXYZ((*curRot)[0], (*curRot)[1], (*curRot)[2]);
          drawModel(*curModel, anim, ANIM_COUNTER_TO_FRAME(curAnimState->counter));
        gfxPopMat();

        curAnimState->counter += curAnimState->speed;
#ifdef FPS30
        curAnimState->counter += curAnimState->speed;
#endif
        if (anim)
        {
            if (curAnimState->counter >= (anim->frameCount << (ANIM_COUNTER_SHIFT)))
            {
                if (anim->flags & ANIM_LOOP)
                {
                    curAnimState->counter -= (anim->frameCount << (ANIM_COUNTER_SHIFT));
                }
                else
                {
                    curAnimState->counter = (anim->frameCount - 1) << (ANIM_COUNTER_SHIFT);
                }
            }
        }

        count--;
        curPos++;
        curRot++;
        curModel++;
        curAnimState++;
    }
}

void drawModels(size_t count, UNUSED void *arg, void **componentArrays)
{
    // Components: Position, Rotation, Model
    Vec3 *curPos = componentArrays[COMPONENT_INDEX(Position, ARCHETYPE_MODEL)];
    Vec3s *curRot = componentArrays[COMPONENT_INDEX(Rotation, ARCHETYPE_MODEL)];
    Model **curModel = componentArrays[COMPONENT_INDEX(Model, ARCHETYPE_MODEL)];

    while (count)
    {
        gfxPushMat();
         gfxTranslate((*curPos)[0], (*curPos)[1], (*curPos)[2]);
         gfxRotateEulerXYZ((*curRot)[0], (*curRot)[1], (*curRot)[2]);
          drawModel(*curModel, NULL, 0);
        gfxPopMat();
        count--;
        curPos++;
        curRot++;
        curModel++;
    }
}

void drawResizableAnimatedModels(size_t count, UNUSED void *arg, void **componentArrays)
{
    // Components: Position, Rotation, Model, Resizable
    Vec3 *curPos = componentArrays[COMPONENT_INDEX(Position, ARCHETYPE_SCALED_ANIM_MODEL)];
    Vec3s *curRot = componentArrays[COMPONENT_INDEX(Rotation, ARCHETYPE_SCALED_ANIM_MODEL)];
    Model **curModel = componentArrays[COMPONENT_INDEX(Model, ARCHETYPE_SCALED_ANIM_MODEL)];
    AnimState *curAnimState = componentArrays[COMPONENT_INDEX(AnimState, ARCHETYPE_SCALED_ANIM_MODEL)];
    float *curScale = componentArrays[COMPONENT_INDEX(Scale, ARCHETYPE_SCALED_ANIM_MODEL)];

    while (count)
    {
        Animation *anim = (Animation *)segmentedToVirtual(curAnimState->anim);

        gfxPushMat();
         gfxTranslate((*curPos)[0], (*curPos)[1], (*curPos)[2]);
         gfxRotateEulerXYZ((*curRot)[0], (*curRot)[1], (*curRot)[2]);
         gfxScale(*curScale, *curScale, *curScale);
          drawModel(*curModel, anim, ANIM_COUNTER_TO_FRAME(curAnimState->counter));
        gfxPopMat();

        curAnimState->counter += curAnimState->speed;
#ifdef FPS30
        curAnimState->counter += curAnimState->speed;
#endif
        if (anim)
        {
            if (curAnimState->counter >= (anim->frameCount << (ANIM_COUNTER_SHIFT)))
            {
                if (anim->flags & ANIM_LOOP)
                {
                    curAnimState->counter -= (anim->frameCount << (ANIM_COUNTER_SHIFT));
                }
                else
                {
                    curAnimState->counter = (anim->frameCount - 1) << (ANIM_COUNTER_SHIFT);
                }
            }
        }

        count--;
        curPos++;
        curRot++;
        curModel++;
        curAnimState++;
        curScale++;
    }
}

void drawResizableModels(size_t count, UNUSED void *arg, void **componentArrays)
{
    // Components: Position, Rotation, Model, Resizable
    Vec3 *curPos = componentArrays[COMPONENT_INDEX(Position, ARCHETYPE_SCALED_MODEL)];
    Vec3s *curRot = componentArrays[COMPONENT_INDEX(Rotation, ARCHETYPE_SCALED_MODEL)];
    Model **curModel = componentArrays[COMPONENT_INDEX(Model, ARCHETYPE_SCALED_MODEL)];
    float *curScale = componentArrays[COMPONENT_INDEX(Scale, ARCHETYPE_SCALED_MODEL)];

    while (count)
    {
        gfxPushMat();
         gfxTranslate((*curPos)[0], (*curPos)[1], (*curPos)[2]);
         gfxRotateEulerXYZ((*curRot)[0], (*curRot)[1], (*curRot)[2]);
         gfxScale(*curScale, *curScale, *curScale);
          drawModel(*curModel, NULL, 0);
        gfxPopMat();
        count--;
        curPos++;
        curRot++;
        curModel++;
        curScale++;
    }
}

float sqrtf(float);

void mtxf_align_camera(MtxF dest, MtxF mtx, Vec3 position, s16 angle) {
    s16 xrot;
    s16 yrot;
    f32 cx, cy, cz;
    Vec3 colX, colY, colZ; // Column vectors
    f32 sx, sy, sz; // Scale
    MtxF scaleMat;

    dest[3][0] =
        mtx[0][0] * position[0] + mtx[1][0] * position[1] + mtx[2][0] * position[2] + mtx[3][0];
    dest[3][1] =
        mtx[0][1] * position[0] + mtx[1][1] * position[1] + mtx[2][1] * position[2] + mtx[3][1];
    dest[3][2] =
        mtx[0][2] * position[0] + mtx[1][2] * position[1] + mtx[2][2] * position[2] + mtx[3][2];
    dest[3][3] = 1;
    xrot = -atan2s(dest[3][2], dest[3][0]);
    yrot = atan2s(dest[3][2], dest[3][1]);
    cx = cossf(xrot);
    cy = cossf(yrot);
    cz = cossf(angle);

    colX[0] = mtx[0][0];
    colX[1] = mtx[1][0];
    colX[2] = mtx[2][0];

    colY[0] = mtx[0][1];
    colY[1] = mtx[1][1];
    colY[2] = mtx[2][1];

    colZ[0] = mtx[0][2];
    colZ[1] = mtx[1][2];
    colZ[2] = mtx[2][2];

    sx = sqrtf(VEC3_DOT(colX, colX));
    sy = sqrtf(VEC3_DOT(colY, colY));
    sz = sqrtf(VEC3_DOT(colZ, colZ));

    guScaleF(scaleMat, sx, sy, sz);

    dest[2][0] = sinsf(xrot);
    dest[0][2] = -dest[2][0];
    dest[1][2] = sinsf(yrot);
    dest[2][1] = -dest[1][2];
    dest[0][1] = sinsf(angle);
    dest[1][0] = -dest[0][1];

    dest[0][0] = -cx * cz;
    dest[1][1] = -cy * cz;
    dest[2][2] = -cx * -cy;

    dest[0][3] = 0;
    dest[1][3] = 0;
    dest[2][3] = 0;
    
    mtxfMul(dest, dest, scaleMat);
}

#define NUM_WATER_TEXTURES 600
#define WATER_TEXTURE_SIZE 4096

u8 waterTextures[2][WATER_TEXTURE_SIZE];

s32 firstFrame = 1;
s32 waterTextureIndex;
s32 waterTextureBufIndex;

extern u8 _dma_waterSegmentRomStart[];

typedef struct TextureScroll_t {
    Vtx *vertices;
    int vtxCount;
    s16 sSpeed;
    s16 tSpeed;
    s16 sMax;
    s16 tMax;
    s16 sPos;
    s16 tPos;
} TextureScroll;

extern Vtx main_model_VIS_mesh_vtx_7[];
extern Vtx main_model_VIS_XDecal_mesh_vtx_0[];

TextureScroll textureScrolls[] = {
    { main_model_VIS_mesh_vtx_7, 17, 0, -20, 128 << 5, 64 << 5, 0, 0 },
    { main_model_VIS_XDecal_mesh_vtx_0, 25, 20, 5, 64 << 5, 64 << 5, 0, 0 },
};

#define NUM_TEXTURE_SCROLLS (sizeof(textureScrolls) / sizeof(textureScrolls[0]))

void scrollTextures()
{
    TextureScroll *curTexScroll;
    for (curTexScroll = &textureScrolls[0]; curTexScroll != &textureScrolls[NUM_TEXTURE_SCROLLS]; curTexScroll++)
    {
        int ds = curTexScroll->sSpeed;
        int dt = curTexScroll->tSpeed;
        int sMax = curTexScroll->sMax;
        int tMax = curTexScroll->tMax;
        Vtx *curVtx;

        curTexScroll->sPos += ds;
        curTexScroll->tPos += dt;

        if (curTexScroll->sPos >= sMax)
        {
            curTexScroll->sPos -= sMax;
            ds -= sMax;
        }

        if (curTexScroll->sPos < 0)
        {
            curTexScroll->sPos += sMax;
            ds += sMax;
        }

        if (curTexScroll->tPos >= tMax)
        {
            curTexScroll->tPos -= tMax;
            dt -= tMax;
        }

        if (curTexScroll->tPos < 0)
        {
            curTexScroll->tPos += tMax;
            dt += tMax;
        }

        for (curVtx = segmentedToVirtual(&curTexScroll->vertices[0]); curVtx != segmentedToVirtual(&curTexScroll->vertices[curTexScroll->vtxCount]); curVtx++)
        {
            curVtx->v.tc[0] += ds;
            curVtx->v.tc[1] += dt;
        }
    }
}

void drawAllEntities()
{
    // Draw all non-resizable entities that have a model and no animation
    iterateOverEntities(drawModels, NULL, ARCHETYPE_MODEL, Bit_AnimState | Bit_Scale);
    // Draw all non-resizable entities that have a model and an animation
    iterateOverEntities(drawAnimatedModels, NULL, ARCHETYPE_ANIM_MODEL, Bit_Scale);
    // Draw all resizable entities that have a model and no animation
    iterateOverEntities(drawResizableModels, NULL, ARCHETYPE_SCALED_MODEL, Bit_AnimState);
    // Draw all resizable entities that have a model and an animation
    iterateOverEntities(drawResizableAnimatedModels, NULL, ARCHETYPE_SCALED_ANIM_MODEL, 0);
    // DMA the water texture for the next frame and set the segment for the current one
    setSegment(SEGMENT_WATER_TEXTURE, waterTextures[waterTextureBufIndex]);
    if (firstFrame)
    {
        firstFrame = 0;
    }
    else
    {
        // waitForDMA();
    }
    waterTextureBufIndex ^= 1;
    waterTextureIndex++;
    if (waterTextureIndex >= NUM_WATER_TEXTURES)
    {
        waterTextureIndex = 0;
    }
    startDMA(waterTextures[waterTextureBufIndex], _dma_waterSegmentRomStart + WATER_TEXTURE_SIZE * waterTextureIndex, WATER_TEXTURE_SIZE);

    scrollTextures();
    
    // waitForDMA();
    // setSegment(SEGMENT_WATER_TEXTURE, waterTextures[waterTextureBufIndex]);
}

Gfx *gfxCbBeforeBillboard(UNUSED Bone* bone, UNUSED BoneLayer *layer)
{
    MtxF billboardMtx;
    Vec3 offset = {0.0f, 0.0f, 0.0f};
    mtxf_align_camera(billboardMtx, *g_curMatFPtr, offset, 0);

    gfxPushLoadMat(&billboardMtx);

    return NULL;
}

Gfx *gfxCbAfterBillboard(UNUSED Bone* bone, UNUSED BoneLayer *layer)
{
    gfxPopMat();
    
    return NULL;
}
