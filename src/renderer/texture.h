/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "renderer.h"

enum {
    FlipNone,
    FlipHorizontal,
    FlipVertical
};

void DE_Renderer_texture_set_color(DE_Texture *texture, DE_Color color);
void DE_Renderer_texture_blit(DE_Vector2f pos, double angle, int flip, DE_Texture *texture);
void DE_Renderer_texture_blit_scaled(DE_Vector2f pos, DE_Vector2f scale, double angle, int flip, DE_Texture *texture);