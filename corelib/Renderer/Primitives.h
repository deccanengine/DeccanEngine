/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "Color.h"
//#include "../Math/vec2.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

/*
typedef struct vec4 {
    float x;
    float y;
    float w;
    float h;
} vec4;

typedef struct vec3 {
    float x;
    float y;
    float radius;
} vec3;
*/

/////////////////////////////////////////////////
// Drawing functions
////////////////////////////////////////////////

void Draw_Point(vec2 pos, Color color);
void Draw_Line(vec2 start, vec2 end, Color color);
void Draw_Rect(vec4 rect, Color color);
void Draw_FilledRect(vec4 rect, Color color);
void Draw_Circle(vec3 circle, Color color);
void Draw_FilledCircle(vec3 circle, Color color);
