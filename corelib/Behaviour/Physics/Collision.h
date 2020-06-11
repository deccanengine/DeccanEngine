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

bool Collision_VecVec(Vector2 v1, Vector2 v2);
bool Collision_RectRect(Rect r1, Rect r2);
bool Collision_CircleCircle(Circle c1, Circle c2);
bool Collision_VecRect(Vector2 vec, Rect rect);
bool Collision_CircleVec(Circle circle, Vector2 vec);
bool Collision_RectCircle(Rect rect, Circle circle);