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
#include <credits.h>

#include <segments/intro.h>

#define NUM_LOGOS 10

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
extern u32 fillColor;

#define CREDITS_LOAD_FADE_TIME 60
#define CREDITS_LOAD_TIME 90

u32 creditsTimer = 0;

Vtx fullscreenVerts[] = {
    {{{-1, -1, 0}, 0, {0, 0},{0x0, 0x0, 0x0, 0x0}}},
    {{{-1,  1, 0}, 0, {0, 0},{0x0, 0x0, 0x0, 0x0}}},
    {{{ 1, -1, 0}, 0, {0, 0},{0x0, 0x0, 0x0, 0x0}}},
    {{{ 1,  1, 0}, 0, {0, 0},{0x0, 0x0, 0x0, 0x0}}},
};

extern s32 firstFrame; // HACK

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
    loadIntroSegment();
    
    {
        OSTime startTime = osGetTime();
        // wait 1 second
        while ((osGetTime() - startTime) < 62500000);
    }

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
        debug_printf("before input polling\n");
        beginInputPolling();
        debug_printf("before start frame\n");
        startFrame();
        debug_printf("before read input\n");
        readInput();

        if (frame < 10)
        {
            bzero(&g_PlayerInput, sizeof(g_PlayerInput));
        }

        // Increment the physics state
        debug_printf("before physics tick\n");
        physicsTick();
        // Increment resizables' states
        debug_printf("before resizables tick\n");
        tickResizables();
        // Process all entities that have a behavior
        debug_printf("before behaviors\n");
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
        debug_printf("before physics tick\n");
        physicsTick();
        // Increment resizables' states
        debug_printf("before resizables tick\n");
        tickResizables();
        // Process all entities that have a behavior
        debug_printf("before behaviors\n");
        iterateOverEntitiesAllComponents(processBehaviorEntities, NULL, Bit_Behavior, 0);
        g_gameTimer++;
#endif
        
        // Set up the camera
        debug_printf("before camera\n");
        setupCameraMatrices(&g_Camera);
        debug_printf("before light dir\n");
        setLightDirection(lightDir);

        debug_printf("before drawing\n");
        drawAllEntities();
        
#ifdef DEBUG_MODE
        ProfilerData.cpuTime = osGetTime() - ProfilerData.cpuTime;
#endif

        g_graphicsTimer++;
        
        if (creditsTimer)
        {
            float alphaPercent;
            Mtx *ortho = (Mtx *)allocGfx(sizeof(Mtx));
            Mtx *ident = (Mtx *)allocGfx(sizeof(Mtx));
            Gfx *fadeDL = (Gfx *)allocGfx(sizeof(Gfx) * 11);
            Gfx *fadeDLHead = fadeDL;
            
            creditsTimer--;

            alphaPercent = MIN(1.0f, (((float)CREDITS_LOAD_TIME - (float)creditsTimer) / (float)CREDITS_LOAD_FADE_TIME));

            guOrtho(ortho, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f);
            guMtxIdent(ident);

            gSPMatrix(fadeDLHead++, ident, G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
            gSPMatrix(fadeDLHead++, ortho, G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);
            gSPPerspNormalize(fadeDLHead++, 0xFFFF);
            gSPVertex(fadeDLHead++, fullscreenVerts, 4, 0);
            gSPClearGeometryMode(fadeDLHead++, G_ZBUFFER);
            gDPPipeSync(fadeDLHead++);
            gDPSetEnvColor(fadeDLHead++, 0, 0, 0, (u8)(alphaPercent * 255.0f));
            gDPSetCombineLERP(fadeDLHead++, 0, 0, 0, 0, 0, 0, 0, ENVIRONMENT, 0, 0, 0, 0, 0, 0, 0, ENVIRONMENT);
            gDPSetRenderMode(fadeDLHead++, G_RM_XLU_SURF, G_RM_XLU_SURF);
            gSP2Triangles(fadeDLHead++, 0, 2, 1, 0x00, 2, 3, 1, 0x00);
            gSPEndDisplayList(fadeDLHead++);

            addGfxToDrawLayer(LAYER_XLU_SURF, fadeDL);

            if (creditsTimer == CREDITS_LOAD_TIME - CREDITS_LOAD_FADE_TIME)
            {
                debug_printf("Deleting all entities");
                // Delete all entities
                deleteAllEntities();
            }
            if (creditsTimer == 0)
            {
                // Free intro segment
                debug_printf("Freeing intro segment\n");
                // freeIntroSegment();
                // DMA credits segment
                debug_printf("DMAing credits segment\n");
                loadCreditsSegment();
                {
                    OSTime startTime = osGetTime();
                    // wait 1 second
                    while ((osGetTime() - startTime) < 62500000);
                }

                // Load credits
                debug_printf("Running credits header\n");
                processLevelHeader(segmentedToVirtual(&creditsHeader));
                debug_printf("Level header complete\n");

                g_Camera.distance = 530.0f;
                g_Camera.target[0] = 0;
                g_Camera.target[1] = 13.0f * 20.0f;
                g_Camera.target[2] = 4.14f * 20.0f;
                g_Camera.yOffset = 0.0f;
                g_Camera.pitch = (s16)(0x8000 * (5.0f / 180.0f));
                g_Camera.yaw = 0;

                fillColor = GPACK_RGBA5551(0, 0, 0, 1) << 16 | GPACK_RGBA5551(0, 0, 0, 1);

                firstFrame = 1; // HACK BAD FIX
            }
        }

        endFrame();
        debug_printf("After end frame\n");

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

void startCreditsLoad(void)
{
    if (creditsTimer == 0)
        creditsTimer = CREDITS_LOAD_TIME;
}
