/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "FontAsset.h"

#define PTR_NULLCHECK(x,y) if(!x) { return y; }

/////////////////////////////////////////////////
// Constructor/Destructor
////////////////////////////////////////////////

DeccanFontAsset *DE_FontNew(const char *name) {
    DeccanFontAsset *asset = DE_Alloc(sizeof(DeccanFontAsset), 1);
    asset->name = DE_StringNew(name);
    return asset;
}

void DE_FontDelete(DeccanFontAsset *asset) {
	if(!asset) return;

    DE_Free(asset->name);
    DE_Free(asset->font);
    DE_Free(asset);
}

/////////////////////////////////////////////////
// Setters/Getters
////////////////////////////////////////////////

void DE_FontSetKerning(DeccanFontAsset *font, bool kerning) {
    PTR_NULLCHECK(font,);

    TTF_SetFontKerning(font->font, kerning ? 1 : 0);
}

bool DE_FontGetKerning(DeccanFontAsset *font) {
    PTR_NULLCHECK(font, false);

    return (bool)TTF_GetFontKerning(font->font);
}

/////////////////////////////////////////////////
// Utility functions
////////////////////////////////////////////////

void DE_FontCalculateTextSize(DeccanFontAsset *font, const char *text, vec2 size) {
    int32_t x = -1;
    int32_t y = -1;
    size[0] = -1;
    size[1] = -1;

    PTR_NULLCHECK(font,);
    TTF_SizeText(font->font, text, &x, &y);

    size[0] = (float)x;
    size[1] = (float)y;
}

#undef PTR_NULLCHECK
