/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "renderer.h"

void _priv_Renderer_texture_set_color(Deccan_Texture *texture, Deccan_Color color);
void _priv_Renderer_texture_draw(Deccan_Vector2i pos, Deccan_Texture *texture);
void _priv_Renderer_texture_draw_with_scale(Deccan_Vector2i pos, Deccan_Vector2f scale, Deccan_Texture *texture);
