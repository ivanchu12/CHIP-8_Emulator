#include <string.h>
#include <sys/random.h>
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
    
    chip8->registers[VF_REGISTER] = (result > 255)? 1 : 0;
    chip8->registers[vx] = result & 0xFF;
}

void OP_8xy5(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    uint8_t vy = get_second_operand(chip8->opcode);
    
    chip8->registers[VF_REGISTER] = (chip8->registers[vx] > chip8->registers[vy])? 1 : 0;
    chip8->registers[vx] = chip8->registers[vx] - chip8->registers[vy];
}

void OP_8xy6(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    chip8->registers[VF_REGISTER] = (chip8->registers[vx] & 0x01);
    chip8->registers[vx] = chip8->registers[vx] >> 1;
}

void OP_8xy7(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    uint8_t vy = get_second_operand(chip8->opcode);
    
    chip8->registers[VF_REGISTER] = (chip8->registers[vy] > chip8->registers[vx])? 1 : 0;
    chip8->registers[vy] = chip8->registers[vy] - chip8->registers[vx];
}

void OP_8xyE(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    chip8->registers[VF_REGISTER] = (chip8->registers[vx] & 0x80) >> 7;
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

void OP_Cxkk(Chip8* chip8){
    uint8_t random_byte;
    getrandom(&random_byte, 1, 0);
    uint8_t vx = get_first_operand(chip8->opcode);
    uint8_t kk = get_value(chip8->opcode);
    chip8->registers[vx] = random_byte & kk;
}

void OP_Dxyn(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    uint8_t vy = get_second_operand(chip8->opcode);
    uint8_t n = chip8->opcode & 0x000F;

    uint8_t x = chip8->registers[vx] % DISPLAY_X;
    uint8_t y = chip8->registers[vy] % DISPLAY_Y;
    int current_display_pos;
    for (int i = 0; i<n; i++){
        current_display_pos = x + (y+i)*DISPLAY_X;
        int8_t updated_sprite = chip8->memory[chip8->ir + i];
        
        uint8_t mask = 0x80;
        uint8_t original;
        uint8_t result;
        for (int j = 0; j<8; j++){
            if (current_display_pos%DISPLAY_X >= x){
                original = chip8->display[current_display_pos];
                result = chip8->display[current_display_pos] ^ ((updated_sprite & mask) >> (7 - j));
                chip8->display[current_display_pos] = result;

                chip8->registers[VF_REGISTER] = (original == 1 && result == 0)? (1 | chip8->registers[VF_REGISTER]) : (0 | chip8->registers[VF_REGISTER]);
                current_display_pos++;
            }
            mask >>= 1;
        }
    }
}

void OP_Ex9E(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);

    // We do not check if Vx value matches to one of the possible keys
    // No safeguard in the specification
    if (chip8->keypad[chip8->registers[vx]] == 1){
        chip8->pc += 2;
    }
}

void OP_ExA1(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);

    // We do not check if Vx value matches to one of the possible keys
    // No safeguard in the specification
    if (chip8->keypad[chip8->registers[vx]] != 1){
        chip8->pc += 2;
    }
}

void OP_Fx07(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    chip8->registers[vx] = chip8->dt;
}

void OP_Fx0A(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);

    uint8_t i = 0;
    uint8_t exit = 0;
    while (i < NUM_REGISTERS && !exit){
        if (chip8->keypad[i] == 1){
            chip8->registers[vx] = i;
            exit = 1;
        }
    }
    if (!exit){
        chip8->pc -= 2;
    }
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

void OP_Fx29(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    chip8->ir = chip8->memory[FONT_BASE_ADDRESS + 5 * chip8->registers[vx]];
}

void OP_Fx33(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    uint8_t x = chip8->registers[vx];

    uint8_t divisor = 10;
    for (int i = 2; i>=0; i--){
        chip8->memory[chip8->ir + i] = x%divisor;
        x /= 10;
    }
}

void OP_Fx55(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    for (int i = 0; i<=vx; i++){
        chip8->memory[chip8->ir + i] = chip8->registers[i];
    }
}

void OP_Fx65(Chip8* chip8){
    uint8_t vx = get_first_operand(chip8->opcode);
    for (int i = 0; i<=vx; i++){
        chip8->registers[i] = chip8->memory[chip8->ir + i];
    }
}