/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "Color.h"
#include "../Asset/FontAsset.h"
#include "../Asset/SpriteAsset.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

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

/////////////////////////////////////////////////
// Font/Text rendering
////////////////////////////////////////////////

SpriteAsset *Font_FastText(FontAsset *font, const char *text, Color color);
SpriteAsset *Font_Text(FontAsset *font, const char *text, FontStyle style, Color color);
SpriteAsset *Font_OutlinedText(FontAsset *font, const char *text, FontStyle style, int32_t outline, Color color);