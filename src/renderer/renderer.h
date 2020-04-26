/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "../core/core.h"
#include "../physics/shape.h"
#include "color.h"

void DE_Renderer_clear(DE_Color color);

void DE_Renderer_set_color(DE_Color color);
void DE_Renderer_set_pixel_size(DE_Vector2f size);

DE_Color DE_Renderer_get_color();
DE_Vector2f DE_Renderer_get_pixel_size();