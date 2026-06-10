#include "fft.h"
#include <math.h>

fft_cfg fft_config(float sample_size, float min_freq, float max_freq, float sample_rate)
{
    fft_cfg cfg;

    cfg.sample_size = sample_size;
    cfg.min_freq = min_freq;
    cfg.max_freq = max_freq;
    cfg.sample_rate = sample_rate;
    cfg.ss_sr_ratio = sample_size / sample_rate;

    return cfg;
}

void compute_fft(
        kiss_fft_cfg cfg,
        kiss_fft_cpx* in,
        kiss_fft_cpx* out,
        float* buffer,
        size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
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

float freq_to_bin(float freq, fft_cfg* cfg) 
{
    return freq * cfg->ss_sr_ratio;
}

void compute_bar_bins(float* bar_start_bin, size_t num_bars, fft_cfg* cfg)
{
    for (int i = 0; i <= num_bars; i++) 
    {
        float t = (float)i / num_bars;
        float freq = cfg->min_freq * powf(cfg->max_freq / cfg->min_freq, t);
        bar_start_bin[i] = freq_to_bin(freq, cfg);
    }
}

void fill_bars(float* mags, float* bars, size_t num_bars, float* bar_start_bin, fft_cfg* cfg)
{
    for (int i = 0; i < num_bars; i++) 
    {
        int start = (int)bar_start_bin[i];
        int end   = (int)bar_start_bin[i + 1];

        if (end <= start) end = start + 1;          
        end = end > cfg->sample_size / 2 ? cfg->sample_size / 2 : end;  

        float max = 0.0f;

        for (int j = start; j < end; j++) 
        {
            max = mags[j] > max ? mags[j]: max;
        }

        bars[i] = max;
    }
}

