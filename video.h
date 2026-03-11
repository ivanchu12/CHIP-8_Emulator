#include <SDL2/SDL.h>
#include "cpu.h"

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;
    SDL_Texture* texture;
} Screen;

void init_screen(Screen* screen, Chip8* chip8);
void draw(Screen* screen);