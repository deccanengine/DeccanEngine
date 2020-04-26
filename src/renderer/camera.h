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
#include "../utils/vector.h"

void DE_Camera_move(DE_Vector2i pos);
void DE_Camera_set_position(DE_Vector2i pos);
void DE_Camera_center_on(DE_GameObject *obj);