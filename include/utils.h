#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

void copy_arr(float* src, float* dest, size_t size);

void remove_dc(float* buffer, size_t size);
float find_peak(float* buffer, size_t size);

void compute_hann_coeffs(float* coeffs, size_t size);
void apply_windowing_func(float* buffer, float* coeffs, size_t size);

void normalize_bars(float* bars, size_t num_bars);
void smoothen(float* prev_bars, float* bars, size_t num_bars, float decay);
void apply_gravity(float* peak_bars, float* bars, size_t num_bars, float fall_speed);

#endif
