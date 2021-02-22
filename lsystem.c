/* Copyright (c) 2008-2021 Alexey Ozeritskiy
 * All rights reserved.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lsystem.h"

struct Group
{
    // {
    struct Group* next;
    double alpha;
    double theta;
    char* axiom;
    char* r[256];
    char* name;
    int order;
    // }

    int error;
    int v[256];

    struct StringList mgl;
};

struct Group* group_new() {
    struct Group* g = calloc(1, sizeof(struct Group));
    return g;
}

static void string_list_destroy(struct StringList lst) {
    struct StringListItem* cur = lst.head;
    struct StringListItem* next;

    while (cur != NULL) {
        next = cur->next;
        free(cur->val);
        free(cur);
        cur = next;
    }
}

void group_free(struct Group* g) {
    if (g) {
        int i;
        free(g->axiom);
        for (i = 0; i < 256; i=i+1) {
            free(g->r[i]);
        }
        string_list_destroy(g->mgl);
        free(g->name);
        free(g);
    }
}

void group_add_mgl(struct Group* g, const char* str) {
    struct StringListItem* item = calloc(1, sizeof(struct StringListItem));
    item->val = strdup(str);
    if (g->mgl.tail == NULL) {
        g->mgl.tail = g->mgl.head = item;
    } else {
        g->mgl.tail->next = item;
        g->mgl.tail = item;
    }
}

void group_set_axiom(struct Group* g, const char* p) {
    g->axiom = strdup(p);
    while (*p) {
        if (*p != '[' && *p != ']' && *p != '+' && *p != '-') {
            g->v[*p] = 1;
        }
        p=p+1;
    }
}

void group_set_order(struct Group* g, double order) {
    g->order = (int)order;
}

int group_check(struct Group* g) {
    if (g->axiom == NULL || !*g->axiom) {
        fprintf(stderr, "fail on axiom\n");
        g->error = 1;
    }

    if (g->theta == 0) {
        fprintf(stderr, "fail on theta\n");
        g->error = 1;
    }
    return g->error == 0;
}

void group_print(struct Group* g) {
    int i;
    fprintf(stderr, "error : %d\n", g->error);
    fprintf(stderr, "alpha : %lf\n", g->alpha);
    fprintf(stderr, "theta : %lf\n", g->theta);
    fprintf(stderr, "axiom : %s\n", g->axiom);

    for (i = 0; i < 255; i=i+1) {
        if (g->r[i]) {
            fprintf(stderr, "%c : %s\n", i, g->r[i]);
        }
    }
}

double group_get_angle(struct Group* g) {
    return g->theta;
}

double group_get_angle_init(struct Group* g) {
    return g->alpha;
}

const char* group_get_axiom(struct Group* g) {
    return g->axiom;
}

const char* group_get_var(struct Group* g, int key) {
    return g->r[key];
}

const char* group_get_name(struct Group* g) {
    return g->name;
}

int group_get_order(struct Group* g) {
    return g->order;
}

struct Group* group_next(struct Group* g) {
    return g->next;
}


struct StringListItem* group_mgl_start(struct Group* g) {
    return g->mgl.head;
}

struct Parser {
    int error;
    char* error_str;
    struct Group* head;
    struct Group* tail;
    struct Group* last;

    struct StringList mgl;
};

struct Parser* parser_new() {
    struct Parser* p = calloc(1, sizeof(struct Parser));
    p->tail = p->head = NULL;
    p->last = group_new();
    return p;
}

void parser_free(struct Parser* p) {
    if (p) {
        struct Group* cur;
        struct Group* next;
        free(p->error_str);
        cur = p->head;
        while (cur != NULL) {
            next = cur->next;
            group_free(cur);
            cur = next;
        }
        string_list_destroy(p->mgl);
        group_free(p->last);
        free(p);
    }
}

void parser_push(struct Parser* p, const char* str) {
    p->last->name = strdup(str);
    if (p->mgl.head != NULL) {
        p->mgl.tail = p->last->mgl.head;
        p->last->mgl = p->mgl;
        p->mgl.head = p->mgl.tail = NULL;
    }

    if (p->head == NULL) {
        p->head = p->tail = p->last;
    } else {
        p->tail->next = p->last;
        p->tail = p->last;
    }

    p->last = group_new();
}

void parser_push_mgl(struct Parser* p, const char* str) {
    struct StringListItem * item = calloc(1, sizeof(struct StringListItem));
    item->val = strdup(str);
    if (p->mgl.head == NULL) {
        p->mgl.head = p->mgl.tail = item;
    } else {
        p->mgl.tail->next = item;
        p->mgl.tail = item;
    }
}

void parser_set_axiom(struct Parser* p, const char* str) {
    group_set_axiom(p->last, str);
}

void parser_set_angle(struct Parser* p, double a) {
    p->last->theta = a;
}

void parser_set_angle_init(struct Parser* p, double a) {
    p->last->alpha = a;
}

void parser_set_var(struct Parser* p, char k, const char* str) {
    free(p->last->r[k]);
    p->last->r[k] = strdup(str);
}

void parser_set_order(struct Parser* p, double n) {
    group_set_order(p->last, n);
}

void parser_set_error(struct Parser* p, const char* str) {
    p->error = 1;
    p->error_str = strdup(str);
    if (p->last) {
        p->last->error = 1;
    }
}

void parser_add_mgl(struct Parser* p, const char* str) {
    group_add_mgl(p->last, str);
}

void parser_print(struct Parser* p) {
    struct Group* cur;
    for (cur = p->head; cur != NULL; cur = cur->next) {
        group_print(cur);
    }
}

void parser_check(struct Parser* p) {
    struct Group* cur;
    for (cur = p->head; cur != NULL; cur = cur->next) {
        group_check((struct Group*)cur);
    }
}

struct Group* parser_group_start(struct Parser* p) {
    return (struct Group*)p->head;
}

int parser_has_error(struct Parser* p) {
    return p->error != 0;
}

void parser_print_error(struct Parser* p) {
    if (p->error_str) {
        fprintf(stderr, "Parser error: '%s'\n", p->error_str);
    }
}
