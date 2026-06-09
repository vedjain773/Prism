#include "fft.h"
#include <math.h>

void compute_fft(
        kiss_fft_cfg cfg,
        kiss_fft_cpx* in,
        kiss_fft_cpx* out,
        float* buffer,
        size_t size)
{
    for (size_t i = 0; i < size; i++) {
        in[i].r = buffer[i];
        in[i].i = 0.0f;
    }

    kiss_fft(cfg, in, out);
}

void compute_mags(float* mags, size_t size, kiss_fft_cpx* out)
{
    for (size_t i = 0; i < size; i++) 
    {
        mags[i] = sqrtf(out[i].r * out[i].r + out[i].i * out[i].i); 
    }
}
