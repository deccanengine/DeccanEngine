/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
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

void Sprite_Blit(Rect rect, double angle, Flip flip, SpriteAsset *texture);
void Sprite_BlitScaled(Rect rect, Vector2 scale, double angle, Flip flip, SpriteAsset *texture);
void Sprite_BlitPartial(Rect rect, Rect dim, double angle, Flip flip, SpriteAsset *texture);
void Sprite_BlitPartialScaled(Rect rect, Rect dim, Vector2 scale, double angle, Flip flip, SpriteAsset *texture);
