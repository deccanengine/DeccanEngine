/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
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
    BlendMode_None = SDL_BLENDMODE_NONE,
    BlendMode_Alpha = SDL_BLENDMODE_BLEND,
    BlendMode_Add = SDL_BLENDMODE_ADD,
    BlendMode_Mod = SDL_BLENDMODE_MOD
} DeccanRenderBlendMode;

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Renderer functions
////////////////////////////////////////////////

DE_API SDL_Renderer *DE_SRendererGetRenderer(void);
DE_API void DE_SRendererInit(SDL_Window *window);
DE_API void DE_SRendererQuit(void);
DE_API void DE_SRendererPresent(void);
DE_API void DE_SRendererBackground(void);
DE_API void DE_SRendererClear(void);
DE_API void DE_SRendererClearColor(DeccanColor color);
DE_API void DE_SRendererSetBackgroundColor(DeccanColor color);
DE_API void DE_SRendererSetBackgroundTexture(DeccanSpriteAsset *texture);
DE_API void DE_SRendererSetTarget(DeccanSpriteAsset *target);
DE_API void DE_SRendererSetColor(DeccanColor color);
DE_API void DE_SRendererSetPixelSize(vec2 size);
DE_API void DE_SRendererSetBlendMode(int blend_mode);
DE_API DeccanColor DE_SRendererGetBackgroundColor(void);
DE_API DeccanSpriteAsset *DE_SRendererGetBackgroundTexture(void);
DE_API DeccanSpriteAsset *DE_SRendererGetTarget(void);
DE_API DeccanColor DE_SRendererGetColor(void);
DE_API void DE_SRendererGetPixelSize(vec2 size);
DE_API DeccanRenderBlendMode DE_SRendererGetBlendMode(void);
