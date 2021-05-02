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

/////////////////////////////////////////////////
// Collisions
////////////////////////////////////////////////

DE_API bool DE_CollisionVecVec(vec2 v1, vec2 v2);
DE_API bool DE_CollisionRectRect(vec4 r1, vec4 r2);
DE_API bool DE_CollisionCircleCircle(vec3 c1, vec3 c2);
DE_API bool DE_CollisionVecRect(vec2 vec, vec4 rect);
DE_API bool DE_CollisionCircleVec(vec3 circle, vec2 vec);
DE_API bool DE_CollisionRectCircle(vec4 rect, vec3 circle);
