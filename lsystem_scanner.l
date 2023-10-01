%{
/* Copyright (c) 2008-2021 Alexey Ozeritskiy
 * All rights reserved.
 */

#include <math.h>
#include <string.h>
#include <ctype.h>
#include "lsystem.h"
#include "lsystem_parser.h"

int isatty(int) ;
static int comment_caller;

static char * strdup_upper(const char * p)
{
    int l = strlen(p);
    char * r = (char*)malloc(l + 1);
    char *r1 = r; 
    while ((*r++ = toupper(*p++)));
    return r1;
}

%}
%option 8bit 
%option header-file="lsystem_scanner.h" case-insensitive
%s gen
%s grp
%s comment
%s mgl
%s order
AXIOM axiom
ALPHA alpha
ANGLE angle
THETA theta
PI pi
NUM [0-9]+\.?[0-9]*
VAR [a-zA-Z]
LS  [a-zA-Z\+\-\[\]!0-9@\.\|\<\>\\/:\(\)]+
IDT [a-zA-Z\.0-9&\*_@!\+\-]+
OP  [=/\*\+\-\(\)]
COMMENT ;.*\n?
WHITESPACE [ \t]
%%

<INITIAL,gen,grp>";" {
     /*  printf("begin comment %d\n", YY_START);*/
       comment_caller = YY_START;
       BEGIN(comment);
    }

<comment>[ \t]*"order"[\ t]+ {
                if (comment_caller != INITIAL) {
                    BEGIN(order);
                    return ORDER;
                }
             }
<order>[0-9]+ {
                  sscanf(yytext, "%lf", &yylval.num);
                  BEGIN(comment);
                  return NUM;
              }

<comment>"\n" { 
             BEGIN(comment_caller); 
             ++yylineno;
             if (comment_caller != INITIAL) {
                  return '\n'; 
             }
         }

<INITIAL>{IDT}  { 
                    yylval.str = strdup(yytext); 
                    return GRPIDT; 
                }
<grp>{NUM}   { sscanf(yytext, "%lf", &yylval.num);
               return NUM; 
             }
<gen>{LS}    {
               yylval.str = strdup_upper(yytext); 
               BEGIN(grp); return TURTLE; }
<INITIAL,grp,gen>"{" { 
                       BEGIN(grp);     return yytext[0]; }
<grp,gen>"}" {
                  BEGIN(INITIAL); return yytext[0]; }
<grp>{AXIOM} {
                  BEGIN(gen); return AXIOM; }
<grp>{ALPHA} { return ALPHA; }
<grp>{THETA} { return THETA; }
<grp>{ANGLE} { return ANGLE; }
<grp>{VAR}   { 
               yylval.str = strdup_upper(yytext);
               BEGIN(gen); return VAR; 
             }
<grp>{PI}    { yylval.num = M_PI; return NUM; }
<grp>{OP}    { return yytext[0]; }
<grp,gen>"=" { return yytext[0]; }
<grp,gen>"\n" { BEGIN(grp); ++yylineno; return '\n'; }
.       {}
"\n"    { ++yylineno; }
%%
/*
 подсказка:
 без указания группы действует во всех группах
<INITIAL> действует в первоначальной группе.
 */

int yywrap()
{
    return 1;
}

