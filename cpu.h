#ifndef CPU.H
#define CPU.H
#include <stdint.h>

typedef struct {
    uint8_t memory[4096]; // Main memory

    uint8_t registers[16]; // 8-bit registers
    uint16_t ir; // Index Register
    uint16_t pc; // Program Counter

    uint8_t sp; // Stack Pointer
    uint16_t stack[16]; // Stack

    uint8_t dt; // Delay Timer
    uint8_t st; //Sound

    uint8_t keypad[16]; // Input keys

    uint8_t display[2048]; // Display 64x32

    uint16_t opcode; // Current Operation code
} Chip8;

#endif
