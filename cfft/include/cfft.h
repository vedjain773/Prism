#include "complex.h"
#include <stddef.h>

typedef struct {
    size_t size;
    Complex* twiddle_table;
    size_t* bit_perm;
} cfft_cfg;

cfft_cfg create_cfft_cfg(size_t size);
void cfft_execute(cfft_cfg* cfg, float* buffer, Complex* output);
void cfft(cfft_cfg* cfg, Complex* input, Complex* output);
void free_cfg(cfft_cfg* cfg);

void bit_rev_swaps(Complex* input, Complex* output, size_t* bit_perm, size_t size);
