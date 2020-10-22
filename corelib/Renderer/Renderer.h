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
#include "../Asset/FontAsset.h"
#include "../Asset/SpriteAsset.h"

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
void Renderer_ClearColor(DeccanColor color);
void Renderer_SetBackgroundColor(DeccanColor color);
void Renderer_SetBackgroundTexture(DeccanSpriteAsset *texture);
void Renderer_SetTarget(DeccanSpriteAsset *target);
void Renderer_SetColor(DeccanColor color);
void Renderer_SetPixelSize(vec2 size);
void Renderer_SetBlendMode(int blend_mode);
DeccanColor Renderer_GetBackgroundColor();
DeccanSpriteAsset *Renderer_GetBackgroundTexture();
DeccanSpriteAsset *Renderer_GetTarget();
DeccanColor Renderer_GetColor();
void Renderer_GetPixelSize(vec2 size);
BlendMode Renderer_GetBlendMode();
