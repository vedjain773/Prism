#ifndef RENDER_H
#define RENDER_H

#include "raylib.h"
#include <stddef.h>

typedef struct {
    size_t num_bars;
    int width;
    int height;
    int gap_width;
} render_cfg;

void set_render_cfg(size_t num_bars, int width, int height, int gap_width, render_cfg* cfg);

void fill_ray_rects(Rectangle* rects, float* bars, size_t size, render_cfg* cfg);
void render_rects(Rectangle* rects, size_t num_bars);

#endif
