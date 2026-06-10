#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

void remove_dc(float* buffer, size_t size);
float find_peak(float* buffer, size_t size);

void compute_hann_coeffs(float* coeffs, size_t size);
void apply_windowing_func(float* buffer, float* coeffs, size_t size);

void normalize_bars(float* bars, size_t num_bars);

#endif
