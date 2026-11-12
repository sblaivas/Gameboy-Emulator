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
    //If window not created, quit
    if (window == NULL) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
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
    }
    //clean up in reverse order of creation.
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}
