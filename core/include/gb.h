#ifndef GB_H
#define GB_H

#include <stdint.h>
#include <stddef.h>


typedef struct GB GB;
//Screen Size constants
#define GB_SCREEN_WIDTH 160
#define GB_SCREEN_HEIGHT 144

//Button Constants
#define GB_BUTTON_A  (1 << 0)
#define GB_BUTTON_B  (1 << 1)
#define GB_BUTTON_SELECT  (1 << 2)
#define GB_BUTTON_START  (1 << 3)
#define GB_BUTTON_RIGHT  (1 << 4)
#define GB_BUTTON_LEFT (1 << 5)
#define GB_BUTTON_UP (1 << 6)
#define GB_BUTTON_DOWN (1 << 7)


//turn on a Game Boy with a ROM
/*
Included:
1) give back a pointer to the new Gameboy
2) pointer to the ROM bytes.
3) how many bytes there are
*/
GB *gb_create(const uint8_t *rom, size_t rom_size);
//turn it off and free its memory

void gb_destroy(GB *gb);
//run one frame of emulation
void gb_run_frame(GB *gb);
//get the current screen image
/*
Get the current screen: GB_SCREEN_WIDTH * GB_SCREEN_HEIGHT pixels,
row by row from the top left, each pixel 0xAARRGGBB.
The pointer stays valid until gb_destroy is called.
*/
const uint32_t *gb_framebuffer(const GB *gb);
//tell it which buttons are pressed
//This takes the Game Boy plus one byte holding all eight buttons as bits, 
//exactly the bitmask from earlier. The frontend builds it with | and the core checks it with &.
void gb_set_buttons(GB *gb, uint8_t buttons);

#endif