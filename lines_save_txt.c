
/* Copyright (c) 2008-2021 Alexey Ozeritskiy
 * All rights reserved.
 */

#include <stdio.h>
#include "lsystem.h"

void lines_save_txt(
    const char* name, struct Line* lines, int n,
    double min_x, double max_x, double min_y, double max_y)
{
    char buf[1024];
    const char* fname = "output.txt";
    int colors[256];

    if (*name) {
        snprintf(buf, sizeof(buf), "%s.txt", name);
        fname = buf;
    }
    FILE * f = fopen(fname, "wb");

    if (!f) {
        fprintf(stderr, "cannot open file '%s'\n", fname);
        return;
    }

    for (int i = 0; i < n; i ++)
    {
        struct Line* it = &lines[i];
        fprintf(f, "{%.16lf, %.16lf}-{%.16lf, %.16lf} %d\n",
                    it->x0, it->y0, it->x1, it->y1, it->c);
    }

    fclose(f);
}

