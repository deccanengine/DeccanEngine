/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "Primitives.h"
#include "Color.h"
#include "Texture.h"
#include "TextRendering.h"
#include "../Asset/FontAsset.h"
#include "../Asset/SpriteAsset.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

typedef enum {
    BlendMode_None  = SDL_BLENDMODE_NONE,
    BlendMode_Alpha = SDL_BLENDMODE_BLEND,
    BlendMode_Add   = SDL_BLENDMODE_ADD,
    BlendMode_Mod   = SDL_BLENDMODE_MOD
} BlendMode;

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Renderer functions
////////////////////////////////////////////////

SDL_Renderer *Renderer_GetRenderer();
void Renderer_Init(SDL_Window *window);
void Renderer_Quit();
void Renderer_Present();
void Renderer_Background();
void Renderer_Clear();
void Renderer_ClearColor(Color color);
void Renderer_SetBackgroundColor(Color color);
void Renderer_SetBackgroundTexture(SpriteAsset *texture);
void Renderer_SetTarget(SpriteAsset *target);
void Renderer_SetColor(Color color);
void Renderer_SetPixelSize(Vector2 size);
void Renderer_SetBlendMode(int blend_mode);
Color Renderer_GetBackgroundColor();
SpriteAsset *Renderer_GetBackgroundTexture();
SpriteAsset *Renderer_GetTarget();
Color Renderer_GetColor();
Vector2 Renderer_GetPixelSize();
BlendMode Renderer_GetBlendMode();