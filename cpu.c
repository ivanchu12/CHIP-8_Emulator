#include <string.h>
#include "cpu.h"

void load_font(Chip8* chip8){
    for (int i = 0; i < FONT_LENGTH; i++){
        chip8->memory[FONT_BASE_ADDRESS + i] = FONT_SPRITES[i];
    }
}

void init(Chip8* chip8){
    memset(chip8->registers, 0, NUM_REGISTERS);
    memset(chip8->keypad, 0, NUM_KEYS);
    load_font(chip8);

    // Not finished, will have to initialize the other values once I know their initial state
}