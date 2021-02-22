#pragma once

/* Copyright (c) 2008-2021 Alexey Ozeritsky
 * All rights reserved.
 */

static unsigned char colormap_vga1[][3] = {
    {0, 0, 0},
    {0, 0, 168},
    {0, 168, 0},
    {0, 168, 168},
    {168, 0, 0},
    {168, 0, 168},
    {168, 84, 0},
    {168, 168, 168},
    {84, 84, 84},
    {84, 84, 252},
    {84, 252, 84},
    {84, 252, 252},
    {252, 84, 84},
    {252, 84, 252},
    {252, 252, 84},
    {252, 252, 252},
    {0, 0, 0},
    {20, 20, 20},
    {32, 32, 32},
    {44, 44, 44},
    {56, 56, 56},
    {68, 68, 68},
    {80, 80, 80},
    {96, 96, 96},
    {112, 112, 112},
    {128, 128, 128},
    {144, 144, 144},
    {160, 160, 160},
    {180, 180, 180},
    {200, 200, 200},
    {224, 224, 224},
    {252, 252, 252},
    {0, 0, 252},
    {64, 0, 252},
    {124, 0, 252},
    {188, 0, 252},
    {252, 0, 252},
    {252, 0, 188},
    {252, 0, 124},
    {252, 0, 64},
    {252, 0, 0},
    {252, 64, 0},
    {252, 124, 0},
    {252, 188, 0},
    {252, 252, 0},
    {188, 252, 0},
    {124, 252, 0},
    {64, 252, 0},
    {0, 252, 0},
    {0, 252, 64},
    {0, 252, 124},
    {0, 252, 188},
    {0, 252, 252},
    {0, 188, 252},
    {0, 124, 252},
    {0, 64, 252},
    {124, 124, 252},
    {156, 124, 252},
    {188, 124, 252},
    {220, 124, 252},
    {252, 124, 252},
    {252, 124, 220},
    {252, 124, 188},
    {252, 124, 156},
    {252, 124, 124},
    {252, 156, 124},
    {252, 188, 124},
    {252, 220, 124},
    {252, 252, 124},
    {220, 252, 124},
    {188, 252, 124},
    {156, 252, 124},
    {124, 252, 124},
    {124, 252, 156},
    {124, 252, 188},
    {124, 252, 220},
    {124, 252, 252},
    {124, 220, 252},
    {124, 188, 252},
    {124, 156, 252},
    {180, 180, 252},
    {196, 180, 252},
    {216, 180, 252},
    {232, 180, 252},
    {252, 180, 252},
    {252, 180, 232},
    {252, 180, 216},
    {252, 180, 196},
    {252, 180, 180},
    {252, 196, 180},
    {252, 216, 180},
    {252, 232, 180},
    {252, 252, 180},
    {232, 252, 180},
    {216, 252, 180},
    {196, 252, 180},
    {180, 252, 180},
    {180, 252, 196},
    {180, 252, 216},
    {180, 252, 232},
    {180, 252, 252},
    {180, 232, 252},
    {180, 216, 252},
    {180, 196, 252},
    {0, 0, 112},
    {28, 0, 112},
    {56, 0, 112},
    {84, 0, 112},
    {112, 0, 112},
    {112, 0, 84},
    {112, 0, 56},
    {112, 0, 28},
    {112, 0, 0},
    {112, 28, 0},
    {112, 56, 0},
    {112, 84, 0},
    {112, 112, 0},
    {84, 112, 0},
    {56, 112, 0},
    {28, 112, 0},
    {0, 112, 0},
    {0, 112, 28},
    {0, 112, 56},
    {0, 112, 84},
    {0, 112, 112},
    {0, 84, 112},
    {0, 56, 112},
    {0, 28, 112},
    {56, 56, 112},
    {68, 56, 112},
    {84, 56, 112},
    {96, 56, 112},
    {112, 56, 112},
    {112, 56, 96},
    {112, 56, 84},
    {112, 56, 68},
    {112, 56, 56},
    {112, 68, 56},
    {112, 84, 56},
    {112, 96, 56},
    {112, 112, 56},
    {96, 112, 56},
    {84, 112, 56},
    {68, 112, 56},
    {56, 112, 56},
    {56, 112, 68},
    {56, 112, 84},
    {56, 112, 96},
    {56, 112, 112},
    {56, 96, 112},
    {56, 84, 112},
    {56, 68, 112},
    {80, 80, 112},
    {88, 80, 112},
    {96, 80, 112},
    {104, 80, 112},
    {112, 80, 112},
    {112, 80, 104},
    {112, 80, 96},
    {112, 80, 88},
    {112, 80, 80},
    {112, 88, 80},
    {112, 96, 80},
    {112, 104, 80},
    {112, 112, 80},
    {104, 112, 80},
    {96, 112, 80},
    {88, 112, 80},
    {80, 112, 80},
    {80, 112, 88},
    {80, 112, 96},
    {80, 112, 104},
    {80, 112, 112},
    {80, 104, 112},
    {80, 96, 112},
    {80, 88, 112},
    {0, 0, 64},
    {16, 0, 64},
    {32, 0, 64},
    {48, 0, 64},
    {64, 0, 64},
    {64, 0, 48},
    {64, 0, 32},
    {64, 0, 16},
    {64, 0, 0},
    {64, 16, 0},
    {64, 32, 0},
    {64, 48, 0},
    {64, 64, 0},
    {48, 64, 0},
    {32, 64, 0},
    {16, 64, 0},
    {0, 64, 0},
    {0, 64, 16},
    {0, 64, 32},
    {0, 64, 48},
    {0, 64, 64},
    {0, 48, 64},
    {0, 32, 64},
    {0, 16, 64},
    {32, 32, 64},
    {40, 32, 64},
    {48, 32, 64},
    {56, 32, 64},
    {64, 32, 64},
    {64, 32, 56},
    {64, 32, 48},
    {64, 32, 40},
    {64, 32, 32},
    {64, 40, 32},
    {64, 48, 32},
    {64, 56, 32},
    {64, 64, 32},
    {56, 64, 32},
    {48, 64, 32},
    {40, 64, 32},
    {32, 64, 32},
    {32, 64, 40},
    {32, 64, 48},
    {32, 64, 56},
    {32, 64, 64},
    {32, 56, 64},
    {32, 48, 64},
    {32, 40, 64},
    {44, 44, 64},
    {48, 44, 64},
    {52, 44, 64},
    {60, 44, 64},
    {64, 44, 64},
    {64, 44, 60},
    {64, 44, 52},
    {64, 44, 48},
    {64, 44, 44},
    {64, 48, 44},
    {64, 52, 44},
    {64, 60, 44},
    {64, 64, 44},
    {60, 64, 44},
    {52, 64, 44},
    {48, 64, 44},
    {44, 64, 44},
    {44, 64, 48},
    {44, 64, 52},
    {44, 64, 60},
    {44, 64, 64},
    {44, 60, 64},
    {44, 52, 64},
    {44, 48, 64},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
};

//256 colors
static unsigned char colormap_vga2[][3] = {
    {252, 252, 252},
    {0, 168, 0},
    {0, 168, 168},
    {168, 0, 0},
    {168, 0, 168},
    {168, 84, 0},
    {168, 168, 168},
    {84, 84, 84},
    {84, 84, 252},
    {84, 252, 84},
    {84, 252, 252},
    {252, 84, 84},
    {252, 84, 252},
    {252, 252, 84},
    {252, 252, 252},
    {0, 0, 0},
    {20, 20, 20},
    {32, 32, 32},
    {44, 44, 44},
    {56, 56, 56},
    {68, 68, 68},
    {80, 80, 80},
    {96, 96, 96},
    {112, 112, 112},
    {128, 128, 128},
    {144, 144, 144},
    {160, 160, 160},
    {180, 180, 180},
    {200, 200, 200},
    {224, 224, 224},
    {252, 252, 252},
    {0, 0, 252},
    {64, 0, 252},
    {124, 0, 252},
    {188, 0, 252},
    {252, 0, 252},
    {252, 0, 188},
    {252, 0, 124},
    {252, 0, 64},
    {252, 0, 0},
    {252, 64, 0},
    {252, 124, 0},
    {252, 188, 0},
    {252, 252, 0},
    {188, 252, 0},
    {124, 252, 0},
    {64, 252, 0},
    {0, 252, 0},
    {0, 252, 64},
    {0, 252, 124},
    {0, 252, 188},
    {0, 252, 252},
    {0, 188, 252},
    {0, 124, 252},
    {0, 64, 252},
    {124, 124, 252},
    {156, 124, 252},
    {188, 124, 252},
    {220, 124, 252},
    {252, 124, 252},
    {252, 124, 220},
    {252, 124, 188},
    {252, 124, 156},
    {252, 124, 124},
    {252, 156, 124},
    {252, 188, 124},
    {252, 220, 124},
    {252, 252, 124},
    {220, 252, 124},
    {188, 252, 124},
    {156, 252, 124},
    {124, 252, 124},
    {124, 252, 156},
    {124, 252, 188},
    {124, 252, 220},
    {124, 252, 252},
    {124, 220, 252},
    {124, 188, 252},
    {124, 156, 252},
    {180, 180, 252},
    {196, 180, 252},
    {216, 180, 252},
    {232, 180, 252},
    {252, 180, 252},
    {252, 180, 232},
    {252, 180, 216},
    {252, 180, 196},
    {252, 180, 180},
    {252, 196, 180},
    {252, 216, 180},
    {252, 232, 180},
    {252, 252, 180},
    {232, 252, 180},
    {216, 252, 180},
    {196, 252, 180},
    {180, 252, 180},
    {180, 252, 196},
    {180, 252, 216},
    {180, 252, 232},
    {180, 252, 252},
    {180, 232, 252},
    {180, 216, 252},
    {180, 196, 252},
    {0, 0, 112},
    {28, 0, 112},
    {56, 0, 112},
    {84, 0, 112},
    {112, 0, 112},
    {112, 0, 84},
    {112, 0, 56},
    {112, 0, 28},
    {112, 0, 0},
    {112, 28, 0},
    {112, 56, 0},
    {112, 84, 0},
    {112, 112, 0},
    {84, 112, 0},
    {56, 112, 0},
    {28, 112, 0},
    {0, 112, 0},
    {0, 112, 28},
    {0, 112, 56},
    {0, 112, 84},
    {0, 112, 112},
    {0, 84, 112},
    {0, 56, 112},
    {0, 28, 112},
    {56, 56, 112},
    {68, 56, 112},
    {84, 56, 112},
    {96, 56, 112},
    {112, 56, 112},
    {112, 56, 96},
    {112, 56, 84},
    {112, 56, 68},
    {112, 56, 56},
    {112, 68, 56},
    {112, 84, 56},
    {112, 96, 56},
    {112, 112, 56},
    {96, 112, 56},
    {84, 112, 56},
    {68, 112, 56},
    {56, 112, 56},
    {56, 112, 68},
    {56, 112, 84},
    {56, 112, 96},
    {56, 112, 112},
    {56, 96, 112},
    {56, 84, 112},
    {56, 68, 112},
    {80, 80, 112},
    {88, 80, 112},
    {96, 80, 112},
    {104, 80, 112},
    {112, 80, 112},
    {112, 80, 104},
    {112, 80, 96},
    {112, 80, 88},
    {112, 80, 80},
    {112, 88, 80},
    {112, 96, 80},
    {112, 104, 80},
    {112, 112, 80},
    {104, 112, 80},
    {96, 112, 80},
    {88, 112, 80},
    {80, 112, 80},
    {80, 112, 88},
    {80, 112, 96},
    {80, 112, 104},
    {80, 112, 112},
    {80, 104, 112},
    {80, 96, 112},
    {80, 88, 112},
    {0, 0, 64},
    {16, 0, 64},
    {32, 0, 64},
    {48, 0, 64},
    {64, 0, 64},
    {64, 0, 48},
    {64, 0, 32},
    {64, 0, 16},
    {64, 0, 0},
    {64, 16, 0},
    {64, 32, 0},
    {64, 48, 0},
    {64, 64, 0},
    {48, 64, 0},
    {32, 64, 0},
    {16, 64, 0},
    {0, 64, 0},
    {0, 64, 16},
    {0, 64, 32},
    {0, 64, 48},
    {0, 64, 64},
    {0, 48, 64},
    {0, 32, 64},
    {0, 16, 64},
    {32, 32, 64},
    {40, 32, 64},
    {48, 32, 64},
    {56, 32, 64},
    {64, 32, 64},
    {64, 32, 56},
    {64, 32, 48},
    {64, 32, 40},
    {64, 32, 32},
    {64, 40, 32},
    {64, 48, 32},
    {64, 56, 32},
    {64, 64, 32},
    {56, 64, 32},
    {48, 64, 32},
    {40, 64, 32},
    {32, 64, 32},
    {32, 64, 40},
    {32, 64, 48},
    {32, 64, 56},
    {32, 64, 64},
    {32, 56, 64},
    {32, 48, 64},
    {32, 40, 64},
    {44, 44, 64},
    {48, 44, 64},
    {52, 44, 64},
    {60, 44, 64},
    {64, 44, 64},
    {64, 44, 60},
    {64, 44, 52},
    {64, 44, 48},
    {64, 44, 44},
    {64, 48, 44},
    {64, 52, 44},
    {64, 60, 44},
    {64, 64, 44},
    {60, 64, 44},
    {52, 64, 44},
    {48, 64, 44},
    {44, 64, 44},
    {44, 64, 48},
    {44, 64, 52},
    {44, 64, 60},
    {44, 64, 64},
    {44, 60, 64},
    {44, 52, 64},
    {44, 48, 64},
    {252, 252, 252},
    {252, 252, 252},
    {252, 252, 252},
    {252, 252, 252},
    {252, 252, 252},
    {252, 252, 252},
    {252, 252, 252},
    {252, 252, 252},
    {0, 0, 168},
};
