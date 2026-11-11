#include "gb.h"
#include <stdio.h>

int main(void){
    //create a fake rom with 32768(smallest real Game Boy cartridge)
    uint8_t rom[32768] = {0};

    //create a fake 32 KB ROM and a Game Boy from it, with the size computed by sizeof
    GB *gb = gb_create(rom, sizeof(rom));

    //check for failure
    if(gb == NULL){
        printf("Failed to create Game Boy\n");
        return 1;
    }
    //run one frame
    gb_run_frame(gb);
    //read and print the first pixel
    const uint32_t *pixels = gb_framebuffer(gb);
    //read the first pixel and print it as 8 hex digits
    printf("%08X\n", (unsigned)pixels[0]);
    printf("%08X\n", (unsigned)pixels[GB_SCREEN_WIDTH * GB_SCREEN_HEIGHT - 1]);
    //turn off the gb
    gb_destroy(gb);
    return 0;
}
