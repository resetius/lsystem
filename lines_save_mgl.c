
/* Copyright (c) 2008-2021 Alexey Ozeritskiy
 * All rights reserved.
 */

#include <stdio.h>
#include "lsystem.h"


void lines_save_mgl(
	struct Group* g, struct Line* lines,
	double min_x, double max_x, double min_y, double max_y)
{
	const char* name = group_get_name(g);
    char buf[1024];
    const char* fname = "output.mgl";
    int colors[256];

    if (*name) {
        snprintf(buf, sizeof(buf), "%s.mgl", name);
        fname = buf;
    }
    FILE * f = fopen(fname, "wb");

    if (!f) {
        fprintf(stderr, "cannot open file '%s'\n", fname);
        return;
    }

	fprintf(f, "axis %lf %lf %lf %lf\n", min_x, min_y, max_x, max_y);
	for (struct StringListItem* it = group_mgl_start(g); it != NULL; it=it->next)
	{
		fprintf(f, "%s\n", it->val);
	}

	for (struct Line* it = lines; it != NULL; it=it->next)
	{
		fprintf(f, "line %.16lf %.16lf %.16lf %.16lf\n",
		            it->x0, it->y0, it->x1, it->y1);
	}

	fclose(f);
}
