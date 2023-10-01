#pragma once

/* Copyright (c) 2008-2023 Alexey Ozeritskiy
 * All rights reserved.
 */


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

typedef void (*log_function_t)(void* user_data, const char* text);
struct Parser* parser_new(log_function_t log, void* log_user_data);
void parser_free(struct Parser* parser);
void parser_push(struct Parser* parser, const char* str);
void parser_set_axiom(struct Parser* parser, const char* str);
void parser_set_angle(struct Parser* parser, double a);
void parser_set_angle_init(struct Parser* parser, double a);
void parser_add_rule(struct Parser* parser, char k, const char* str);
void parser_set_order(struct Parser* parser, double n);
void parser_set_error(struct Parser* parser, const char* str, int lineno);
void parser_print(struct Parser* parser);
void parser_check(struct Parser* parser);
struct Group* parser_group_start(struct Parser* parser);
int parser_has_error(struct Parser* parser);
int parser_get_error_line(struct Parser* parser);

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
