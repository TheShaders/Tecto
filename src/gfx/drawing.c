#include <types.h>
#include <ecs.h>
#include <gfx.h>
#include <model.h>
#include <resize.h>

void drawAnimatedModels(size_t count, UNUSED void *arg, void **componentArrays)
{
    // Components: Position, Rotation, Model
    Vec3 *curPos = componentArrays[COMPONENT_INDEX(Position, ARCHETYPE_ANIM_MODEL)];
    Vec3s *curRot = componentArrays[COMPONENT_INDEX(Rotation, ARCHETYPE_ANIM_MODEL)];
    Model **curModel = componentArrays[COMPONENT_INDEX(Model, ARCHETYPE_ANIM_MODEL)];
    AnimState *curAnimState = componentArrays[COMPONENT_INDEX(AnimState, ARCHETYPE_ANIM_MODEL)];

    while (count)
    {
        gfxPushMat();
         gfxTranslate((*curPos)[0], (*curPos)[1], (*curPos)[2]);
         gfxRotateEulerXYZ((*curRot)[0], (*curRot)[1], (*curRot)[2]);
          drawModel(*curModel, curAnimState->anim, ANIM_COUNTER_TO_FRAME(curAnimState->counter));
        gfxPopMat();

        curAnimState->counter += curAnimState->speed;
#ifdef FPS30
        curAnimState->counter += curAnimState->speed;
#endif
        if (curAnimState->counter >= (curAnimState->anim->frameCount << (ANIM_COUNTER_SHIFT)))
        {
            curAnimState->counter -= (curAnimState->anim->frameCount << (ANIM_COUNTER_SHIFT));
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
        gfxPushMat();
         gfxTranslate((*curPos)[0], (*curPos)[1], (*curPos)[2]);
         gfxRotateEulerXYZ((*curRot)[0], (*curRot)[1], (*curRot)[2]);
         gfxScale(*curScale, *curScale, *curScale);
          drawModel(*curModel, curAnimState->anim, ANIM_COUNTER_TO_FRAME(curAnimState->counter));
        gfxPopMat();

        curAnimState->counter += curAnimState->speed;
#ifdef FPS30
        curAnimState->counter += curAnimState->speed;
#endif
        if (curAnimState->counter >= (curAnimState->anim->frameCount << (ANIM_COUNTER_SHIFT)))
        {
            curAnimState->counter -= (curAnimState->anim->frameCount << (ANIM_COUNTER_SHIFT));
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
}
