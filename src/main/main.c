#include <main.h>
#include <init.h>
#include <input.h>
#include <gfx.h>
#include <model.h>
#include <mem.h>
#include <collision.h>
#include <ecs.h>
#include <multiarraylist.h>
#include <debug.h>
#include <algorithms.h>
#include <mathutils.h>
#include <player.h>
#include <physics.h>
#include <camera.h>

#include <segments/intro.h>

#define NUM_LOGOS 10

extern u8 *introSegAddr;

extern u8 _introSegmentStart[];

extern Animation character_anim_Idle_Long;
extern Animation character_anim_Jump_Start;
extern Animation character_anim_Walk;
extern BVHTree test_collision_tree;

void processBehaviorEntities(size_t count, __attribute__((unused)) void *arg, int numComponents, archetype_t archetype, void **componentArrays, size_t *componentSizes)
{
    int i = 0;
    // Get the index of the BehaviorParams component in the component array and iterate over it
    BehaviorParams *curBhvParams = componentArrays[COMPONENT_INDEX(Behavior, archetype)];
    // Iterate over every entity in the given array
    while (count)
    {
        // Call the entity's callback with the component pointers and it's data pointer
        curBhvParams->callback(componentArrays, curBhvParams->data);

        // Increment the component pointers so they are valid for the next entity
        for (i = 0; i < numComponents; i++)
        {
            componentArrays[i] += componentSizes[i];
        }
        // Increment to the next entity's behavior params
        curBhvParams++;
        // Decrement the remaining entity count
        count--;
    }
}

void drawAnimatedModels(size_t count, __attribute__((unused)) void *arg, void **componentArrays)
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

void drawModels(size_t count, __attribute__((unused)) void *arg, void **componentArrays)
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

void setCollision(size_t count, void *tree, void **componentArrays)
{
    // Components: Collision
    BVHTree **curCollision = componentArrays[COMPONENT_INDEX(Collision, Bit_Collision)];
    while (count)
    {
        *curCollision = tree;
        curCollision++;
        count--;
    }
}

#ifdef DEBUG_MODE
static struct {
    u32 cpuTime;
    u32 rspTime;
    u32 rdpClockTime;
    u32 rdpCmdTime;
    u32 rdpPipeTime;
    u32 rdpTmemTime;
} ProfilerData;
#endif

#define xstr(a) str(a)
#define str(a) #a

u32 __osSetFpcCsr(u32);

void mainThreadFunc(__attribute__ ((unused)) void *arg)
{
    float angle = 0.0f;
    u32 fpccsr;

    // Read fpcsr
    fpccsr = __osSetFpcCsr(0);
    // Write back fpcsr with division by zero and invalid operations exceptions disabled
    __osSetFpcCsr(fpccsr & ~(FPCSR_EZ | FPCSR_EV));
    
    debug_printf("Main\n");

    initInput();
    initGfx();

    // Create the player entity
    createPlayer();

    // Create the level collision entity
    debug_printf("Creating collision entity\n");
    createEntitiesCallback(Bit_Collision, segmentedToVirtual(&test_collision_tree), 1, setCollision);

    while (1)
    {
        Vec3 lightDir = { 127.0f * sinf((M_PI / 180.0f) * angle), 127.0f * cosf((M_PI / 180.0f) * angle), 0.0f};
#ifdef DEBUG_MODE
        bzero(&ProfilerData, sizeof(ProfilerData));
        ProfilerData.cpuTime = osGetTime();
        IO_WRITE(DPC_STATUS_REG, DPC_CLR_CLOCK_CTR | DPC_CLR_CMD_CTR | DPC_CLR_PIPE_CTR | DPC_CLR_TMEM_CTR);
#endif
        beginInputPolling();
        startFrame();
        readInput();

        // Process all entities that have a behavior
        iterateOverEntitiesAllComponents(processBehaviorEntities, NULL, Bit_Behavior, 0);
        
        // Set up the camera
        setupCameraMatrices(&g_Camera);

        setLightDirection(lightDir);

        // Draw all entities that have a model and no animation
        iterateOverEntities(drawModels, NULL, ARCHETYPE_MODEL, Bit_AnimState);
        // Draw all entities that have a model and an animation
        iterateOverEntities(drawAnimatedModels, NULL, ARCHETYPE_ANIM_MODEL, 0);

        if (1) {
            BVHTree *test_collision_virtual = (BVHTree*)segmentedToVirtual(&test_collision_tree);
            ColTri *tris = segmentedToVirtual(test_collision_virtual->tris);
            
            drawColTris(LAYER_OPA_SURF, tris, test_collision_virtual->triCount, 0x7F3300FF);
            // {
            //     Vec3 rayOrigin = { 150.0f * sinf((M_PI / 180.0f) * angle), 80.0f, 150.0f * cosf((M_PI / 180.0f) * angle) };
            //     Vec3 rayDir = { 0.0f, -1000.0f, 0.0f };
            //     ColTri *hit = NULL;
            //     BVHNode *nodes = (BVHNode*)segmentedToVirtual(test_collision_virtual->nodes);
            //     int i;


            //     Off(O2) :              105000 -  107000
            //     On (O2) :             1500000 - 1700000
            //     On (Ofast) :          1500000 - 2480000
            //     On (vertical/O2) :    1070000 - 1440000
            //     On (vertical/Ofast) : 1160000 - 1700000
            //     On (O1) :             1080000 - 1380000
            //     On (Os) :              990000 - 1380000
            //     for (i = 0; i < 1000; i++)
            //     {
            //         verticalRayVsBvh(rayOrigin, rayDir[1], test_collision_virtual, 0.0f, 1.0f, &hit);
            //     }
            // }
        }
        
#ifdef DEBUG_MODE
        ProfilerData.cpuTime = osGetTime() - ProfilerData.cpuTime;
#endif

        endFrame();

        angle += 360.0f / (5 * 60.0f);
            
#ifdef DEBUG_MODE
        ProfilerData.rdpClockTime = IO_READ(DPC_CLOCK_REG);
        ProfilerData.rdpCmdTime = IO_READ(DPC_BUFBUSY_REG);
        ProfilerData.rdpPipeTime = IO_READ(DPC_PIPEBUSY_REG);
        ProfilerData.rdpTmemTime = IO_READ(DPC_TMEM_REG);

        debug_printf("CPU:  %8u RSP:  %8u CLK:  %8u\nCMD:  %8u PIPE: %8u TMEM: %8u\n",
            ProfilerData.cpuTime, ProfilerData.rspTime, ProfilerData.rdpClockTime, ProfilerData.rdpCmdTime,
            ProfilerData.rdpPipeTime, ProfilerData.rdpTmemTime);
#endif
    }
}