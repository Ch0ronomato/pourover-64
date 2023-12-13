// This works for the most part. Some notes
// 1. It starts paused? 
// 2. It's pretty slow when doing an initial render,
//    we drop to 12fps really fast. We are doing software
//    rendering which probably won't be great for various
//    reasons, but we have a square!
#include <stdio.h>

#include <libdragon.h>

int main(void)
{
    console_init();

    debug_init_usblog();
    console_set_debug(true);

    // Initialize screen?
    rdp_init();


    while(1) 
    {
        // static because you always want
        // a display lock before doing colors
        static display_context_t disp = 0;

        while ( !(disp = display_lock()) );

        // Fill
        graphics_fill_screen(disp, 0x00000000);
        graphics_set_color(0x00103A00, 0x00000000);

        // Gonna do software rendering for now
        graphics_draw_text(disp, 20, 20, "Look at me mom");
        graphics_draw_box(disp, 40, 40, 128, 128, 0xFFFFFFFF);

	// swap bufs
	display_show(disp);
    }
}
