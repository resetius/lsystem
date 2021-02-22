
/* Copyright (c) 2008-2021 Alexey Ozeritsky
 * All rights reserved.
 */

#include "turtle_scanner.h"
#include "turtle.h"
#include "lsystem.h"

#include <math.h>

int turtlewrap()
{
    return 1;
}

struct String {
    char* r;
    int size;
    int capacity;
};

static void string_append(struct String* s, const char *str) {
    int len = strlen(str);
    while (s->capacity <= (s->size + len)) {
        s->capacity = (s->capacity+1)*2;
        s->r = realloc(s->r, s->capacity);
    }
    memcpy(&s->r[s->size], str, len);
    s->size += len;
    s->r[s->size] = 0;
}

static void string_append_char(struct String* s, char c) {
    if (s->size == s->capacity) {
        s->capacity = (s->capacity+1)*2;
        s->r = realloc(s->r, s->capacity);
    }
    s->r[s->size] = c;
    s->size += 1;
    s->r[s->size] = 0;
}

char* lsystem_iter(char* src, struct Group* gr)
{
    int result;
    struct String r;
    memset(&r, 0, sizeof(struct String));
    YY_BUFFER_STATE buf_state;

    buf_state = turtle_scan_string(&src[0]);
    while ((result = turtlelex()) != 0)
    {
        switch (result) {
        case '!': /*inverse +/-*/
        case '+':
        case '-':
        case '[':
        case ']':
            string_append_char(&r, (char)result);
            break;
        case INCNUMBER:
        case INCCOLOR:
        case COLOR:
        case NUMBER:
            string_append(&r, st.str); 
            free(st.str);
            break;
        default: {
            const char* val = group_get_var(gr, result);
            if (val) {
                string_append(&r, val);
            } else {
//				cerr << "not replaced " << (char)result << "\n";
                string_append_char(&r, (char)result);
            }
            break;
        }
        }
    }

    turtle_delete_buffer(buf_state);

    return r.r;
}

char* lsystem(struct Group* gr, int level) {
    char* W = strdup(group_get_axiom(gr));
    char* Next;

    for (int i = 0; i < level; ++i) {
        Next = lsystem_iter(W, gr);
        free(W);
        W = Next;
    }

    return W;
}

struct Context {
    double a;
    double x0;
    double y0;
    double r;
    double sgn;
    int col;
};

struct Context ctx(double alpha, double x, double y) {
    struct Context c;
    c.a = alpha;
    c.x0 = x;
    c.y0 = y;
    c.r = 1.0;
    c.sgn = 1.0;
    c.col = 0;
    return c;
}

struct Line* turtle(struct Group* p, const char* src)
{
    double inc;
    struct Line* head = NULL;
    struct Line* tail = NULL;
    struct Context* stk = NULL;
    int stk_pos = 0;
    int stk_capacity = 0;
    struct Context c = ctx(group_get_angle_init(p), 0, 0);
    int col = 0;
    double theta = group_get_angle(p);

    int result;
    YY_BUFFER_STATE buf_state;

    buf_state = turtle_scan_string(&src[0]);

    while ((result = turtlelex()) != 0)
    {
        switch (result) {
        case '+': c.a += c.sgn * theta; break;
        case '-': c.a -= c.sgn * theta; break;
            /*пропуск*/
        case 'G':
        case 'M':
            c.x0 += c.r * cos(c.a); c.y0 += c.r * sin(c.a);
            break;
            /*branch open*/
        case '[':
            //printf("branch [\n");
            if (stk_pos >= stk_capacity) {
                stk_capacity = (stk_capacity+1)*2;
                stk = realloc(stk, stk_capacity*sizeof(struct Context));
            }
            stk[stk_pos++] = c;
            break;
            /*branch close*/
        case ']':
            //printf("branch ]\n");
            c = stk[--stk_pos];
            break;
            /*forward*/
        case 'F':
        case 'D': {
            struct Line* l = calloc(1, sizeof(struct Line));
            //printf("draw\n");
            l->x0 = c.x0; l->y0 = c.y0;
            c.x0 += c.r * cos(c.a); c.y0 += c.r * sin(c.a);
            l->x1 = c.x0; l->y1 = c.y0;
            l->c  = c.col;
            if (head == NULL) {
                head = tail = l;
            } else {
                tail->next = l; tail = l;
            }
            break;
        }
        case '!':
            //printf("reverse sign\n");
            c.sgn = -c.sgn;
            break;
        case COLOR:
            c.col = st.i; free(st.str);
            break;
        case INCCOLOR:
            c.col = (256 + c.col + st.i) % 256;
            free(st.str);
            break;
        case NUMBER:
//			printf("mult r %lf\n", st.m);
            c.r *= st.m; free(st.str);
            break;
        case INCNUMBER:
            //printf("inc angle by %d\n", st.i);
            inc = c.sgn * (double)st.i * M_PI / 180.0;
            c.a += inc; 
            free(st.str);
            break;
        default:
            break;
        }
    }

    free(stk);
    turtle_delete_buffer(buf_state);

    return head;
}

