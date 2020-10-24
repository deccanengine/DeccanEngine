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
} DeccanRenderBlendMode;

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Renderer functions
////////////////////////////////////////////////

SDL_Renderer *DE_RendererGetRenderer();
void DE_RendererInit(SDL_Window *window);
void DE_RendererQuit();
void DE_RendererPresent();
void DE_RendererBackground();
void DE_RendererClear();
void DE_RendererClearColor(DeccanColor color);
void DE_RendererSetBackgroundColor(DeccanColor color);
void DE_RendererSetBackgroundTexture(DeccanSpriteAsset *texture);
void DE_RendererSetTarget(DeccanSpriteAsset *target);
void DE_RendererSetColor(DeccanColor color);
void DE_RendererSetPixelSize(vec2 size);
void DE_RendererSetBlendMode(int blend_mode);
DeccanColor DE_RendererGetBackgroundColor();
DeccanSpriteAsset *DE_RendererGetBackgroundTexture();
DeccanSpriteAsset *DE_RendererGetTarget();
DeccanColor DE_RendererGetColor();
void DE_RendererGetPixelSize(vec2 size);
DeccanRenderBlendMode DE_RendererGetBlendMode();
