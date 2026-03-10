#include <string.h>
#include "cpu.h"

void load_font(Chip8* chip8){
    for (int i = 0; i < FONT_LENGTH; i++){
        chip8->memory[FONT_BASE_ADDRESS + i] = FONT_SPRITES[i];
    }
}

void init(Chip8* chip8){
    memset(chip8->memory, 0, MEMORY_SIZE);
    memset(chip8->stack, 0, STACK_SIZE);
    memset(chip8->display, 0, DISPLAY_SIZE);
    memset(chip8->registers, 0, NUM_REGISTERS);
    memset(chip8->keypad, 0, NUM_KEYS);

    chip8->pc = ROM_BASE_ADDRESS;
    chip8->opcode = 0;
    chip8->ir = 0;
    chip8->dt = 0;
    chip8->sp = 0;
    chip8->st = 0;
    load_font(chip8);
}

void fetch(Chip8* chip8){
    chip8->opcode = (chip8->memory[chip8->pc] << 8) | chip8->memory[chip8->pc + 1];
    chip8->pc += 2;
}

void execute(Chip8* chip8){
    switch (chip8->opcode & 0xF000){
        case 0x0000: 
            switch (chip8->opcode & 0x00FF){
                case 0x00E0: OP_00E0(chip8); break;
                case 0x00EE: OP_00EE(chip8); break;
                default: OP_0nnn(chip8);
            }; break;
        case 0X1000: OP_1nnn(chip8); break;
        case 0x2000: OP_2nnn(chip8); break;
        case 0x3000: OP_3xkk(chip8); break;
        case 0x4000: OP_4xkk(chip8); break;
        case 0x5000: OP_5xy0(chip8); break;
        case 0x6000: OP_6xkk(chip8); break;
        case 0x7000: OP_7xkk(chip8); break;
        case 0x8000:
            switch (chip8->opcode & 0x000F){
                case 0x0000: OP_8xy0(chip8); break;
                case 0x0001: OP_8xy1(chip8); break;
                case 0x0002: OP_8xy2(chip8); break;
                case 0x0003: OP_8xy3(chip8); break;
                case 0x0004: OP_8xy4(chip8); break;
                case 0x0005: OP_8xy5(chip8); break;
                case 0x0006: OP_8xy6(chip8); break;
                case 0x0007: OP_8xy7(chip8); break;
                case 0x000E: OP_8xyE(chip8); break;
                default: OP_0nnn(chip8);
            }; break;
        case 0x9000: OP_9xy0(chip8); break;
        case 0xA000: OP_Annn(chip8); break;
        case 0xB000: OP_Bnnn(chip8); break;
        case 0xC000: OP_Cxkk(chip8); break;
        case 0xD000: OP_Dxyn(chip8); break;
        case 0xE000:
            switch (chip8->opcode & 0x00FF){
                case 0x009E: OP_Ex9E(chip8); break;
                case 0x00A1: OP_ExA1(chip8); break;
                default: OP_0nnn(chip8);
            }; break;
        case 0xF000:
            switch (chip8->opcode & 0x00FF){
                case 0x0007: OP_Fx07(chip8); break;
                case 0x000A: OP_Fx0A(chip8); break;
                case 0x0015: OP_Fx15(chip8); break;
                case 0x0018: OP_Fx18(chip8); break;
                case 0x001E: OP_Fx1E(chip8); break;
                case 0x0029: OP_Fx29(chip8); break;
                case 0x0033: OP_Fx33(chip8); break;
                case 0x0055: OP_Fx55(chip8); break;
                case 0x0065: OP_Fx65(chip8); break;
                default: OP_0nnn(chip8);
            }; break;
        default: OP_0nnn(chip8);
    }
}