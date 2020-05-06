/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "color.h"
#include "../physics/shape.h"
#include "../utils/vector.h"

typedef enum {
    BlendMode_None  = SDL_BLENDMODE_NONE,
    BlendMode_Alpha = SDL_BLENDMODE_BLEND,
    BlendMode_Add   = SDL_BLENDMODE_ADD,
    BlendMode_Mod   = SDL_BLENDMODE_MOD
} DE_BlendMode;

void DE_Renderer_Clear();
void DE_Renderer_ClearColor(DE_Color color);

void DE_Renderer_SetBackgroundColor(DE_Color color);
void DE_Renderer_SetBackgroundTexture(DE_Texture *texture);
void DE_Renderer_SetTarget(DE_Texture *target);
void DE_Renderer_SetColor(DE_Color color);
void DE_Renderer_SetPixelSize(DE_Vector2f size);
void DE_Renderer_SetBlendMode(int blend_mode);

DE_Color DE_Renderer_GetBackgroundColor();
DE_Texture *DE_Renderer_GetBackgroundTexture();
DE_Texture *DE_Renderer_GetTarget();
DE_Color DE_Renderer_GetColor();
DE_Vector2f DE_Renderer_GetPixelSize();
DE_BlendMode DE_Renderer_GetBlendMode();