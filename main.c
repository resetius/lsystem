/* Copyright (c) 2008-2021 Alexey Ozeritskiy
 * All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include "lsystem.h"
#include "lsystem_scanner.h"
#include "lsystem_parser.h"

void usage(const char * n)
{
    printf("usage:\n");
    printf("%s [-f filename] [-t type] [-l order] [-w width] [-h height] \n", n);
    printf("-f -- read lsystem from file (stdin - default)\n");
    printf("-t -- points save type: \n");
    printf("\t\t mgl -- MathGL script\n");
    printf("\t\t png -- PNG\n");
    printf("\t\t txt -- txt\n");
    printf("-l -- default order \n");
    exit(0);
}

static void log_function(void* unused, const char* text) {
    fprintf(stderr, "%s", text);
}

int main(int argc, char** argv) {
    struct Parser* p = parser_new(log_function, NULL);
    struct Group* g = NULL;
    FILE * f  = 0;
    int level = 0;
    int type  = 2;

    int w = 1024;
    int h = 1024;

    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-f") && i < argc - 1) {
            f = fopen(argv[i + 1], "r");
        } else if (!strcmp(argv[i], "-l") && i < argc - 1) {
            level = atoi(argv[i + 1]);
        } else if (!strcmp(argv[i], "-w") && i < argc - 1) {
            w = atoi(argv[i+1]);
        } else if (!strcmp(argv[i], "-h") && i < argc - 1) {
            h = atoi(argv[i+1]);
        } else if (!strcmp(argv[i], "-t") && i < argc - 1) {
            if (!strcmp(argv[i + 1], "txt")) {
                type = 0;
            } else if (!strcmp(argv[i + 1], "mgl")) {
                type = 1;
            } else if (!strcmp(argv[i + 1], "png")) {
                type = 2;
            }
        } else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            usage(argv[0]);
        }
    }

    if (f) yyrestart(f);

    while (yyparse(p) && !parser_has_error(p));

    if (parser_has_error(p)) {
        parser_free(p);
        return -1;
    }

    for (g = parser_group_start(p); g != NULL; g = group_next(g))
    {
        double min_x, max_x, min_y, max_y;
        int l;
        char* W;
        struct Line* lines;

        if (!group_check(g)) continue;

        l = level;
        if (group_get_order(g) != 0 && level == 0) l = group_get_order(g);

        fprintf(stderr, "building %s\n", group_get_name(g));
        fprintf(stderr, "  using order %d\n", l);

        W = lsystem(g, l);
        fprintf(stderr, "  lsystem done\n");
        //fprintf(stderr, " '%s'\n", W);
        lines = turtle(g, W); 
        free(W);
        if (lines == NULL) {
            continue;
        }
        fprintf(stderr, "  turtle done\n");
        lines_normilize(lines, &min_x, &max_x, &min_y, &max_y);
        fprintf(stderr, "  normilize done\n");
        switch (type) {
        case 0:
            lines_save_txt(group_get_name(g), lines, min_x, max_x, min_y, max_y);
            break;
        case 1:
            lines_save_mgl(g, lines, min_x, max_x, min_y, max_y);
            break;
        case 2:
            lines_save_png(group_get_name(g), lines, min_x, max_x, min_y, max_y, w, h);
            break;
        default:
            fprintf(stderr, "Unknown save type: %d\n", type);
            return -1;
            break;
        }
        fprintf(stderr, "  saving done\n");
    }

    parser_free(p);

    if (f) fclose(f);

    return 0;
}