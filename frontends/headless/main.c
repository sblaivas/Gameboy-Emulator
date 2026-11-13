#include "gb.h"
#include <stdio.h>
#include <stdlib.h>   

static uint8_t *load_file(const char *path, size_t *out_size) {
    //open the file
    FILE *file = fopen(path, "rb");
    if (file == NULL){
        return NULL; 
    }
    // find its size
    //move pointer to end of file
    fseek(file, 0, SEEK_END);   
    //check where pointer is and thats the size
    long size = ftell(file);   
    //move it back to start
    rewind(file);    
    if (size < 0){
        fclose(file);
        return NULL;
    }
    // malloc a buffer to make room
    uint8_t *buffer = malloc(size);
    if (buffer == NULL){
        fclose(file);
        return NULL;
    }
    //copy the bytes in into the buffer, and make sure all of it arrived.
    size_t read = fread(buffer, 1, size, file);
    // fclose the file
    fclose(file);
     // Make sure the whole file arrived.
    if (read != (size_t)size) {
        free(buffer);
        return NULL;
    }

    // Give the size back through the pointer, and return the buffer.
    *out_size = (size_t)size;
    return buffer;
    
}

int main(int argc, char *argv[]){
    if (argc < 2) {
        printf("usage: %s <rom.gb>\n", argv[0]);
        return 1;
    }
    //load the ROM file named on the command line
    size_t rom_size;
    uint8_t *rom = load_file(argv[1], &rom_size);
    if (rom == NULL) {
        printf("Failed to load ROM: %s\n", argv[1]);
        return 1;
    }
    printf("Loaded %zu bytes\n", rom_size);


    GB *gb = gb_create(rom, rom_size);

    //check for failure
    if(gb == NULL){
        printf("Failed to create Game Boy\n");
        free(rom);
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
    free(rom);
    return 0;
}
