// vim: ts=4 sw=4 expandtab
#include "guy.h"
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
    GuySprite guy;

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
        graphics_draw_sprite_stride(disp, 160, 120, guy.GetSprite(), (animationCounter % 8) * 2);

        // swap bufs
        display_show(disp);
    }
}
