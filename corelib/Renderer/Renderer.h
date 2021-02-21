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
    BlendMode_None  = SDL_BLENDMODE_NONE,
    BlendMode_Alpha = SDL_BLENDMODE_BLEND,
    BlendMode_Add   = SDL_BLENDMODE_ADD,
    BlendMode_Mod   = SDL_BLENDMODE_MOD
} DeccanRenderBlendMode;

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Renderer functions
////////////////////////////////////////////////

DE_API SDL_Renderer *DE_RendererGetRenderer(void);
DE_API void DE_RendererInit(SDL_Window *window);
DE_API void DE_RendererQuit(void);
DE_API void DE_RendererPresent(void);
DE_API void DE_RendererBackground(void);
DE_API void DE_RendererClear(void);
DE_API void DE_RendererClearColor(DeccanColor color);
DE_API void DE_RendererSetBackgroundColor(DeccanColor color);
DE_API void DE_RendererSetBackgroundTexture(DeccanSpriteAsset *texture);
DE_API void DE_RendererSetTarget(DeccanSpriteAsset *target);
DE_API void DE_RendererSetColor(DeccanColor color);
DE_API void DE_RendererSetPixelSize(vec2 size);
DE_API void DE_RendererSetBlendMode(int blend_mode);
DE_API DeccanColor DE_RendererGetBackgroundColor(void);
DE_API DeccanSpriteAsset *DE_RendererGetBackgroundTexture(void);
DE_API DeccanSpriteAsset *DE_RendererGetTarget(void);
DE_API DeccanColor DE_RendererGetColor(void);
DE_API void DE_RendererGetPixelSize(vec2 size);
DE_API DeccanRenderBlendMode DE_RendererGetBlendMode(void);
