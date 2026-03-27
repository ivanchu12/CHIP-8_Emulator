#include <SDL2/SDL.h>
#include "ui.h"
#include "cpu.h"

SDL_Color palette[2] = {{7, 85, 59, 255}, {206, 212, 106, 255}};

void init_screen(Screen* screen, Chip8* chip8){
    SDL_Init(SDL_INIT_VIDEO);

    screen->window = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 400, SDL_WINDOW_SHOWN);
    screen->renderer =  SDL_CreateRenderer(screen->window, -1, SDL_RENDERER_ACCELERATED);
    screen->surface = SDL_CreateRGBSurface(0, DISPLAY_X, DISPLAY_Y, 8, 0, 0, 0, 0);
    SDL_SetPaletteColors(screen->surface->format->palette, palette, 0, 2);
    screen->surface->pixels = chip8->display;
}

void draw(Screen* screen){
    screen->texture = SDL_CreateTextureFromSurface(screen->renderer, screen->surface);
    SDL_RenderClear(screen->renderer);
    SDL_RenderCopy(screen->renderer, screen->texture, NULL, NULL);
    SDL_RenderPresent(screen->renderer);

    // We delete the texture each time since it will be recreated the next time we call draw function
    SDL_DestroyTexture(screen->texture);
}

int proces_input(Chip8* chip8){
    int quit = 0;
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT: quit = 1; break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                    case SDLK_ESCAPE: quit = 1; break;
                    case SDLK_x: chip8->keypad[0] = 1; break;
                    case SDLK_1: chip8->keypad[1] = 1; break;
                    case SDLK_2: chip8->keypad[2] = 1; break;
                    case SDLK_3: chip8->keypad[3] = 1; break;
                    case SDLK_q: chip8->keypad[4] = 1; break;
                    case SDLK_w: chip8->keypad[5] = 1; break;
                    case SDLK_e: chip8->keypad[6] = 1; break;
                    case SDLK_a: chip8->keypad[7] = 1; break;
                    case SDLK_s: chip8->keypad[8] = 1; break;
                    case SDLK_d: chip8->keypad[9] = 1; break;
                    case SDLK_z: chip8->keypad[10] = 1; break;
                    case SDLK_c: chip8->keypad[11] = 1; break;
                    case SDLK_4: chip8->keypad[12] = 1; break;
                    case SDLK_r: chip8->keypad[13] = 1; break;
                    case SDLK_f: chip8->keypad[14] = 1; break;
                    case SDLK_v: chip8->keypad[15] = 1; break;
                }; break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym){
                    case SDLK_ESCAPE: quit = 1; break;
                    case SDLK_x: chip8->keypad[0] = 0; break;
                    case SDLK_1: chip8->keypad[1] = 0; break;
                    case SDLK_2: chip8->keypad[2] = 0; break;
                    case SDLK_3: chip8->keypad[3] = 0; break;
                    case SDLK_q: chip8->keypad[4] = 0; break;
                    case SDLK_w: chip8->keypad[5] = 0; break;
                    case SDLK_e: chip8->keypad[6] = 0; break;
                    case SDLK_a: chip8->keypad[7] = 0; break;
                    case SDLK_s: chip8->keypad[8] = 0; break;
                    case SDLK_d: chip8->keypad[9] = 0; break;
                    case SDLK_z: chip8->keypad[10] = 0; break;
                    case SDLK_c: chip8->keypad[11] = 0; break;
                    case SDLK_4: chip8->keypad[12] = 0; break;
                    case SDLK_r: chip8->keypad[13] = 0; break;
                    case SDLK_f: chip8->keypad[14] = 0; break;
                    case SDLK_v: chip8->keypad[15] = 0; break;
                }; break;
        }
    }
    

    return quit;
}