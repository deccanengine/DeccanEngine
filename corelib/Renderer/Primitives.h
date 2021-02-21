/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
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

DE_API void DE_DrawPoint(vec2 pos, DeccanColor color);
DE_API void DE_DrawLine(vec2 start, vec2 end, DeccanColor color);
DE_API void DE_DrawRect(vec4 rect, DeccanColor color);
DE_API void DE_DrawFilledRect(vec4 rect, DeccanColor color);
DE_API void DE_DrawCircle(vec3 circle, DeccanColor color);
DE_API void DE_DrawFilledCircle(vec3 circle, DeccanColor color);
