#pragma once

/* Copyright (c) 2008-2023 Alexey Ozeritskiy
 * All rights reserved.
 */

struct State {
    double m;
    int i;
    const char * str;
};

#define NUMBER 256 
#define COLOR 257  
#define INCNUMBER 258
#define INCCOLOR  259
#define DELAY 260
#define YY_DECL int turtlelex(struct State* st)

YY_DECL;
