// vim: ts=4 sw=4 expandtab

// Game
//----------------------------
#include "guy.hpp"

// N64
//----------------------------
#include <libdragon.h>

// Core
//----------------------------
#include <limits>
#include <cstdlib>

// External
//----------------------------
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>

// Init DFS first as global C++ object use DFS
//----------------------------
__attribute__((constructor)) void __init_dfs()
{
    dfs_init(DFS_DEFAULT_LOCATION);
}

// Declare a counter, is changed by libdragon during
// a callback
//----------------------------
static volatile uint32_t animationCounter = 0;

//----------------------------
void update_counter(int overflow)
{
    const uint32_t kMaxTick = std::numeric_limits<uint32_t>::max();
    if (animationCounter > kMaxTick)
    {
        animationCounter = 0;
    }
    else
    {
        animationCounter++;
    }
}

//----------------------------
int main()
{
    // Initialize screen and peripherals
    display_init( RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE );

    // rdp_init();
    controller_init();
    timer_init();

    // start a timer
    new_timer(TIMER_TICKS(1000000 / 30), TF_CONTINUOUS, update_counter);

    //----------------------------
    // Start our world. This has to happen
    // as static initalization or else we
    // corrupt the dfs handles; not sure why
    // or now to fix that (maybe just this)
    b2Vec2 gravity(0.0f, 10.0f);
    b2World world(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(150.f, 200.f);
    b2Body* ground = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    
    // This is in meters
    groundBox.SetAsBox(10.f, 3.f);
    ground->CreateFixture(&groundBox, 0.f);
    
    // read our sprite map
    GuySprite guy(&world);

    // Read our ground sprite
    int fp = dfs_open("/test.sprite");
    sprite_t* groundSprite = (sprite_t*)malloc(dfs_size(fp));
    assert(dfs_read(groundSprite, 1, dfs_size(fp), fp) >= 0);
    assert(dfs_close(fp) == 0);


    while(1) 
    {
        // static because you always want
        // a display lock before doing colors
        static display_context_t disp = 0;

        while ( !(disp = display_lock()) );

        graphics_fill_screen(disp, 0x00000000);

        // Draw (right now I'm just doing 1px to 1m)
        graphics_draw_sprite(disp, groundBodyDef.position.x,
                groundBodyDef.position.y, groundSprite);


        graphics_draw_line(disp, 
                groundBodyDef.position.x,
                groundBodyDef.position.y, 
                groundBodyDef.position.x + 100.f,
                groundBodyDef.position.y,
                graphics_make_color(255, 0, 0, 255));

        graphics_draw_line(disp, 
                groundBodyDef.position.x,
                groundBodyDef.position.y, 
                groundBodyDef.position.x,
                groundBodyDef.position.y + 3.f,
                graphics_make_color(255, 0, 0, 255));

        graphics_draw_line(disp, 
                groundBodyDef.position.x,
                groundBodyDef.position.y + 3.f, 
                groundBodyDef.position.x + 100.f,
                groundBodyDef.position.y + 3.f,
                graphics_make_color(255, 0, 0, 255));

        graphics_draw_line(disp, 
                groundBodyDef.position.x + 100.f,
                groundBodyDef.position.y, 
                groundBodyDef.position.x + 100.f,
                groundBodyDef.position.y + 3.f,
                graphics_make_color(255, 0, 0, 255));

        graphics_draw_sprite_stride(disp, 
                guy.GetBody()->GetPosition().x,
                guy.GetBody()->GetPosition().y,
                guy.GetSprite(),
                guy.GetCurrentAnimationOffset(animationCounter));

        // swap bufs
        display_show(disp);

        // Step the world
        world.Step(1.f / 60.f, 6, 2); 

        // Process controls
        controller_scan();

        struct controller_data keys = get_keys_held();
        guy.Animate(keys.c[0].A);
    }
}
