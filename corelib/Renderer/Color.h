/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct DeccanColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} DeccanColor;

// TODO: Need a better solution to handle colours (or)
// do not provide these at all, as these should not be
// part of core, rather, it should be part of runtime.
#if 0

static Color
    ColorList_Blank     = (Color){  0,   0,   0,   0},
    ColorList_White     = (Color){255, 255, 255, 255},
    ColorList_Black     = (Color){  0,   0,   0, 255},
    ColorList_Grey      = (Color){192, 192, 192, 255},
    ColorList_DarkGrey  = (Color){128, 128, 128, 255},
	ColorList_Red       = (Color){255,   0,   0, 255},
    ColorList_DarkRed   = (Color){128,   0,   0, 255},
    ColorList_Green     = (Color){  0, 255,   0, 255},
    ColorList_DarkGreen = (Color){  0, 128,   0, 255},
    ColorList_Blue      = (Color){  0,   0, 255, 255},
    ColorList_DarkBlue  = (Color){  0,   0, 128, 255},
    ColorList_Yellow    = (Color){255, 255,   0, 255},
    ColorList_Cyan      = (Color){  0, 255, 255, 255},
    ColorList_Magenta   = (Color){255,   0, 255, 255},
    ColorList_Orange    = (Color){255, 165,   0, 255},
    ColorList_Violet    = (Color){238, 130, 238, 255},
    ColorList_Fuchsia   = (Color){255,   0, 255, 255};

#endif
