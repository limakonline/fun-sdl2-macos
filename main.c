#include "SDL2/SDL.h"

#include <stdbool.h>
#include <stdio.h>

#define WIN_W 1024
#define WIN_H 720

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* helloWorld = NULL;
bool quit = false;

enum KeyPressSurface {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

void handle_key(int key) {
    switch (key) {
        case SDLK_UP:
            puts("UP");
            break;
        case SDLK_DOWN:
            puts("DOWN");
            break;
        case SDLK_RIGHT:
            puts("RIGHT");
            break;
        case SDLK_LEFT:
            puts("LEFT");
            break;
        case 113:
            quit = true;
            break;
        default:
            printf("unknown press %d\n", key);
            break;
    }
}

int main(void) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL not initilized: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_METAL);

    if (window == NULL) {
        printf("Window not initialized: %s\n", SDL_GetError());
        return 1;
    }

    screenSurface = SDL_GetWindowSurface(window);

    helloWorld = SDL_LoadBMP("some.bmp");

    if(helloWorld == NULL) {
        printf("Unable to load image %s, error: %s\n", "some.bmp", SDL_GetError());
        return 1;
    }

    SDL_BlitSurface(helloWorld, NULL, screenSurface, NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Event e;

    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT: 
                    quit = true;
                   break;
                case SDL_KEYDOWN:
                    handle_key(e.key.keysym.sym);
                   break;
            }
        }
    }

    SDL_FreeSurface(helloWorld);
    helloWorld = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();

    return 0;
}
