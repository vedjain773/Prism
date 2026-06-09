#ifndef FFT_H
#define FFT_H

#include "kiss_fft.h"
#include <stddef.h>

void compute_fft(
        kiss_fft_cfg cfg,
        kiss_fft_cpx* in,
        kiss_fft_cpx* out,
        float* buffer,
        size_t size);

void compute_mags(float* mags, size_t size, kiss_fft_cpx* out);

#endif
