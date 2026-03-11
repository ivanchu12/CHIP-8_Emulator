#include <SDL2/SDL.h>
#include "video.h"
#include "cpu.h"

SDL_Color palette[2] = {{0, 0, 0, 255}, {255, 255, 255, 255}};

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