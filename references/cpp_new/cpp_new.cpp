// vim: ts=2 sw=2 expandtab
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <libdragon.h>

static volatile uint32_t animationCounter = 0;
void update_counter(int overflow)
{
    animationCounter++;
}

int main()
{
    // Initialize screen and peripherals
    display_init( RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE );
    dfs_init( DFS_DEFAULT_LOCATION );
    // rdp_init();
    controller_init();
    timer_init();

    // read our sprite map
    int fp = dfs_open("/guy.sprite");
    // @todo: This halts execution (our timer never runs either)
    // sizeof(sprite_t) != dfs_size(fp)
    // sprite_t* guySprite = new sprite_t;
    //
    // I can't tell why honestly. when reviewing the syscalls from
    // the ares emulator, you can clearly see the timer not being called
    // but there isn't any indication from that level what could be wrong.
    // We would probably have to disassemble and review the memory model of
    // the n64 to really know
    sprite_t* guySprite = (sprite_t*)malloc(dfs_size(fp));
    assert(dfs_read(guySprite, 1, dfs_size(fp), fp) >= 0);
    dfs_close(fp);

    // start a timer
    new_timer(TIMER_TICKS(1000000 / 30), TF_CONTINUOUS, update_counter);


    while(1) 
    {
        // static because you always want
        // a display lock before doing colors
        static display_context_t disp = 0;

        while ( !(disp = display_lock()) );

        graphics_fill_screen(disp, 0x00000000);

        // Draw first sprite
        graphics_draw_sprite_stride(disp, 160, 120, guySprite, (animationCounter % 8) * 2);

        // swap bufs
        display_show(disp);
    }
}
