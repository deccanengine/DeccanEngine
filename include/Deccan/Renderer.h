/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include <Deccan/Config.h>
#include <Deccan/Info.h>

typedef enum {
    BlendMode_None  = SDL_BLENDMODE_NONE,
    BlendMode_Alpha = SDL_BLENDMODE_BLEND,
    BlendMode_Add   = SDL_BLENDMODE_ADD,
    BlendMode_Mod   = SDL_BLENDMODE_MOD
} DE_BlendMode;

enum {
    FlipNone,
    FlipHorizontal,
    FlipVertical
};

typedef struct {
    uint8_t r, g, b, a;
} DE_Color;

typedef struct DE_ColorList {
    DE_Color blank, 
    white, black, grey, dark_grey,
    red, dark_red, green, dark_green,
    blue, dark_blue, yellow, cyan,
    magenta, orange, violet, fuchsia;
} DE_ColorList;

static DE_ColorList ColorList = {
    {  0,   0,   0,   0},
    {255, 255, 255, 255}, {  0,   0,   0, 255},
    {192, 192, 192, 255}, {128, 128, 128, 255},
	{255,   0,   0, 255}, {128,   0,   0, 255},
    {  0, 255,   0, 255}, {  0, 128,   0, 255},
    {  0,   0, 255, 255}, {  0,   0, 128, 255},
    {255, 255,   0, 255}, {  0, 255, 255, 255}, 
    {255,   0, 255, 255}, {255, 165,   0, 255}, 
    {238, 130, 238, 255}, {255,   0, 255, 255}
};

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

void DE_Renderer_DrawPoint(DE_Vector2f pos, DE_Color color);
void DE_Renderer_DrawLine(DE_Vector2f start, DE_Vector2f end, DE_Color color);
void DE_Renderer_DrawRect(DE_Rect rect, DE_Color color);
void DE_Renderer_DrawFilledRect(DE_Rect rect, DE_Color color);
void DE_Renderer_DrawCircle(DE_Circle circle, DE_Color color);
void DE_Renderer_DrawFilledCircle(DE_Circle circle, DE_Color color);

void DE_Renderer_TextureSetColor(DE_Texture *texture, DE_Color color);

DE_Vector2i DE_Renderer_TextureGetSize(DE_Texture *texture);

void DE_Renderer_TextureBlit(DE_Rect rect, double angle, int flip, DE_Texture *texture);
void DE_Renderer_TextureBlitScaled(DE_Rect rect, DE_Vector2f scale, double angle, int flip, DE_Texture *texture);
void DE_Renderer_TextureBlitPartial(DE_Rect rect, DE_Rect dim, double angle, int flip, DE_Texture *texture);

SDL_Texture *DE_Renderer_FontText(TTF_Font *font, const char *text, DE_Color color);