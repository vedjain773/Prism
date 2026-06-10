#include "capture.h"
#include "utils.h"
#include "fft.h"
#include "raylib.h"
#include "render.h"
#include <stdio.h>

#define FFT_SAMPLE 2048
#define SAMPLE_RATE 44100

#define NUM_BARS 64
#define MIN_FREQ 20.0f
#define MAX_FREQ 20000.0f
#define WINDOW_HEIGHT 450
#define WINDOW_WIDTH 800

int main()
{   
    //Creating and filling bars
    float hann_coeffs[FFT_SAMPLE];
    compute_hann_coeffs(hann_coeffs, FFT_SAMPLE);
    
    kiss_fft_cfg cfg = kiss_fft_alloc(FFT_SAMPLE, 0, NULL, NULL);

    kiss_fft_cpx fft_in[FFT_SAMPLE];
    kiss_fft_cpx fft_out[FFT_SAMPLE];

    float magnitudes[FFT_SAMPLE / 2];

    fft_cfg config = fft_config(FFT_SAMPLE, MIN_FREQ, MAX_FREQ, SAMPLE_RATE);

    float bar_start_bin[NUM_BARS + 1];
    compute_bar_bins(bar_start_bin, NUM_BARS, &config);

    float bars[NUM_BARS];

    float buffer[FFT_SAMPLE];

    //Raylib init
    const int screen_width = WINDOW_WIDTH;
    const int screen_height = WINDOW_HEIGHT;
    render_cfg rconfig;

    set_render_cfg(NUM_BARS, WINDOW_WIDTH, WINDOW_HEIGHT, 1, &rconfig);

    Rectangle rects[NUM_BARS];

    InitWindow(screen_width, screen_height, "RE:CAVA");
    SetTargetFPS(60);

    init_ma();
   
    while (!WindowShouldClose())
    {
        get_latest_samples(buffer, FFT_SAMPLE);
        remove_dc(buffer, FFT_SAMPLE);
        
        apply_windowing_func(buffer, hann_coeffs, FFT_SAMPLE);
        
        compute_fft(cfg, fft_in, fft_out, buffer, FFT_SAMPLE);
        compute_mags(magnitudes, FFT_SAMPLE / 2, fft_out);
        
        fill_bars(magnitudes, bars, NUM_BARS, bar_start_bin, &config);
        normalize_bars(bars, NUM_BARS);
        fill_ray_rects(rects, bars, NUM_BARS, &rconfig);

        BeginDrawing();

            ClearBackground(RAYWHITE);
            render_rects(rects, NUM_BARS);

        EndDrawing();
    }
    
    CloseWindow();
    dinit_ma();
    kiss_fft_free(cfg);

    return 0;
}
