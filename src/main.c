#include "capture.h"
#include "utils.h"
#include "fft.h"
#include <stdio.h>

#define TRUE 1
#define FFT_SAMPLE 2048
#define SAMPLE_RATE 44100

int main()
{   
    kiss_fft_cfg cfg = kiss_fft_alloc(FFT_SAMPLE, 0, NULL, NULL);

    kiss_fft_cpx fft_in[FFT_SAMPLE];
    kiss_fft_cpx fft_out[FFT_SAMPLE];

    float magnitudes[FFT_SAMPLE / 2];

    float hann_coeffs[FFT_SAMPLE];
    compute_hann_coeffs(hann_coeffs, FFT_SAMPLE);

    float buffer[FFT_SAMPLE]; 
    init_ma();
   
    while (TRUE)
    {
        get_latest_samples(buffer, FFT_SAMPLE);
        remove_dc(buffer, FFT_SAMPLE);
        
        apply_windowing_func(buffer, hann_coeffs, FFT_SAMPLE);
        
        compute_fft(cfg, fft_in, fft_out, buffer, FFT_SAMPLE);
        compute_mags(magnitudes, FFT_SAMPLE / 2, fft_out);

        float peak_mag = 0.0f;
        int peak_bin = 0;
        for (int i = 1; i < FFT_SAMPLE / 2; i++) 
        {
            if (magnitudes[i] > peak_mag)
            {
                peak_mag = magnitudes[i];
                peak_bin = i;
            }
        }

        float peak_freq = peak_bin * SAMPLE_RATE / (float)FFT_SAMPLE;
        printf("peak bin: %d  freq: %.1f Hz  mag: %.4f\n", peak_bin, peak_freq, peak_mag);
    }

    dinit_ma();
    kiss_fft_free(cfg);

    return 0;
}
