#pragma once

/* Copyright (c) 2008-2021 Alexey Ozeritsky
 * All rights reserved.
 */

struct State {
	int s;
	double m;
	int i;
	char * str;
};

extern struct State st;

#define NUMBER 256 
#define COLOR 257  
#define INCNUMBER 258
#define INCCOLOR  259
