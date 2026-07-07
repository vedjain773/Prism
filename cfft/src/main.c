#include "fft.h"
#include <stdio.h>
#include <time.h>

#define SIZE 1024
#define NUMBENCH 10000

int main()
{
    struct timespec start, end;
    float buffer[SIZE];

    for (size_t i = 0; i < SIZE; i++) 
    {
        buffer[i] = 1.00f;    
    }

    Complex output[SIZE];

    cfft_cfg cfg = create_cfft_cfg(SIZE);
    
    timespec_get(&start, TIME_UTC);
    for (size_t i = 0; i < NUMBENCH; i++)
    {
        cfft_execute(&cfg, buffer, output);
    }
    timespec_get(&end, TIME_UTC);
   
    double time_taken = (end.tv_nsec - start.tv_nsec) / 1e6;   

    printf("Time elapsed: %f\n", time_taken);

    free_cfg(&cfg); 
    return 0;
}
