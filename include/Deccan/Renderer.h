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
SDL_Renderer *Renderer_GetRenderer();
void Renderer_Init(SDL_Window *window);
void Renderer_Quit();
void Renderer_Present();
void Renderer_Background();
void Renderer_Clear();
void Renderer_ClearColor(Color color);
void Renderer_SetBackgroundColor(Color color);
void Renderer_SetBackgroundTexture(TextureAsset *texture);
void Renderer_SetTarget(TextureAsset *target);
void Renderer_SetColor(Color color);
void Renderer_SetPixelSize(Vector2f size);
void Renderer_SetBlendMode(int blend_mode);
Color Renderer_GetBackgroundColor();
TextureAsset *Renderer_GetBackgroundTexture();
TextureAsset *Renderer_GetTarget();
Color Renderer_GetColor();
Vector2f Renderer_GetPixelSize();
BlendMode Renderer_GetBlendMode();

/* Drawing */
void Draw_Point(Vector2f pos, Color color);
void Draw_Line(Vector2f start, Vector2f end, Color color);
void Draw_Rect(Rect rect, Color color);
void Draw_FilledRect(Rect rect, Color color);
void Draw_Circle(Circle circle, Color color);
void Draw_FilledCircle(Circle circle, Color color);

/* Texture */
void Texture_SetColor(TextureAsset *texture, Color color);
Vector2i Texture_GetSize(TextureAsset *texture);
void Texture_Blit(Rect rect, double angle, Flip flip, TextureAsset *texture);
void Texture_BlitScaled(Rect rect, Vector2f scale, double angle, Flip flip, TextureAsset *texture);
void Texture_BlitPartial(Rect rect, Rect dim, double angle, Flip flip, TextureAsset *texture);

/* Font/Text */
TextureAsset *Font_Text(FontAsset *font, const char *text, Color color);