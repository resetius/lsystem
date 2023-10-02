
/* Copyright (c) 2008-2021 Alexey Ozeritskiy
 * All rights reserved.
 */

#include <stdlib.h>
#include "lsystem.h"

void lines_normilize(struct Line* lines, int n, double* mnx, double* mxx, double* mny, double* mxy) {
    double max_x, min_x;
    double max_y, min_y;
    max_x = min_x = lines->x0;
    max_y = min_y = lines->y0;

    for (int i = 0; i < n; i ++)
    {
        struct Line* it = &lines[i];
        if (max_x < it->x0) max_x = it->x0;
        if (max_x < it->x1) max_x = it->x1;
        if (min_x > it->x0) min_x = it->x0;
        if (min_x > it->x1) min_x = it->x1;

        if (max_y < it->y0) max_y = it->y0;
        if (max_y < it->y1) max_y = it->y1;
        if (min_y > it->y0) min_y = it->y0;
        if (min_y > it->y1) min_y = it->y1;
    }

    double xx = 2.0 / (max_x - min_x);
    double yy = 2.0 / (max_y - min_y);
    double kk = xx > yy ? yy : xx; // min

    double x = lines->x0, y = lines->y0;
    *mnx = *mxx = (x - min_x) * yy - 1.0;
    *mny = *mxy = (y - min_y) * yy - 1.0;

    for (int i = 0; i < n; i ++)
    {
        struct Line* it = &lines[i];
        it->x0 = (it->x0 - min_x) * kk - 1.0;
        it->x1 = (it->x1 - min_x) * kk - 1.0;

        it->y0 = (it->y0 - min_y) * kk - 1.0;
        it->y1 = (it->y1 - min_y) * kk - 1.0;

        if (*mxx < it->x0) *mxx = it->x0;
        if (*mxx < it->x1) *mxx = it->x1;
        if (*mnx > it->x0) *mnx = it->x0;
        if (*mnx > it->x1) *mnx = it->x1;

        if (*mxy < it->y0) *mxy = it->y0;
        if (*mxy < it->y1) *mxy = it->y1;
        if (*mny > it->y0) *mny = it->y0;
        if (*mny > it->y1) *mny = it->y1;
    }
}
