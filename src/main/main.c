#include <main.h>
#include <init.h>
#include <input.h>
#include <gfx.h>
#include <model.h>
#include <mem.h>
#include <collision.h>
#include <ecs.h>
#include <debug.h>
#include <algorithms.h>
#include <mathutils.h>
#include <player.h>
#include <physics.h>
#include <camera.h>
#include <level.h>
#include <resize.h>
#include <audio.h>

#include <segments/intro.h>

#define NUM_LOGOS 10

extern u8 *introSegAddr;

extern u8 _introSegmentStart[];

extern Animation character_anim_Idle_Long;
extern Animation character_anim_Jump_Start;
extern Animation character_anim_Walk;
extern BVHTree main_collision_tree;

void processBehaviorEntities(size_t count, UNUSED void *arg, int numComponents, archetype_t archetype, void **componentArrays, size_t *componentSizes)
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

extern LevelHeader mainHeader;
extern Model logo_model;

u32 __osSetFpcCsr(u32);

PlayerState playerState;

u32 g_gameTimer = 0;
u32 g_graphicsTimer = 0;

void mainThreadFunc(__attribute__ ((unused)) void *arg)
{
    float angle = 0.0f;
    int frame = 0;
    u32 fpccsr;

    // Read fpcsr
    fpccsr = __osSetFpcCsr(0);
    // Write back fpcsr with division by zero and invalid operations exceptions disabled
    __osSetFpcCsr(fpccsr & ~(FPCSR_EZ | FPCSR_EV));
    
    debug_printf("Main\n");

    initInput();
    initGfx();

    // Create the player entity
    createPlayer(&playerState);

    // Create the level collision entity
    // debug_printf("Creating collision entity\n");
    // createEntitiesCallback(Bit_Collision, segmentedToVirtual(&test_collision_collision_tree), 1, setCollision);

    // {
    //     Entity *toDelete;
    //     Entity *lastEntity;
    //     debug_printf("Creating 5000 position only entities\n");
    //     createEntities(Bit_Position, 5000);

    //     debug_printf("Creating 1 position only entity to delete\n");
    //     toDelete = createEntity(Bit_Position);
    //     debug_printf("To delete entity archetype array index: %d\n", toDelete->archetypeArrayIndex);

    //     debug_printf("Creating 5000 more position only entities\n");
    //     createEntities(Bit_Position, 5000);

    //     debug_printf("Creating 1 position only entity to test\n");
    //     lastEntity = createEntity(Bit_Position);
    //     debug_printf("Test entity archetype array index: %d\n", lastEntity->archetypeArrayIndex);
        
    //     debug_printf("Deleting entity at array position %d\n", toDelete->archetypeArrayIndex);
    //     deleteEntity(toDelete);

    //     debug_printf("Last entity was moved to %d\n", lastEntity->archetypeArrayIndex);
    // }
    debug_printf("Processing level header\n");
    processLevelHeader(segmentedToVirtual(&mainHeader));

    while (1)
    {
        Vec3 lightDir = { 100.0f * sinf((M_PI / 180.0f) * 45.0f), 100.0f * cosf((M_PI / 180.0f) * 45.0f), 0.0f};
        
        // Vec3 lightDir = { 100.0f * sinf((M_PI / 180.0f) * angle), 100.0f * cosf((M_PI / 180.0f) * angle), 0.0f};
#ifdef DEBUG_MODE
        bzero(&ProfilerData, sizeof(ProfilerData));
        ProfilerData.cpuTime = osGetTime();
        IO_WRITE(DPC_STATUS_REG, DPC_CLR_CLOCK_CTR | DPC_CLR_CMD_CTR | DPC_CLR_PIPE_CTR | DPC_CLR_TMEM_CTR);
#endif
        beginInputPolling();
        startFrame();
        readInput();

        if (frame < 10)
        {
            bzero(&g_PlayerInput, sizeof(g_PlayerInput));
        }

        // Increment the physics state
        physicsTick();
        // Increment resizables' states
        tickResizables();
        // Process all entities that have a behavior
        iterateOverEntitiesAllComponents(processBehaviorEntities, NULL, Bit_Behavior, 0);
        g_gameTimer++;
#ifdef FPS30
        beginInputPolling();
        readInput();

        if (frame < 10)
        {
            bzero(&g_PlayerInput, sizeof(g_PlayerInput));
        }
        // Just run everything twice per frame to match 60 fps gameplay speed lol
        // Increment the physics state
        physicsTick();
        // Increment resizables' states
        tickResizables();
        // Process all entities that have a behavior
        iterateOverEntitiesAllComponents(processBehaviorEntities, NULL, Bit_Behavior, 0);
        g_gameTimer++;
#endif
        
        // Set up the camera
        setupCameraMatrices(&g_Camera);
        setLightDirection(lightDir);

        drawAllEntities();
        
#ifdef DEBUG_MODE
        ProfilerData.cpuTime = osGetTime() - ProfilerData.cpuTime;
#endif

        endFrame();

        g_graphicsTimer++;

        angle += 360.0f / (5 * 60.0f);
            
#ifdef DEBUG_MODE
        ProfilerData.rdpClockTime = IO_READ(DPC_CLOCK_REG);
        ProfilerData.rdpCmdTime = IO_READ(DPC_BUFBUSY_REG);
        ProfilerData.rdpPipeTime = IO_READ(DPC_PIPEBUSY_REG);
        ProfilerData.rdpTmemTime = IO_READ(DPC_TMEM_REG);

        // debug_printf("CPU:  %8u RSP:  %8u CLK:  %8u\nCMD:  %8u PIPE: %8u TMEM: %8u\n",
        //     ProfilerData.cpuTime, ProfilerData.rspTime, ProfilerData.rdpClockTime, ProfilerData.rdpCmdTime,
        //     ProfilerData.rdpPipeTime, ProfilerData.rdpTmemTime);
#endif

        frame++;
    }
}