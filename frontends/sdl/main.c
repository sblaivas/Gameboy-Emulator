#include "gb.h"
#include <stdio.h>
#include <SDL.h>

int main(int argc, char *argv[]){
    (void)argc;
    (void)argv;
    
    // Start SDL's video system. It returns a negative number on failure.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // SDL_GetError() returns a string explaining what went wrong.
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }
    //Create the window 4x the Game Boys screen size
    SDL_Window *window = SDL_CreateWindow("gbemu", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GB_SCREEN_WIDTH * 4, GB_SCREEN_HEIGHT * 4,0);
    if (window == NULL) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    

   //Render: what we will draw onto the window
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 
        -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL) {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    //Texture: the image stored on the graphics card where we copy framebuffer into it and renderer
    //will stretch to fill the window
    SDL_Texture *texture =  SDL_CreateTexture(renderer, 
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, GB_SCREEN_WIDTH, GB_SCREEN_HEIGHT);

    if (texture == NULL) {
        printf("SDL_CreateTexture failed: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    //create a fake ROM and a Game Boy from it.
    uint8_t rom[32768] = {0};
    GB *gb = gb_create(rom, sizeof(rom));
    if (gb == NULL) {
        printf("Failed to create Game Boy\n");
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    //main loop where we keep running until the window is closed
    SDL_Event event;
    int running = 1;
    while (running) {
        //we will handle every event thats waiting.
        while (SDL_PollEvent(&event)) {
            //the windows close button was clicked.
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        //draws the next frame into the framebuffer
        gb_run_frame(gb);
        //copies the framebuffer into the texture
        SDL_UpdateTexture(texture, NULL, gb_framebuffer(gb), GB_SCREEN_WIDTH * sizeof(uint32_t));
        //draws the texture onto the window where we strech all of the textures,stretched to lal the window
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        //shows the finished frame on screen
        SDL_RenderPresent(renderer);
        

    }
    gb_destroy(gb);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
