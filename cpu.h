#ifndef CPU.H
#define CPU.H
#include <stdint.h>

const int NUM_REGISTERS = 16;
const int VF_REGISTER = 15;
const int NUM_KEYS = 16;
const int MEMORY_SIZE = 4096;
const int STACK_SIZE = 16;

const int DISPLAY_X = 64;
const int DISPLAY_Y = 32;
const int DISPLAY_SIZE = DISPLAY_X * DISPLAY_Y;

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

const int FONT_BASE_ADDRESS = 0x50;
const int FONT_LENGTH = 16;
uint8_t FONT_SPRITES[] = {
    0XF0, 0X90, 0X90, 0X90, 0XF0, // 0
    0X20, 0X60, 0X20, 0X20, 0X70, // 1
    0XF0, 0X10, 0XF0, 0X80, 0XF0, // 2
    0XF0, 0X10, 0XF0, 0X10, 0XF0, // 3
    0X90, 0X90, 0XF0, 0X10, 0X10, // 4
    0XF0, 0X80, 0XF0, 0X10, 0XF0, // 5
    0XF0, 0X80, 0XF0, 0X90, 0XF0, // 6
    0XF0, 0X10, 0X20, 0X40, 0X40, // 7
    0XF0, 0X90, 0XF0, 0X90, 0XF0, // 8
    0XF0, 0X90, 0XF0, 0X10, 0XF0, // 9
    0XF0, 0X90, 0XF0, 0X90, 0X90, // A
    0XE0, 0X90, 0XE0, 0X90, 0XE0, // B
    0XF0, 0X80, 0X80, 0X80, 0XF0, // C
    0XE0, 0X90, 0X90, 0X90, 0XE0, // D
    0XF0, 0X80, 0XF0, 0X80, 0XF0, // E
    0XF0, 0X80, 0XF0, 0X80, 0X80  // F
};

void init(Chip8* chip8);

#endif
