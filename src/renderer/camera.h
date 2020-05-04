/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */
 
#pragma once
#include "../config.h"
#include "renderer.h"
#include "../core/core.h"
#include "../core/object.h"
#include "../physics/shape.h"
#include "../utils/vector.h"

void DE_Camera_Move(DE_Vector2f pos);
void DE_Camera_CenterOn(DE_GameObject *obj);

void DE_Camera_SetPosition(DE_Vector2f pos);
void DE_Camera_SetBounds(DE_PosRect rect);

DE_Vector2f DE_Camera_GetPosition();
DE_PosRect  DE_Camera_GetBounds();