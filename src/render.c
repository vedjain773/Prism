#include "render.h"

void set_render_cfg(size_t num_bars, int width, int height, int gap_width, render_cfg* cfg)
{
    cfg->num_bars = num_bars;
    cfg->width = width;
    cfg->height = height;
    cfg->gap_width = gap_width;
}

void fill_ray_rects(Rectangle* rects, float* bars, size_t num_bars, render_cfg* cfg)
{
    const int gap = cfg->gap_width;
    const int width = (cfg->width - (num_bars + 1)) / num_bars;

    int start = gap;

    for (size_t i = 0; i < num_bars; i++)
    {
        rects[i].x = start;
        rects[i].y = 0;
        rects[i].width = width;
        rects[i].height = bars[i] * (cfg->height - 20);

        start += gap + width;
    }
}

void render_rects(Rectangle* rects, size_t num_bars)
{
    for (size_t i = 0; i < num_bars; i++)
    {
        DrawRectangleRec(rects[i], ORANGE);
    }
}
