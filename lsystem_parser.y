%{

/* Copyright (c) 2008-2021 Alexey Ozeritskiy
 * All rights reserved.
 */
 
#include <stdio.h>
#include <math.h>
#include "lsystem_scanner.h"

#include "lsystem.h"

extern int yyerror(struct Parser * ptr, const char *s);
extern int yyget_lineno  (void);

%}
%union {
    double num;
    char* str;
}
%parse-param { struct Parser * ptr }
%token <str> VAR
%token <num> NUM
%token <str> TURTLE
%token <str> GRPIDT
%type  <num> number
%type  <str> turtle
%token AXIOM
%token THETA
%token ALPHA
%token ANGLE
%token ORDER
%right '='
%left '+' '-'
%left '*' '/'
%%

grp_list: grp
    | grp_list grp
    ;

grp: GRPIDT '{' list '}' { parser_push(ptr, $1); free($1); /* named group   */ }

list: '\n'
    | list '\n'
    | list expr '\n'
    ;

number: NUM { $$ = $1; }
    | number '/' number { $$ = $1 / $3; }
    | number '*' number { $$ = $1 * $3; }
    | number '+' number { $$ = $1 + $3; }
    | number '-' number { $$ = $1 - $3; }
    | '(' number ')'    { $$ = $2; }
    ;

turtle: { $$ = strdup(""); }
    | TURTLE { $$ = $1; }
    ;

expr: AXIOM  TURTLE { parser_set_axiom(ptr, $2); free($2); }
    | THETA  number { parser_set_angle(ptr, $2); }
    | ANGLE  number { parser_set_angle(ptr, M_PI * (360.0 / $2) / 180.0); }
    | ALPHA  number { parser_set_angle_init(ptr, $2); }
    | VAR   '=' turtle { parser_add_rule(ptr, $1[0], $3); free($1); free($3); }
    | ORDER  NUM    { parser_set_order(ptr, $2); }
    ;

%%
int yyerror(struct Parser * ptr, const char * s)
{
    char buf[1024];
    snprintf(buf, 1024, "syntax error near line %d", yyget_lineno()); 
    parser_set_error(ptr, buf, yyget_lineno());
    return 0;
}
