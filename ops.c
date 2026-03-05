#include "cpu.h"

void OP_3xkk(Chip8* chip8){
    uint8_t vx = (chip8->opcode & 0x0F00) >> 8;
    uint8_t kk = chip8->opcode & 0x00FF;
    if (chip8->registers[vx] == kk){
        chip8->pc += 2;
    }
}

void OP_4xkk(Chip8* chip8){
    uint8_t vx = (chip8->opcode & 0x0F00) >> 8;
    uint8_t kk = chip8->opcode & 0x00FF;
    if (chip8->registers[vx] != kk){
        chip8->pc += 2;
    }
}

void OP_5xy0(Chip8* chip8){
    uint8_t vx = (chip8->opcode & 0x0F00) >> 8;
    uint8_t vy = (chip8->opcode & 0x00F0) >> 4;
    if (chip8->registers[vx] == chip8->registers[vy]){
        chip8->pc += 2;
    }
}

void OP_6xkk(Chip8* chip8){
    uint8_t vx = (chip8->opcode & 0x0F00) >> 8;
    uint8_t kk = chip8->opcode & 0x00FF;
    chip8->registers[vx] = kk;
}

void OP_7xkk(Chip8* chip8){
    uint8_t vx = (chip8->opcode & 0x0F00) >> 8;
    uint8_t kk = chip8->opcode & 0x00FF;
    chip8->registers[vx] += kk;
}

void OP_8xy0(Chip8* chip8){
    uint8_t vx = (chip8->opcode & 0x0F00) >> 8;
    uint8_t vy = (chip8->opcode & 0x00F0) >> 4;
    chip8->registers[vx] = chip8->registers[vy];
}

void OP_8xy1(Chip8* chip8){
    uint8_t vx = (chip8->opcode & 0x0F00) >> 8;
    uint8_t vy = (chip8->opcode & 0x00F0) >> 4;
    chip8->registers[vx] = chip8->registers[vx] | chip8->registers[vy];
}   

void OP_8xy2(Chip8* chip8){
    uint8_t vx = (chip8->opcode & 0x0F00) >> 8;
    uint8_t vy = (chip8->opcode & 0x00F0) >> 4;
    chip8->registers[vx] = chip8->registers[vx] & chip8->registers[vy];
}   

void OP_8xy3(Chip8* chip8){
    uint8_t vx = (chip8->opcode & 0x0F00) >> 8;
    uint8_t vy = (chip8->opcode & 0x00F0) >> 4;
    chip8->registers[vx] = chip8->registers[vx] ^ chip8->registers[vy];
} 

void OP_8xy4(Chip8* chip8){
    uint8_t vx = (chip8->opcode & 0x0F00) >> 8;
    uint8_t vy = (chip8->opcode & 0x00F0) >> 4;
    uint16_t result = chip8->registers[vx] + chip8->registers[vy];
    
    chip8->registers[15] = (result > 255)? 1 : 0;
    chip8->registers[vx] = result & 0xFF;
}

void OP_8xy5(Chip8* chip8){
    uint8_t vx = (chip8->opcode & 0x0F00) >> 8;
    uint8_t vy = (chip8->opcode & 0x00F0) >> 4;
    
    chip8->registers[15] = (chip8->registers[vx] > chip8->registers[vy])? 1 : 0;
    chip8->registers[vx] = chip8->registers[vx] - chip8->registers[vy];
}

void OP_8xy6(Chip8* chip8){
    uint8_t vx = (chip8->opcode & 0x0F00) >> 8;
    chip8->registers[15] = (chip8->registers[vx] & 0x01);
    chip8->registers[vx] = chip8->registers[vx] >> 1;
}

void OP_8xy7(Chip8* chip8){
    uint8_t vx = (chip8->opcode & 0x0F00) >> 8;
    uint8_t vy = (chip8->opcode & 0x00F0) >> 4;
    
    chip8->registers[15] = (chip8->registers[vy] > chip8->registers[vx])? 1 : 0;
    chip8->registers[vy] = chip8->registers[vy] - chip8->registers[vx];
}

void OP_8xyE(Chip8* chip8){
    uint8_t vx = (chip8->opcode & 0x0F00) >> 8;
    chip8->registers[15] = (chip8->registers[vx] & 0x80) >> 128;
    chip8->registers[vx] = chip8->registers[vx] << 1;
}

void OP_9xy0(Chip8* chip8){
    uint8_t vx = (chip8->opcode & 0x0F00) >> 8;
    uint8_t vy = (chip8->opcode & 0x00F0) >> 4;
    if (chip8->registers[vx] != chip8->registers[vy]){
        chip8->pc += 2;
    }
}

void OP_Annn(Chip8* chip8){
    uint16_t addr = chip8->opcode & 0x0FFF;
    chip8->ir = addr;
}

void OP_Bnnn(Chip8* chip8){
    uint16_t addr = chip8->opcode & 0x0FFF;
    chip8->pc = addr + chip8->registers[0];
}

void OP_Fx07(Chip8* chip8){
    uint8_t vx = (chip8->opcode & 0x0F00) >> 8;
    chip8->registers[vx] = chip8->dt;
}

void OP_Fx15(Chip8* chip8){
    uint8_t vx = (chip8->opcode & 0x0F00) >> 8;
    chip8->dt = chip8->registers[vx];
}

void OP_Fx18(Chip8* chip8){
    uint8_t vx = (chip8->opcode & 0x0F00) >> 8;
    chip8->st = chip8->registers[vx];
}

void OP_Fx1E(Chip8* chip8){
    uint8_t vx = (chip8->opcode & 0x0F00) >> 8;
    chip8->ir += chip8->registers[vx];
}