/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../Config.h"
#include "../../Math/Vector2.h"
#include "../../Renderer/Primitives.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Collisions
////////////////////////////////////////////////

bool Collision_VecVec(Vector2f *v1, Vector2f *v2);
bool Collision_RectRect(PosRect *r1, PosRect *r2);
bool Collision_CircleCircle(Circle *c1, Circle *c2);
bool Collision_VecRect(Vector2f *vec, PosRect *rect);
bool Collision_CircleVec(Circle *circle, Vector2f *vec);
bool Collision_RectCircle(PosRect *rect, Circle *circle);