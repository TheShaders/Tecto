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

#include <segments/intro.h>

#define NUM_LOGOS 10

extern u8 *introSegAddr;

extern u8 _introSegmentStart[];

extern Model testmodel;
extern Model character_model;
extern Animation testmodelAnim;
extern Animation character_anim_Walking;
extern BVHTree test_collision_tree;

LookAt lookAt = gdSPDefLookAt(127, 0, 0, 0, 127, 0);
Vec3 g_lightDir = {127.0f, -127.0f, 0.0f};

int numPosVels = 0;
float totalPos = 0.0f;

void posVelCallback(size_t count, __attribute__((unused)) void *arg, void **componentArrays)
{
    Position *posArr = componentArrays[0];
    Velocity *velArr = componentArrays[1];
    while (count)
    {
        totalPos += (*posArr)[0] + (*posArr)[1] + (*posArr)[2];
        posArr++;
        count--;
    }
}

void setPos(size_t count, __attribute__((unused)) void *arg, void **componentArrays)
{
    Position *posArr = componentArrays[0];
    while (count)
    {
        (*posArr)[0] = 1.0f;
        (*posArr)[1] = 2.0f;
        (*posArr)[2] = 3.0f;
        posArr++;
        count--;
    }
}

void setPos2(size_t count, __attribute__((unused)) void *arg, void **componentArrays)
{
    Position *posArr = componentArrays[0];
    while (count)
    {
        (*posArr)[0] = 2.0f;
        (*posArr)[1] = 4.0f;
        (*posArr)[2] = 6.0f;
        posArr++;
        count--;
    }
}

void setPos3(size_t count, __attribute__((unused)) void *arg, void **componentArrays)
{
    Position *posArr = componentArrays[0];
    while (count)
    {
        (*posArr)[0] = 100.0f;
        (*posArr)[1] = 200.0f;
        (*posArr)[2] = 300.0f;
        posArr++;
        count--;
    }
}

void processBehaviorEntities(size_t count, __attribute__((unused)) void *arg, int numComponents, size_t *components, void **componentArrays, size_t *componentSizes)
{
    int i = 0;
    // Get the index of the BehaviorParams component in the component array and iterate over it
    BehaviorParams *curBhvParams = componentArrays[indexOfSorted_size_t(Component_Behavior, components, numComponents)];
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

void playerCallback(__attribute__((unused)) void **components, __attribute__((unused)) void *data)
{
    // Components: Position, Velocity, Rotation, BehaviorParams
    debug_printf("Player callback!\n");
}

void createPlayer(__attribute__((unused)) size_t count, __attribute__((unused)) void *arg, void **componentArrays)
{
    // Components: Position, Velocity, Rotation, BehaviorParams
    BehaviorParams *bhvParams = componentArrays[3];
    bhvParams->callback = playerCallback;
    bhvParams->data = arg;
}

static const archetype_t PosVelArchetype = Bit_Position | Bit_Velocity;
static const archetype_t CollisionArchetype = Bit_Position | Bit_Velocity | Bit_Collision;

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

static InputData playerInput;

void mainThreadFunc(__attribute__ ((unused)) void *arg)
{
    u32 frame = 0;
    u32 i;
    float angle = 0.0f;
    float tmpAngle;
    u32 fpccsr;

    // Read fpcsr
    fpccsr = __osSetFpcCsr(0);
    // Write back fpcsr with division by zero and invalid operations exceptions disabled
    __osSetFpcCsr(fpccsr & ~(FPCSR_EZ | FPCSR_EV));

    initInput();
    initGfx();

    #define POSVEL_TO_ALLOC 10000
    #define POSVELCOL_TO_ALLOC 5000

    debug_printf("Main\n");
    debug_printf("Creating " xstr(POSVEL_TO_ALLOC) " entities with pos and vel, setting their pos via callback\n");
    createEntitiesCallback(PosVelArchetype, NULL, POSVEL_TO_ALLOC, setPos);

    // Create the player entity
    createEntitiesCallback(Bit_Position | Bit_Velocity | Bit_Rotation | Bit_Behavior, NULL, 1, createPlayer);

    debug_printf("Creating " xstr(POSVELCOL_TO_ALLOC) " entities with pos, vel, and col\n");
    createEntities(CollisionArchetype, POSVELCOL_TO_ALLOC);

    debug_printf("Setting position of pos+vel+col entities\n");
    iterateOverEntities(setPos2, NULL, Bit_Position | Bit_Velocity | Bit_Collision, 0);

    debug_printf("Creating 1 entity with only position\n");
    createEntity(Bit_Position);
    debug_printf("Setting position of only pos entities\n");
    iterateOverEntities(setPos3, NULL, Bit_Position, Bit_Collision | Bit_Velocity);

    // Iterate over all entities that have position
    debug_printf("Iterating over components with position\n");
    iterateOverEntities(posVelCallback, NULL, Bit_Position, 0);
    debug_printf("Total position: %f\n", totalPos);

    while (1)
    {
#ifdef DEBUG_MODE
        bzero(&ProfilerData, sizeof(ProfilerData));
        ProfilerData.cpuTime = osGetTime();
        IO_WRITE(DPC_STATUS_REG, DPC_CLR_CLOCK_CTR | DPC_CLR_CMD_CTR | DPC_CLR_PIPE_CTR | DPC_CLR_TMEM_CTR);
#endif
        beginInputPolling();
        startFrame();
        readInput(&playerInput, 1);

        // Process all entities that have a behavior
        iterateOverEntitiesAllComponents(processBehaviorEntities, NULL, Bit_Behavior, 0);

        gSPLookAt(g_dlistHead++, &lookAt);
        gfxLookat(
            1000.0f * sinf((M_PI / 180.0f) * angle * 0), 1000.0f, 1000.0f * cosf((M_PI / 180.0f) * angle * 0), // Eye pos
            0.0f, 300.0f, 0.0f, // Look pos
            0.0f, 1.0f, 0.0f);

        // g_lightDir[0] = -127.0f * cosf((M_PI / 180.0f) * angle);
        // g_lightDir[2] = 127.0f * sinf((M_PI / 180.0f) * angle);

        lookAt.l[0].l.dir[0] = (s8)(g_lightDir[0] * (*g_curMatFPtr)[0][0] + g_lightDir[1] * (*g_curMatFPtr)[1][0] + g_lightDir[2] * (*g_curMatFPtr)[2][0]);
        lookAt.l[0].l.dir[1] = (s8)(g_lightDir[0] * (*g_curMatFPtr)[0][1] + g_lightDir[1] * (*g_curMatFPtr)[1][1] + g_lightDir[2] * (*g_curMatFPtr)[2][1]);
        lookAt.l[0].l.dir[2] = (s8)(g_lightDir[0] * (*g_curMatFPtr)[0][2] + g_lightDir[1] * (*g_curMatFPtr)[1][2] + g_lightDir[2] * (*g_curMatFPtr)[2][2]);

        lookAt.l[1].l.dir[0] = (s8)(*g_curMatFPtr)[1][0];
        lookAt.l[1].l.dir[1] = -(s8)(*g_curMatFPtr)[1][1];
        lookAt.l[1].l.dir[2] = (s8)(*g_curMatFPtr)[1][2];


        // gfxPushMat();
        //  gfxRotateAxisAngle(angle, 0.0f, 1.0f, 0.0f);
        //  drawGfx(logo_logo_mesh);
        // gfxPopMat();

        gfxPushMat();
         gfxScale(0.5f, 0.5f, 0.5f);
        //  gfxRotateAxisAngle(angle, 0.0f, 1.0f, 0.0f);
        //  drawModel(&character_model, &character_anim_Walking, frame);
        gfxPopMat();

        tmpAngle = -angle * (M_PI / 180) / 4.0f;

        for (i = 0; i < NUM_LOGOS; i++)
        {
            // f32 tmpAngle2 = angle - i * (360.0f / NUM_LOGOS);
            gfxPushMat();
             gfxPosition(0.0f, angle - i * (360.0f / NUM_LOGOS), 0.0f, 1.0f, sinf(tmpAngle) * 200.0f, cosf(tmpAngle) * 200.0f, 0.0f);
            //  drawGfx(LAYER_OPA_SURF, logo_logo_mesh);
                // drawModel(&testmodel, &testmodelAnim, 0);
            gfxPopMat();
            tmpAngle += (2 * M_PI) / NUM_LOGOS;
        }


        gfxPushMat();
         gfxTranslate(0.0f, 0.0f, 0.0f);
         gfxScale(1.0f, 1.0f, 1.0f);
        if (1) {
            BVHTree *test_collision_virtual = (BVHTree*)segmentedToVirtual(&test_collision_tree);
            ColTri *tris = segmentedToVirtual(test_collision_virtual->tris);
            Vec3 rayOrigin = { 150.0f * sinf((M_PI / 180.0f) * angle), 80.0f, 150.0f * cosf((M_PI / 180.0f) * angle) };
            Vec3 rayDir = { 0.0f, -1000.0f, 0.0f };
            Vec3 rayDirInv = { 1.0f / rayDir[0], 1.0f / rayDir[1], 1.0f / rayDir[2] };
            Vec3 rayEnd;
            ColTri *hit = NULL;
            f32 hitDist;
            BVHNode *nodes = (BVHNode*)segmentedToVirtual(test_collision_virtual->nodes);
            int i;

            drawColTris(LAYER_OPA_SURF, tris, test_collision_virtual->triCount, 0xFF0000FF);

            for (i = 0; i < test_collision_virtual->nodeCount; i++)
            {
                if (testRayVsAABB(rayOrigin, rayDirInv, &nodes[i].aabb, 0.0f, 1.0f))
                {
                    drawAABB(LAYER_OPA_LINE, &nodes[i].aabb, 0x00FF00FF);
                }
            }

            // Off(O2) :              105000 -  107000
            // On (O2) :             1500000 - 1700000
            // On (Ofast) :          1500000 - 2480000
            // On (vertical/O2) :    1070000 - 1440000
            // On (vertical/Ofast) : 1160000 - 1700000
            // On (O1) :             1080000 - 1380000
            // On (Os) :              990000 - 1380000
            // for (i = 0; i < 1000; i++)
            // {
            //     verticalRayVsBvh(rayOrigin, rayDir[1], test_collision_virtual, 0.0f, 1.0f, &hit);
            // }

            hitDist = verticalRayVsBvh(rayOrigin, rayDir[1], test_collision_virtual, 0.0f, 1.0f, &hit);

            if (hit)
            {
                drawColTris(LAYER_OPA_DECAL, hit, 1, 0x00FF00FF);
                VEC3_SCALE(rayDir, rayDir, hitDist);
            }
            VEC3_ADD(rayEnd, rayOrigin, rayDir);

            drawLine(LAYER_OPA_LINE, rayOrigin, rayEnd, 0x0000FFFF);
            // No longer works, since child node indices are no longer stored
            // for (index = 0; index < test_collision_virtual->nodeCount; index++)
            // {
            //     if (nodes[index].triCount == 0 && nodes[nodes[index].childIndex].triCount == 0 && nodes[nodes[nodes[index].childIndex].childIndex].triCount)
            //     {
            //         drawAABB(LAYER_OPA_LINE, &nodes[index].aabb, 0x00FF00FF);
            //     }
            // }
        }
        if (0) {
            AABB aabb = {
                .min = {-100.0f, -100.0f, -100.0f},
                .max = { 100.0f,  100.0f,  100.0f},
            };
            ColTri tri = {
                .normal = {-0.7071f, 0.7071f, 0.0f},
                .originDist = 0.0f,
                .vertex = {-100.0f, -100.0f, -100.0f},
                .u = {0.0f, 0.0f, 200.0f},
                .v = {200.0f, 200.0f, 0.0f},
                .uu = 40000.0f,
                .uv = 0.0f,
                .vv = 80000.0f,
            };
            Vec3 rayOrigin = { 200.0f * sinf((M_PI / 180.0f) * angle), 80.0f, 0.0f };
            Vec3 rayDir = { 0.0f, -1000.0f, 0.0f };
            Vec3 rayDirInv = { 1/rayDir[0], 1/rayDir[1], 1/rayDir[2] };
            Vec3 rayEnd;
            // s32 hitAABB = (rayVsAABB(rayOrigin, rayDirInv, &aabb, 0.0f, 1.0f) >= 0.0f);
            s32 hitAABB = (verticalRayVsAABB(rayOrigin, rayDirInv[1], &aabb, 0.0f, 1.0f) >= 0.0f);
            // f32 rayDist = rayVsTri(rayOrigin, rayDir, &tri, 0.0f, 1.0f);
            f32 rayDist = verticalRayVsTri(rayOrigin, rayDir[1], &tri, 0.0f, 1.0f);

            if (hitAABB)
            {
                drawAABB(LAYER_OPA_LINE, &aabb, 0x00FF00FF);
            }
            else
            {
                drawAABB(LAYER_OPA_LINE, &aabb, 0xFF0000FF);                
            }

            if (rayDist >= 0)
            {
                drawColTris(LAYER_OPA_SURF, &tri, 1, 0x00FF00FF);
                VEC3_SCALE(rayDir, rayDir, rayDist);
            }
            else
            {
                drawColTris(LAYER_OPA_SURF, &tri, 1, 0xFF0000FF);
            }

            VEC3_ADD(rayEnd, rayOrigin, rayDir);
            drawLine(LAYER_OPA_LINE, rayOrigin, rayEnd, 0x0000FFFF);
        }
        gfxPopMat();
        
#ifdef DEBUG_MODE
        ProfilerData.cpuTime = osGetTime() - ProfilerData.cpuTime;
#endif
    
        endFrame();

        angle += 360.0f / (5 * 60.0f);
        frame++;
        if (frame >= ((Animation*)segmentedToVirtual(&character_anim_Walking))->frameCount)
            frame = 0;
            
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