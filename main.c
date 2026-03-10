#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "cpu.h"

int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Incorrect usage. No ROM file indicated\n");
        return 0;
    }

    // CHIP8 CPU running at 500Hz frequency
    float cycle_time = (1/500) * 1000;
    float dct = 0;

    // CHIP8 timers are updated with 60Hz frequency
    float timers_time = (1/60) * 1000;
    float dtt = 0;

    Chip8* chip8 = (Chip8*)malloc(sizeof(Chip8));
    init(chip8);
    load_ROM(chip8, argv[1]);

    struct timeval lastTime, currentTime;
    gettimeofday(&lastTime, NULL);

    while (1){
        gettimeofday(&currentTime, NULL);
        dct += currentTime.tv_usec/1000 - lastTime.tv_usec/1000;
        dtt += currentTime.tv_usec/1000 - lastTime.tv_usec/1000;

        lastTime.tv_sec = currentTime.tv_sec;
        lastTime.tv_usec = currentTime.tv_usec;

        if (dct > cycle_time){
            cycle(chip8);
            dct = 0;
        }
        if (dtt > timers_time){
            update_timers(chip8);
            dtt = 0;
        }
    }
}