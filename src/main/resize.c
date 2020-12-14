#include <resize.h>
#include <ecs.h>
#include <model.h>

#define ARCHETYPE_RESIZABLE (Bit_Resizable | Bit_Scale)

float scaleLerpFactorFrames[RESIZE_TIMER_START] = 
{
    1.00000000,
    1.00980800,
    1.01364900,
    1.01781200,
    1.02229000,
    1.02707000,
    1.03213700,
    1.03746900,
    1.04303900,
    1.04881300,
    1.05475400,
    1.06081300,
    1.06693700,
    1.07306700,
    1.07913300,
    1.08506000,
    1.09076400,
    1.09615200,
    1.10112700,
    1.10558000,
    1.10939700,
    1.11245600,
    1.11463000,
    1.11578500,
    1.11578200,
    1.11447800,
    1.11172500,
    1.10737800,
    1.10128600,
    1.09330400,
    1.08328700,
    1.07109600,
    1.05659900,
    1.03967400,
    1.02021200,
    0.99811770,
    0.97331350,
    0.94574340,
    0.91537540,
    0.88220490,
    0.84625830,
    0.80759620,
    0.76631750,
    0.72256270,
    0.67651710,
    0.62841520,
    0.57854320,
    0.52724280,
    0.47491370,
    0.42201680,
    0.36907630,
    0.31668170,
    0.26548900,
    0.21622210,
    0.16967250,
    0.12669910,
    0.08822672,
    0.05524400,
    0.02880000,
    0.01000000,
};

void resizableCallback(size_t count, UNUSED void *arg, void **componentArrays)
{
    ResizeParams *curResize = componentArrays[COMPONENT_INDEX(Resizable, ARCHETYPE_RESIZABLE)];
    float *curScale = componentArrays[COMPONENT_INDEX(Scale, ARCHETYPE_RESIZABLE)];
    while (count)
    {
        if (curResize->resizeTimer)
        {
            float scale1, scale2;

            if (curResize->resizeTimer == RESIZE_TIMER_START && curResize->callback != NULL)
            {
                curResize->callback(curResize, Resize_Starting);
            }

            if (curResize->curSize == Size_Grown)
            {
                scale1 = curResize->largeScale;
                scale2 = curResize->smallScale;
            }
            else
            {
                scale1 = curResize->smallScale;
                scale2 = curResize->largeScale;
            }
            *curScale = (scale1 - scale2) * scaleLerpFactorFrames[curResize->resizeTimer - 1] + scale2;

            curResize->resizeTimer--;
            if (curResize->resizeTimer == 0)
            {
                if (curResize->callback != NULL)
                {
                    curResize->callback(curResize, Resize_Ending);
                }
                if (curResize->curSize == Size_Grown && curResize->growTemporary)
                {
                    curResize->restoreTimer = curResize->grownTime;
                }
            }
        }
        else
        {
            if (curResize->curSize == Size_Grown)
            {
                *curScale = curResize->largeScale;
            }
            else
            {
                *curScale = curResize->smallScale;
            }
            if (curResize->restoreTimer)
            {
                curResize->restoreTimer--;
                if (curResize->restoreTimer == 0)
                {
                    curResize->curSize = Size_Shrunk;
                    curResize->resizeTimer = RESIZE_TIMER_START;
                }
            }
        }

        curResize++;
        curScale++;
        count--;
    }
}

void tickResizables()
{
    iterateOverEntities(resizableCallback, NULL, ARCHETYPE_RESIZABLE, 0);
}

extern Animation treevineleaf_anim_tvleaf_shrink;
extern Animation treevineleaf_anim_tvleaf_grow;
extern BVHTree treevineleaf_collision_tree;

extern BVHTree lilypad_collision_tree;

extern BVHTree bounceflower_collision_tree;

void treevineleafResizeCallback(ResizeParams *params, ResizeTrigger trigger)
{
    Entity *entity = findEntityFromComponent(ARCHETYPE_INTERACTABLE, Component_Resizable, params);
    BVHTree **collision;
    AnimState *animState;
    void *components[NUM_COMPONENTS(ARCHETYPE_INTERACTABLE)];

    getEntityComponents(entity, components);

    collision = components[COMPONENT_INDEX(Collision, ARCHETYPE_INTERACTABLE)];
    animState = components[COMPONENT_INDEX(AnimState, ARCHETYPE_INTERACTABLE)];

    if (trigger == Resize_Starting)
    {
        if (params->curSize == Size_Grown)
        {
            animState->anim = &treevineleaf_anim_tvleaf_grow;
        }
        else
        {
            animState->anim = &treevineleaf_anim_tvleaf_shrink;
        }
        animState->counter = 0;
        animState->speed = 1 << ANIM_COUNTER_SHIFT;
    }
    else
    {
        if (params->curSize == Size_Grown)
        {
            *collision = &treevineleaf_collision_tree;
        }
        else
        {
            *collision = NULL;
        }
    }
}

void lillypadResizeCallback(ResizeParams *params, UNUSED ResizeTrigger trigger)
{
    Entity *entity = findEntityFromComponent(ARCHETYPE_INTERACTABLE, Component_Resizable, params);
    BVHTree **collision;
    void *components[NUM_COMPONENTS(ARCHETYPE_INTERACTABLE)];

    getEntityComponents(entity, components);

    collision = components[COMPONENT_INDEX(Collision, ARCHETYPE_INTERACTABLE)];

    if (trigger == Resize_Ending)
    {
        if (params->curSize == Size_Grown)
        {
            *collision = &lilypad_collision_tree;
        }
        else
        {
            *collision = NULL;
        }
    }
}

void bounceflowerResizeCallback(ResizeParams *params, UNUSED ResizeTrigger trigger)
{
    Entity *entity = findEntityFromComponent(ARCHETYPE_INTERACTABLE, Component_Resizable, params);
    BVHTree **collision;
    void *components[NUM_COMPONENTS(ARCHETYPE_INTERACTABLE)];

    getEntityComponents(entity, components);

    collision = components[COMPONENT_INDEX(Collision, ARCHETYPE_INTERACTABLE)];

    if (trigger == Resize_Ending)
    {
        if (params->curSize == Size_Grown)
        {
            *collision = &bounceflower_collision_tree;
        }
        else
        {
            *collision = NULL;
        }
    }
}
