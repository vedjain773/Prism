#include "fft.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

cfft_cfg create_cfft_cfg(size_t size)
{
    cfft_cfg cfg;
    
    cfg.size = size;

    Complex* twiddle_table = malloc(sizeof(Complex) * size / 2);
    size_t* bit_perm = malloc(sizeof(size_t) * size);

    const double PI = acos(-1);

    for (size_t i = 0; i < size / 2; i++)
    {
        float denom = (float) size;
        float k_f = (float) i;

        twiddle_table[i] = cis(-2 * PI * k_f / denom);
    }

    size_t num_of_bits = log2(size);
    
    for (size_t i = 0; i < size; i++)
    {
        int index = i;
        int new_index = 0;
        
        for (size_t j = 0; j < num_of_bits; j++)
        {
            new_index <<= 1;
            new_index += index % 2;
            index >>= 1;
        }

        bit_perm[i] = new_index;
    }

    cfg.twiddle_table = twiddle_table;
    cfg.bit_perm = bit_perm;

    return cfg;
}

void cfft_execute(cfft_cfg* cfg, float* buffer, Complex* output)
{
    Complex inp[cfg->size];

    for (size_t i = 0; i < cfg->size; i++)
    {
        inp[i].re = buffer[i];
        inp[i].im = 0.00f;
    }

    cfft(cfg, inp, output);
}

void cfft(cfft_cfg* cfg, Complex* input, Complex* output)
{
    size_t size = cfg->size;
    Complex* twiddle_table = cfg->twiddle_table;
    bit_rev_swaps(input, output, cfg->bit_perm, size);
    
    int num_of_stages = log2(size);
    size_t gap = 1;

    for (size_t i = 0; i < num_of_stages; i++)
    {
        size_t curr_index = 0;
        while (curr_index + gap < size)
        {
            size_t j = 0;
            
            while (j < gap) 
            {
                Complex even = output[curr_index + j];
                Complex odd = output[curr_index + j + gap];

                Complex factor = twiddle_table[j * size / (gap * 2)];
                Complex term_2 = mul(&factor, &odd);
                Complex neg_term_2 = neg(&term_2);

                output[curr_index + j] = add(&even, &term_2);
                output[curr_index + j + gap] = add(&even, &neg_term_2);
                j += 1;
            }

            curr_index += gap * 2;
        }

        gap *= 2;
    }
}

void free_cfg(cfft_cfg* cfg)
{
    free(cfg->twiddle_table);
    free(cfg->bit_perm);
}

void bit_rev_swaps(Complex* input, Complex* output, size_t* bit_perm, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        size_t new_index = bit_perm[i];
        output[new_index] = input[i];
    }
}
