/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include <Deccan/Config.h>

typedef enum {
    BlendMode_None  = SDL_BLENDMODE_NONE,
    BlendMode_Alpha = SDL_BLENDMODE_BLEND,
    BlendMode_Add   = SDL_BLENDMODE_ADD,
    BlendMode_Mod   = SDL_BLENDMODE_MOD
} BlendMode;

typedef enum {
    FlipNone,
    FlipHorizontal,
    FlipVertical
} Flip;

typedef struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;

typedef struct ColorList_ {
    Color blank, 
    white, black, grey, dark_grey,
    red, dark_red, green, dark_green,
    blue, dark_blue, yellow, cyan,
    magenta, orange, violet, fuchsia;
} ColorList_;

static ColorList_ ColorList = {
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

/* Renderer */
void Renderer_Clear();
void Renderer_ClearColor(Color color);
void Renderer_SetBackgroundColor(Color color);
void Renderer_SetBackgroundTexture(RawTexture *texture);
void Renderer_SetTarget(RawTexture *target);
void Renderer_SetColor(Color color);
void Renderer_SetPixelSize(Vector2f size);
void Renderer_SetBlendMode(int blend_mode);
Color Renderer_GetBackgroundColor();
RawTexture *Renderer_GetBackgroundTexture();
RawTexture *Renderer_GetTarget();
Color Renderer_GetColor();
Vector2f Renderer_GetPixelSize();
BlendMode Renderer_GetBlendMode();

/* Drawing */
void Renderer_DrawPoint(Vector2f pos, Color color);
void Renderer_DrawLine(Vector2f start, Vector2f end, Color color);
void Renderer_DrawRect(Rect rect, Color color);
void Renderer_DrawFilledRect(Rect rect, Color color);
void Renderer_DrawCircle(Circle circle, Color color);
void Renderer_DrawFilledCircle(Circle circle, Color color);

/* Texture */
void Renderer_TextureSetColor(RawTexture *texture, Color color);
Vector2i Renderer_TextureGetSize(RawTexture *texture);
void Renderer_TextureBlit(Rect rect, double angle, Flip flip, RawTexture *texture);
void Renderer_TextureBlitScaled(Rect rect, Vector2f scale, double angle, Flip flip, RawTexture *texture);
void Renderer_TextureBlitPartial(Rect rect, Rect dim, double angle, Flip flip, RawTexture *texture);

/* Font/Text */
SDL_Texture *Renderer_FontText(TTF_Font *font, const char *text, Color color);