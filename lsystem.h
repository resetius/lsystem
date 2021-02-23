#pragma once

/* Copyright (c) 2008-2021 Alexey Ozeritskiy
 * All rights reserved.
 */


struct StringListItem {
    char* val;
    struct StringListItem* next;
};

struct StringList {
    struct StringListItem* head;
    struct StringListItem* tail;
};

struct Group;

int group_check(struct Group* g);
double group_get_angle(struct Group* g);
double group_get_angle_init(struct Group* g);
const char* group_get_axiom(struct Group* g);
const char* group_get_var(struct Group* g, int key);
const char* group_get_name(struct Group* g);
int group_get_order(struct Group* g);
struct Group* group_next(struct Group* g);
struct StringListItem* group_mgl_start(struct Group* g);

struct Parser;

struct Parser* parser_new();
void parser_free(struct Parser* parser);
void parser_push(struct Parser* parser, const char* str);
void parser_push_mgl(struct Parser* parser, const char* str);
void parser_set_axiom(struct Parser* parser, const char* str);
void parser_set_angle(struct Parser* parser, double a);
void parser_set_angle_init(struct Parser* parser, double a);
void parser_add_rule(struct Parser* parser, char k, const char* str);
void parser_set_order(struct Parser* parser, double n);
void parser_set_error(struct Parser* parser, const char* str);
void parser_add_mgl(struct Parser* parser, const char* str);
void parser_print(struct Parser* parser);
void parser_check(struct Parser* parser);
struct Group* parser_group_start(struct Parser* parser);
int parser_has_error(struct Parser* parser);
void parser_print_error(struct Parser* parser);

int yyparse(struct Parser * );

char* lsystem(struct Group* gr, int level);

struct Line {
    double x0;
    double y0;
    double x1;
    double y1;
    int c;
    struct Line* next;
};

struct Line* turtle(struct Group* p, const char* W);

void lines_normilize(struct Line* lines, double* mnx, double* mxx, double* mny, double* mxy);
void lines_save_png(
	const char* name, struct Line* lines, 
	double min_x, double max_x, double min_y, double max_y, int w, int h);
void lines_save_txt(
    const char* name, struct Line* lines,
    double min_x, double max_x, double min_y, double max_y);
void lines_save_mgl(
	struct Group* g, struct Line* lines,
	double min_x, double max_x, double min_y, double max_y);
