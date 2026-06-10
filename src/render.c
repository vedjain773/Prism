#include "render.h"

void set_render_cfg(size_t num_bars, int width, int height, int gap_width, render_cfg* cfg)
{
    cfg->num_bars = num_bars;
    cfg->width = width;
    cfg->height = height;
    cfg->gap_width = gap_width;
    cfg->color_start = ORANGE;
    cfg->color_end = ORANGE;
}

void set_color(Color color_start, Color color_end, render_cfg* cfg)
{
    cfg->color_start = color_start;
    cfg->color_end = color_end;
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

void render_rects(Rectangle* rects, size_t num_bars, Color* color_arr)
{
    for (size_t i = 0; i < num_bars; i++)
    {
        DrawRectangleRec(rects[i], color_arr[i]);
    }
}

void set_color_arr(Color* color_arr, size_t num_bars, render_cfg* cfg)
{
    float step_r = (float)(cfg->color_end.r - cfg->color_start.r) / (float) num_bars;
    float step_g = (float)(cfg->color_end.g - cfg->color_start.g) / (float) num_bars;
    float step_b = (float)(cfg->color_end.b - cfg->color_start.b) / (float) num_bars;

    for (size_t i = 0; i < num_bars; i++)
    {
        color_arr[i].r = (int)(cfg->color_start.r + i * step_r);
        color_arr[i].g = (int)(cfg->color_start.g + i * step_g);
        color_arr[i].b = (int)(cfg->color_start.b + i * step_b);
        color_arr[i].a = 255;
    }
}
