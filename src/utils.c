#include "utils.h"
#include <stddef.h>
#include <math.h>

void remove_dc(float* buffer, size_t size)
{
    float sum = 0.0f;

    for (size_t i = 0; i < size; i++)
        sum += buffer[i];

    float dc_off = sum / size;

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

