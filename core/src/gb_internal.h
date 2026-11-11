//This file holds the definition of everything inside the emulated Game Boy, 
//so that all the cores .c files can share and work on the same machine, 
//while the frontends stay locked out.
#ifndef GB_INTERNAL_H
#define GB_INTERNAL_H


#include "gb.h"

struct GB{
    //This array is the Game Boys screen stored in memory. 
    uint32_t framebuffer[GB_SCREEN_WIDTH * GB_SCREEN_HEIGHT];
    uint8_t buttons;
};

#endif
