/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "../Core/Utils.h"
#include "../Core/String.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct DeccanFontAsset {
    char *name;
    TTF_Font *font;
} DeccanFontAsset;

/////////////////////////////////////////////////
// Constructor/Destructor
////////////////////////////////////////////////

DeccanFontAsset *DE_FontNew(const char *name);
void DE_FontDelete(DeccanFontAsset *asset);

/////////////////////////////////////////////////
// Setters/Getters
////////////////////////////////////////////////

void DE_FontSetKerning(DeccanFontAsset *font, bool kerning);
bool DE_FontGetKerning(DeccanFontAsset *font);

/////////////////////////////////////////////////
// Utility functions
////////////////////////////////////////////////

void DE_FontCalculateTextSize(DeccanFontAsset *font, const char *text, vec2 size);
