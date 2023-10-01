%{
/* Copyright (c) 2008-2023 Alexey Ozeritskiy
 * All rights reserved.
 */
 
#include <math.h>
#include "turtle.h"

int isatty(int);

struct State st = {0, 0, 0};
%}
%option 8bit
%option header-file="turtle_scanner.h" prefix="turtle" case-insensitive
NUM [0-9]*\.?[0-9]+
INT [0-9]+
VAR [\.a-zA-Z]
%%
"f"|"d"   { /*forward*/ return 'F'; }
"g"|"m"   { /*skip*/    return 'G'; }
"!"       { /*inverse*/ return '!'; }
"+"       { /*inc angle*/ return '+'; }
"-"       { /*dec angle*/ return '-'; }
"("{INT}")" { /*delay expand*/ 
              sscanf(&yytext[1],"%d", &st.i);
              st.str = strdup(yytext);
              return DELAY;
          }
"["|"]"   { /*branch */   return yytext[0]; }
"C"{INT}  { /*color*/
              sscanf(&yytext[1],"%d", &st.i); 
              st.str = strdup(yytext);
              return COLOR; 
          }
"<"{INT}  { /*next color*/
              sscanf(&yytext[1],"%d", &st.i);
              st.str = strdup(yytext);
              return INCCOLOR;
          }
">"{INT}  { /*prev color */
              sscanf(&yytext[1],"%d", &st.i);
              st.i   = -st.i;
              st.str = strdup(yytext);
              return INCCOLOR;
          }
"|"       { /*inc 180 deg*/
                 st.i   = 180;
                 st.str = strdup("|");
                 return INCNUMBER;
          }
"\\"{INT} { /*inc INT deg */
                 sscanf(&yytext[1], "%d", &st.i);
                 st.str = strdup(yytext);
                 return INCNUMBER;
          }
"/"{INT}  { /*dec INT deg */
                 sscanf(&yytext[1], "%d", &st.i);
                 st.i   = -st.i;
                 st.str = strdup(yytext);
                 return INCNUMBER;
          }
"@"{NUM}  { /*len multiply*/ sscanf(&yytext[1], "%lf", &st.m); 
              st.str = strdup(yytext); return NUMBER; }
"@Q"{NUM} { /*square root*/ sscanf(&yytext[2],"%lf", &st.m); 
                 st.m   = sqrt(st.m);
                 st.str = strdup(yytext); 
                 BEGIN(INITIAL);
                 return NUMBER; 
          }
"@I"{NUM} { /*inverse*/ sscanf(&yytext[2],"%lf", &st.m); 
                 st.m   = 1.0 / st.m;
                 st.str = strdup(yytext);  
                 BEGIN(INITIAL);
                 return NUMBER;
          }
"@IQ"{NUM} { /*inverse*/ sscanf(&yytext[3],"%lf", &st.m); 
                 st.m   = 1.0 / sqrt(st.m);
                 st.str = strdup(yytext);  
                 BEGIN(INITIAL);
                 return NUMBER;
           }
"@QI"{NUM} { /*inverse*/ sscanf(&yytext[3],"%lf", &st.m); 
                 st.m   = 1.0 / sqrt(st.m);
                 st.str = strdup(yytext);  
                 BEGIN(INITIAL);
                 return NUMBER;
           }
{VAR} { /*replace*/ return yytext[0]; }
.|"\n"    {}
%%
/*
  The standard drawing commands are:
      F Draw forward
      G Move forward (without drawing)
      + Increase angle
      - Decrease angle
      | Try to turn 180 degrees. (If angle is odd, the turn
        will be the largest possible turn less than 180 degrees.)

 These commands increment angle by the user specified angle value. They should be used when possible because they are fast. If greater flexibility is needed, use the following commands which keep a completely separate angle pointer which is specified in degrees. 
      D   Draw forward
      M   Move forward
      \nn Increase angle nn degrees
      /nn Decrease angle nn degrees

  Color control:
      Cnn Select color nn
      < nn Increment color by nn
      > nn decrement color by nn

  Advanced commands:
      !     Reverse directions (Switch meanings of +, - and , /)
      @nnn  Multiply line segment size by nnn
            nnn may be a plain number, or may be preceded by
                I for inverse, or Q for square root.
                (e.g.  @IQ2 divides size by the square root of 2)
      [     Push.  Stores current angle and position on a stack
      ]     Pop.  Return to location of last push
*/
