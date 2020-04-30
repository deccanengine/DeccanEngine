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

void DE_Camera_move(DE_Vector2i pos);
void DE_Camera_center_on(DE_GameObject *obj);

void DE_Camera_set_position(DE_Vector2i pos);
void DE_Camera_set_bounds(DE_PosRect rect);

DE_Vector2i DE_Camera_get_position();
DE_PosRect  DE_Camera_get_bounds();