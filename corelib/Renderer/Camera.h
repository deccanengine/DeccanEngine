/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "Primitives.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Camera
////////////////////////////////////////////////

DE_API void DE_CameraMove(vec2 pos);
//void DE_CameraCenterOn(GameObject *obj);
DE_API void DE_CameraSetPosition(vec2 pos);
DE_API void DE_CameraSetBounds(vec4 rect);
DE_API void DE_CameraGetPosition(vec2 pos);
DE_API void DE_CameraGetBounds(vec4 bounds);
