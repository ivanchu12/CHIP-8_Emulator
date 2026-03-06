#include <string.h>
#include "cpu.h"

uint8_t get_first_operand(uint16_t opcode){
    return (opcode & 0x0F00) >> 8;
}

uint8_t get_second_operand(uint16_t opcode){
    return (opcode & 0x00F0) >> 4;
}

uint16_t get_address(uint16_t opcode){
    return opcode & 0x0FFF;
}

uint8_t get_value(uint16_t opcode){
    return opcode & 0x00FF;
}

void OP_0nnn(Chip8* chip8){
    // Do nothing, function is not used in mdoern CHIP-8
}

void OP_00E0(Chip8* chip8){
    memset(chip8->display, 0, DISPLAY_SIZE);
}

void OP_00EE(Chip8* chip8){
    chip8->sp -= 1;
    chip8->pc = chip8->stack[chip8->sp];
}

void OP_1nnn(Chip8* chip8){
    uint16_t addr = get_address(chip8->opcode);
    chip8->pc = addr;
}

void OP_2nnn(Chip8* chip8){
    uint16_t addr = get_address(chip8->opcode);
    chip8->stack[chip8->sp] = chip8->pc;
    chip8->sp += 1;
    chip8->pc = addr;
}

void OP_3xkk(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    uint8_t kk = get_value(chip8->opcode);
    if (chip8->registers[vx] == kk){
        chip8->pc += 2;
    }
}

void OP_4xkk(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    uint8_t kk = get_value(chip8->opcode);
    if (chip8->registers[vx] != kk){
        chip8->pc += 2;
    }
}

void OP_5xy0(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    uint8_t vy = get_second_operand(chip8->opcode);
    if (chip8->registers[vx] == chip8->registers[vy]){
        chip8->pc += 2;
    }
}

void OP_6xkk(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    uint8_t kk = get_value(chip8->opcode);
    chip8->registers[vx] = kk;
}

void OP_7xkk(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    uint8_t kk = get_value(chip8->opcode);
    chip8->registers[vx] += kk;
}

void OP_8xy0(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    uint8_t vy = get_second_operand(chip8->opcode);
    chip8->registers[vx] = chip8->registers[vy];
}

void OP_8xy1(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    uint8_t vy = get_second_operand(chip8->opcode);
    chip8->registers[vx] = chip8->registers[vx] | chip8->registers[vy];
}   

void OP_8xy2(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    uint8_t vy = get_second_operand(chip8->opcode);
    chip8->registers[vx] = chip8->registers[vx] & chip8->registers[vy];
}   

void OP_8xy3(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    uint8_t vy = get_second_operand(chip8->opcode);
    chip8->registers[vx] = chip8->registers[vx] ^ chip8->registers[vy];
} 

void OP_8xy4(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    uint8_t vy = get_second_operand(chip8->opcode);
    uint16_t result = chip8->registers[vx] + chip8->registers[vy];
    
    chip8->registers[15] = (result > 255)? 1 : 0;
    chip8->registers[vx] = result & 0xFF;
}

void OP_8xy5(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    uint8_t vy = get_second_operand(chip8->opcode);
    
    chip8->registers[15] = (chip8->registers[vx] > chip8->registers[vy])? 1 : 0;
    chip8->registers[vx] = chip8->registers[vx] - chip8->registers[vy];
}

void OP_8xy6(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    chip8->registers[15] = (chip8->registers[vx] & 0x01);
    chip8->registers[vx] = chip8->registers[vx] >> 1;
}

void OP_8xy7(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    uint8_t vy = get_second_operand(chip8->opcode);
    
    chip8->registers[15] = (chip8->registers[vy] > chip8->registers[vx])? 1 : 0;
    chip8->registers[vy] = chip8->registers[vy] - chip8->registers[vx];
}

void OP_8xyE(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    chip8->registers[15] = (chip8->registers[vx] & 0x80) >> 128;
    chip8->registers[vx] = chip8->registers[vx] << 1;
}

void OP_9xy0(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    uint8_t vy = get_second_operand(chip8->opcode);
    if (chip8->registers[vx] != chip8->registers[vy]){
        chip8->pc += 2;
    }
}

void OP_Annn(Chip8* chip8){
    uint16_t addr = get_address(chip8->opcode);
    chip8->ir = addr;
}

void OP_Bnnn(Chip8* chip8){
    uint16_t addr = get_address(chip8->opcode);
    chip8->pc = addr + chip8->registers[0];
}

void OP_Fx07(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    chip8->registers[vx] = chip8->dt;
}

void OP_Fx15(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    chip8->dt = chip8->registers[vx];
}

void OP_Fx18(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    chip8->st = chip8->registers[vx];
}

void OP_Fx1E(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    chip8->ir += chip8->registers[vx];
}