#include "capture.h"
#include <stdio.h>

int main()
{
    float buffer[2048]; 
    init_ma();
    
    while (1) {
        get_latest_samples(buffer, 2048);
        printf("%f\n", buffer[2047]);
    }

    dinit_ma();

    return 0;
}
