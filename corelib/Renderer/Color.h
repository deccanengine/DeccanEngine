/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
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

typedef struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;

static Color
    ColorList_Blank     = {  0,   0,   0,   0},
    ColorList_White     = {255, 255, 255, 255}, 
    ColorList_Black     = {  0,   0,   0, 255},
    ColorList_Grey      = {192, 192, 192, 255}, 
    ColorList_DarkGrey  = {128, 128, 128, 255},
	ColorList_Red       = {255,   0,   0, 255}, 
    ColorList_DarkRed   = {128,   0,   0, 255},
    ColorList_Green     = {  0, 255,   0, 255}, 
    ColorList_DarkGreen = {  0, 128,   0, 255},
    ColorList_Blue      = {  0,   0, 255, 255}, 
    ColorList_DarkBlue  = {  0,   0, 128, 255},
    ColorList_Yellow    = {255, 255,   0, 255}, 
    ColorList_Cyan      = {  0, 255, 255, 255}, 
    ColorList_Magenta   = {255,   0, 255, 255}, 
    ColorList_Orange    = {255, 165,   0, 255}, 
    ColorList_Violet    = {238, 130, 238, 255}, 
    ColorList_Fuchsia   = {255,   0, 255, 255};
