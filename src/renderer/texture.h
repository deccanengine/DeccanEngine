/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "renderer.h"

void DE_Renderer_texture_set_color(DE_Texture *texture, DE_Color color);
void DE_Renderer_texture_draw(DE_Vector2i pos, DE_Texture *texture);
void DE_Renderer_texture_draw_with_scale(DE_Vector2i pos, DE_Vector2f scale, DE_Texture *texture);
