/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "Primitives.h"
#include "../Math/Vector2.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Camera
////////////////////////////////////////////////

void Camera_Move(Vector2 pos);
//void Camera_CenterOn(GameObject *obj);
void Camera_SetPosition(Vector2 pos);
void Camera_SetBounds(Rect rect);
Vector2 Camera_GetPosition();
Rect Camera_GetBounds();