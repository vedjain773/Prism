#ifndef RENDER_H
#define RENDER_H

#include "raylib.h"
#include <stddef.h>

typedef struct {
    size_t num_bars;
    int width;
    int height;
    int gap_width;
    Color color_start;
    Color color_end;
} render_cfg;

void set_render_cfg(
        size_t num_bars,
        int width,
        int height,
        int gap_width,
        render_cfg* cfg);

void set_color(Color color_start, Color color_end, render_cfg* cfg);
void fill_ray_rects(Rectangle* rects, float* bars, size_t size, render_cfg* cfg);
void render_rects(Rectangle* rects, size_t num_bars, Color* color_arr);

void set_color_arr(Color* color_arr, size_t num_bars, render_cfg* cfg);

#endif
