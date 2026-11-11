#include "gb_internal.h"
#include <stdlib.h>

//turn on a Game Boy
//this function will ask for a zeroed block of memory big enough for one Game Boy, 
//and return its address,or NULL if no memory was available.
GB *gb_create(const uint8_t *rom, size_t rom_size){
    (void)rom;
    (void)rom_size;

    GB *gb = calloc(1,sizeof(*gb));

    if (gb == NULL) {
        return NULL;
    }
    return gb;
}

//turn it off
//free the gameboy
void gb_destroy(GB *gb){
    free(gb);
}

//get the picture out
//take a Game Boy and returns the read only address of its screen pixels,
//so the frontend can display them without copying them or being able to change them.
const uint32_t *gb_framebuffer(const GB *gb){
    return gb->framebuffer;
}
//send input in
// Save which buttons are currently held (one bit per button).
void gb_set_buttons(GB *gb, uint8_t buttons){
    gb->buttons = buttons;
}

//run the game for one frame
void gb_run_frame(GB *gb){
    for(int i = 0; i < GB_SCREEN_WIDTH * GB_SCREEN_HEIGHT; i++){
        gb->framebuffer[i] =  0xFF00FF00;
    }
}