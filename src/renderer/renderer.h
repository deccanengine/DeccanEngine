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

void _priv_Renderer_clear(Deccan_Color color);

void _priv_Renderer_set_color(Deccan_Color color);
void _priv_Renderer_set_pixel_size(Deccan_Vector2f size);

Deccan_Color _priv_Renderer_get_color();
Deccan_Vector2f _priv_Renderer_get_pixel_size();