/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "Primitives.h"
//#include "../Math/vec2.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Camera
////////////////////////////////////////////////

void Camera_Move(vec2 pos);
//void Camera_CenterOn(GameObject *obj);
void Camera_SetPosition(vec2 pos);
void Camera_SetBounds(vec4 rect);
void Camera_GetPosition(vec2 pos);
void Camera_GetBounds(vec4 bounds);
