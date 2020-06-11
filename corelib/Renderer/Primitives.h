/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "Color.h"
#include "../Math/Vector2.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct Rect {
    float x;
    float y;
    float w;
    float h;
} Rect;

typedef struct Circle {
    float x;
    float y;
    float radius;
} Circle;

/////////////////////////////////////////////////
// Drawing functions
////////////////////////////////////////////////

void Draw_Point(Vector2 pos, Color color);
void Draw_Line(Vector2 start, Vector2 end, Color color);
void Draw_Rect(Rect rect, Color color);
void Draw_FilledRect(Rect rect, Color color);
void Draw_Circle(Circle circle, Color color);
void Draw_FilledCircle(Circle circle, Color color);