/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
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

DE_API DeccanSpriteAsset *DE_FontFastText(DeccanFontAsset *font, const char *text, DeccanColor color);
DE_API DeccanSpriteAsset *DE_FontText(DeccanFontAsset *font, const char *text, FontStyle style, DeccanColor color);
DE_API DeccanSpriteAsset *DE_FontOutlinedText(DeccanFontAsset *font, const char *text, FontStyle style, int32_t outline, DeccanColor color);
