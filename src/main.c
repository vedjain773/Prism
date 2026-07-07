#include "capture.h"
#include "utils.h"
#include "fft.h"
#include "raylib.h"
#include "render.h"
#include <string.h>
#include <stdio.h>

#define FFT_SAMPLE 2048
#define SAMPLE_RATE 44100

#define NUM_BARS 32
#define MIN_FREQ 20.0f
#define MAX_FREQ 20000.0f
#define WINDOW_HEIGHT 450
#define WINDOW_WIDTH 800

int main()
{   
    //Creating and filling bars
    float hann_coeffs[FFT_SAMPLE];
    compute_hann_coeffs(hann_coeffs, FFT_SAMPLE);
    
    Complex output[FFT_SAMPLE];

    cfft_cfg cfg = create_cfft_cfg(FFT_SAMPLE);

    float magnitudes[FFT_SAMPLE / 2];

    fft_cfg config = fft_config(FFT_SAMPLE, MIN_FREQ, MAX_FREQ, SAMPLE_RATE);

    float bar_start_bin[NUM_BARS + 1];
    compute_bar_bins(bar_start_bin, NUM_BARS, &config);

    float bars[NUM_BARS];
    float prev_bars[NUM_BARS];
    float peak_bars[NUM_BARS];

    memset(prev_bars, 0.0f, NUM_BARS * sizeof(float));
    memset(peak_bars, 0.0f, NUM_BARS * sizeof(float));

    float buffer[FFT_SAMPLE];

    //Raylib init
    const int screen_width = WINDOW_WIDTH;
    const int screen_height = WINDOW_HEIGHT;
    render_cfg rconfig;

    set_render_cfg(NUM_BARS, WINDOW_WIDTH, WINDOW_HEIGHT, 1, &rconfig);
    set_color(BLUE, VIOLET, &rconfig);

    Color color_arr[NUM_BARS];
    set_color_arr(color_arr, NUM_BARS, &rconfig);

    Rectangle rects[NUM_BARS];

    InitWindow(screen_width, screen_height, "Prism");
    SetTargetFPS(60);

    init_ma();
   
    while (!WindowShouldClose())
    {
        get_latest_samples(buffer, FFT_SAMPLE);
        remove_dc(buffer, FFT_SAMPLE);
        
        apply_windowing_func(buffer, hann_coeffs, FFT_SAMPLE);
       
        cfft_execute(&cfg, buffer, output);
        compute_mags(magnitudes, FFT_SAMPLE / 2, output);
        
        fill_bars(magnitudes, bars, NUM_BARS, bar_start_bin, &config);
        normalize_bars(bars, NUM_BARS);

        smoothen(prev_bars, bars, NUM_BARS, 0.85f);
       
        fill_ray_rects(rects, bars, NUM_BARS, &rconfig);

        apply_gravity(peak_bars, bars, NUM_BARS, 0.01f);

        BeginDrawing();

            ClearBackground(RAYWHITE);
            render_rects(rects, NUM_BARS, color_arr);

        EndDrawing();

        memcpy(prev_bars, bars, NUM_BARS * sizeof(float));    
    }
    
    CloseWindow();
    dinit_ma();
    free_cfg(&cfg); 
    
    return 0;
}
