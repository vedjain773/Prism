#ifndef FFT_H
#define FFT_H

#include "cfft.h"
#include <stddef.h>

typedef struct {
    float sample_size;
    float min_freq;
    float max_freq;
    float sample_rate;
    float ss_sr_ratio;
} fft_cfg;

fft_cfg fft_config(float sample_size, float min_freq, float max_freq, float sample_rate);

void compute_mags(float* mags, size_t size, Complex* out);
float freq_to_bin(float freq, fft_cfg* cfg);
void compute_bar_bins(float* bar_start_bin, size_t num_bars, fft_cfg* cfg);
void fill_bars(float* mags, float* bars, size_t num_bars, float* bar_start_bin, fft_cfg* cfg);

#endif
