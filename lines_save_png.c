
/* Copyright (c) 2008-2021 Alexey Ozeritskiy
 * All rights reserved.
 */

#include <stdio.h>
#include <gd.h>
#include "lsystem.h"
#include "vga_palette.h"

static void init_color_map(int *colors, gdImagePtr im)
{
    for (int i = 0; i < 256; ++i) {
        colors[i] = gdImageColorAllocate(im,
                                         (vga_palette[i] >> 16) & 0xff,
                                         (vga_palette[i] >> 8) & 0xff,
                                         (vga_palette[i] >> 0) & 0xff);
    }
}

void lines_save_png(
    const char* name, struct Line* lines, int n,
    double min_x, double max_x, double min_y, double max_y, int w, int h)
{
    char buf[1024];
    const char* fname = "output.png";
    int colors[256];

    if (*name) {
        snprintf(buf, sizeof(buf), "%s.png", name);
        fname = buf;
    }
    FILE * f = fopen(fname, "wb");

    if (!f) {
        fprintf(stderr, "cannot open file '%s'\n", fname);
        return;
    }

    gdImagePtr im;
    im    = gdImageCreate(w, h);
    int trans = gdImageColorAllocate(im, 0, 0, 0);

    init_color_map(colors, im);

    gdImageFill(im, w - 1, h - 1, trans);
    gdImageColorTransparent(im, trans);

    double xx = (w - 2) / (max_x - min_x);
    double yy = (h - 2) / (max_y - min_y);
    double kk = xx < yy ? xx : yy;

    for (int i = 0; i < n; i ++)
    {
        struct Line* it = &lines[i];
        int x0 = (int)(1 + (it->x0 - min_x) * kk);
        int y0 = (int)(1 + (it->y0 - min_y) * kk); y0 = h - y0 - 1;
        int x1 = (int)(1 + (it->x1 - min_x) * kk);
        int y1 = (int)(1 + (it->y1 - min_y) * kk); y1 = h - y1 - 1;
        gdImageLine(im, x0, y0, x1, y1, colors[it->c]);
    }

    gdImagePng(im, f);
    fclose(f);
    gdImageDestroy(im);
}
