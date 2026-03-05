#include "cpu.h"

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