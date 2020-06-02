/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
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

typedef enum {
    FlipNone,
    FlipHorizontal,
    FlipVertical
} Flip;

typedef enum {
	FontStyle_Bold = TTF_STYLE_BOLD,
	FontStyle_Italic = TTF_STYLE_ITALIC,
	FontStyle_Underline = TTF_STYLE_UNDERLINE,
	FontStyle_Strikethrough = TTF_STYLE_STRIKETHROUGH,
	FontStyle_Normal = TTF_STYLE_NORMAL
} FontStyle;

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;

static Color
    ColorList_Blank     = {  0,   0,   0,   0},
    ColorList_White     = {255, 255, 255, 255}, 
    ColorList_Black     = {  0,   0,   0, 255},
    ColorList_Grey      = {192, 192, 192, 255}, 
    ColorList_DarkGrey  = {128, 128, 128, 255},
	ColorList_Red       = {255,   0,   0, 255}, 
    ColorList_DarkRed   = {128,   0,   0, 255},
    ColorList_Green     = {  0, 255,   0, 255}, 
    ColorList_DarkGreen = {  0, 128,   0, 255},
    ColorList_Blue      = {  0,   0, 255, 255}, 
    ColorList_DarkBlue  = {  0,   0, 128, 255},
    ColorList_Yellow    = {255, 255,   0, 255}, 
    ColorList_Cyan      = {  0, 255, 255, 255}, 
    ColorList_Magenta   = {255,   0, 255, 255}, 
    ColorList_Orange    = {255, 165,   0, 255}, 
    ColorList_Violet    = {238, 130, 238, 255}, 
    ColorList_Fuchsia   = {255,   0, 255, 255};

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
void Renderer_SetPixelSize(Vector2f size);
void Renderer_SetBlendMode(int blend_mode);
Color Renderer_GetBackgroundColor();
SpriteAsset *Renderer_GetBackgroundTexture();
SpriteAsset *Renderer_GetTarget();
Color Renderer_GetColor();
Vector2f Renderer_GetPixelSize();
BlendMode Renderer_GetBlendMode();

/////////////////////////////////////////////////
// Drawing functions
////////////////////////////////////////////////

void Draw_Point(Vector2f pos, Color color);
void Draw_Line(Vector2f start, Vector2f end, Color color);
void Draw_Rect(Rect rect, Color color);
void Draw_FilledRect(Rect rect, Color color);
void Draw_Circle(Circle circle, Color color);
void Draw_FilledCircle(Circle circle, Color color);

/////////////////////////////////////////////////
// Sprite functions
////////////////////////////////////////////////

void Sprite_SetColor(SpriteAsset *texture, Color color);
Vector2i Sprite_GetSize(SpriteAsset *texture);
void Sprite_SetAnimLoop(SpriteAsset *texture, bool loop);
bool Sprite_GetAnimLoop(SpriteAsset *texture);
void Sprite_SetAnimActive(SpriteAsset *texture, bool active);
bool Sprite_GetAnimActive(SpriteAsset *texture);
void Sprite_SetAnimDelay(SpriteAsset *texture, float ms);
float Sprite_GetAnimDelay(SpriteAsset *texture);
void Sprite_Blit(Rect rect, double angle, Flip flip, SpriteAsset *texture);
void Sprite_BlitScaled(Rect rect, Vector2f scale, double angle, Flip flip, SpriteAsset *texture);
void Sprite_BlitPartial(Rect rect, Rect dim, double angle, Flip flip, SpriteAsset *texture);
void Sprite_BlitPartialScaled(Rect rect, Rect dim, Vector2f scale, double angle, Flip flip, SpriteAsset *texture);

/////////////////////////////////////////////////
// Font/Text functions
////////////////////////////////////////////////

void Font_SetKerning(FontAsset *font, bool kerning);
bool Font_GetKerning(FontAsset *font);

Vector2i Font_CalculateTextSize(FontAsset *font, const char *text);

SpriteAsset *Font_FastText(FontAsset *font, const char *text, Color color);
SpriteAsset *Font_Text(FontAsset *font, const char *text, FontStyle style, Color color);
SpriteAsset *Font_OutlinedText(FontAsset *font, const char *text, FontStyle style, int32_t outline, Color color);