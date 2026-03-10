#pragma once
#include <stdint.h>

#define NUM_REGISTERS 16
#define VF_REGISTER 15
#define NUM_KEYS 16
#define MEMORY_SIZE 4096
#define STACK_SIZE 16

#define DISPLAY_X 64
#define DISPLAY_Y 32
#define DISPLAY_SIZE 2048 // DISPLAY_X * DISPLAY_Y

#define ROM_BASE_ADDRESS 0x200

typedef struct {
    uint8_t memory[MEMORY_SIZE]; // Main memory

    uint8_t registers[NUM_REGISTERS]; // 8-bit registers
    uint16_t ir; // Index Register
    uint16_t pc; // Program Counter

    uint8_t sp; // Stack Pointer
    uint16_t stack[STACK_SIZE]; // Stack

    uint8_t dt; // Delay Timer
    uint8_t st; //Sound

    uint8_t keypad[NUM_KEYS]; // Input keys

    uint8_t display[DISPLAY_SIZE]; // Display 64x32

    uint16_t opcode; // Current Operation code
} Chip8;

#define FONT_BASE_ADDRESS 0x50
#define FONT_LENGTH 16

void init(Chip8* chip8);
void load_ROM(Chip8* chip8, char* filename);
void fetch(Chip8* chip8);
void execute(Chip8* chip8);
void update_timers(Chip8* chip8);
void cycle(Chip8* chip8);
