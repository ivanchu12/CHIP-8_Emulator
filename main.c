#include <stdlib.h>
#include <sys/time.h>
#include "cpu.h"
#include "debug.h"

int main(int argc, char *argv[]){

    int cycle_count = 0;

    if (argc != 2){
        printf("Incorrect usage. No ROM file indicated\n");
        return 0;
    }

    // CHIP8 CPU running at 500Hz frequency
    unsigned long cycle_time = 2000; //1000*1000/500
    unsigned long dct = 0;

    // CHIP8 timers are updated with 60Hz frequency
    unsigned long timers_time = (1000000/60);
    unsigned long dtt = 0;

    Chip8* chip8 = (Chip8*)malloc(sizeof(Chip8));
    init(chip8);
    load_ROM(chip8, argv[1]);

    struct timeval lastTime, currentTime;
    gettimeofday(&lastTime, NULL);

    while (1){
        gettimeofday(&currentTime, NULL);
        dct += (currentTime.tv_usec - lastTime.tv_usec)%__LONG_MAX__;
        dtt += (currentTime.tv_usec - lastTime.tv_usec)%__LONG_MAX__;

        lastTime.tv_sec = currentTime.tv_sec;
        lastTime.tv_usec = currentTime.tv_usec;

        if (dct > cycle_time){
            cycle(chip8);
	        LOG("[ CPU INFO ] Cycle: %d, pc: %X, opcode: %X\n", cycle_count++, chip8->pc, chip8->opcode);
            dct = 0;
        }
        if (dtt > timers_time){
            update_timers(chip8);
            dtt = 0;
        }
    }
}
