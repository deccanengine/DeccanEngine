/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "Renderer.h"
#include "Color.h"
#include "Primitives.h"
#include "../Asset/SpriteAsset.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

typedef enum {
    FlipNone,
    FlipHorizontal,
    FlipVertical
} Flip;

/////////////////////////////////////////////////
// Texture rendering
////////////////////////////////////////////////

//void Sprite_SetColor(SpriteAsset *texture, Color color);

void Sprite_Blit(vec4 rect, double angle, Flip flip, SpriteAsset *texture);
void Sprite_BlitScaled(vec4 rect, vec2 scale, double angle, Flip flip, SpriteAsset *texture);
void Sprite_BlitPartial(vec4 rect, vec4 dim, double angle, Flip flip, SpriteAsset *texture);
void Sprite_BlitPartialScaled(vec4 rect, vec4 dim, vec2 scale, double angle, Flip flip, SpriteAsset *texture);
