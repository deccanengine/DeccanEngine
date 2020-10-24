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

void DE_DrawPoint(vec2 pos, DeccanColor color);
void DE_DrawLine(vec2 start, vec2 end, DeccanColor color);
void DE_DrawRect(vec4 rect, DeccanColor color);
void DE_DrawFilledRect(vec4 rect, DeccanColor color);
void DE_DrawCircle(vec3 circle, DeccanColor color);
void DE_DrawFilledCircle(vec3 circle, DeccanColor color);
