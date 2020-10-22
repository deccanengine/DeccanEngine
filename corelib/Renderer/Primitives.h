/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "Color.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Drawing functions
////////////////////////////////////////////////

void Draw_Point(vec2 pos, DeccanColor color);
void Draw_Line(vec2 start, vec2 end, DeccanColor color);
void Draw_Rect(vec4 rect, DeccanColor color);
void Draw_FilledRect(vec4 rect, DeccanColor color);
void Draw_Circle(vec3 circle, DeccanColor color);
void Draw_FilledCircle(vec3 circle, DeccanColor color);
