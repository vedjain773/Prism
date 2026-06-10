#include "utils.h"
#include <stddef.h>
#include <math.h>
#include <stdio.h>

void copy_arr(float* src, float* dest, size_t size)
{
    for (size_t i = 0; i < size; i++)
        dest[i] = src[i];
}

void remove_dc(float* buffer, size_t size)
{
    float sum = 0.0f;

    for (size_t i = 0; i < size; i++)
        sum += buffer[i];

    float dc_off;

    for (size_t i = 0; i < size; i++)
        buffer[i] -= dc_off;
}

float find_peak(float* buffer, size_t size)
{
    float max = 0.0f;

    for (size_t i = 0; i < size; i++)
    {
        float abs = buffer[i] < 0 ? -buffer[i] : buffer[i];
        max = abs > max ? abs : max;
    }

    return max;
}

void compute_hann_coeffs(float* coeffs, size_t size)
{
    const float PI = 3.14f;

    for (size_t i = 0; i < size; i++)
    {
        float cos_term = (2 * PI * i) / ((float) size);
        coeffs[i] = 0.5f * (1 - cos(cos_term));
    }
}

void apply_windowing_func(float* buffer, float* coeffs, size_t size) 
{
    for (size_t i = 0; i < size; i++)
    {
        buffer[i] *= coeffs[i];
    }    
}

void normalize_bars(float* bars, size_t num_bars)
{
    float max = 0.0f;
    for (size_t i = 0; i < num_bars; i++)
    {
        max = bars[i] > max ? bars[i] : max;
    }
    
    if (max > 0.0f)
    {
        for (size_t i = 0; i < num_bars; i++)
        {
            bars[i] /= max;
        }
    }
}

void smoothen(float* prev_bars, float* bars, size_t num_bars, float decay)
{
    for (size_t i = 0; i < num_bars; i++)
    {
        bars[i] = decay * prev_bars[i] + (1.00f - decay) * bars[i];
    }
}

void apply_gravity(float* peak_bars, float* bars, size_t num_bars, float fall_speed)
{
    for (size_t i = 0; i < num_bars; i++) 
    {
        if (peak_bars[i] < bars[i])
            peak_bars[i] = bars[i];
        else
            peak_bars[i] -= fall_speed;

        if (peak_bars[i] < 0.0f)
            peak_bars[i] = 0.0f;

        bars[i] = peak_bars[i];
    }
}
