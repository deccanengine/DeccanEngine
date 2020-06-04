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

FontAsset *Font_New(const char *name) {
    FontAsset *asset = DE_NEW(FontAsset, 1);
    asset->name = DE_NEWSTRING(name);
    return asset;
}

/////////////////////////////////////////////////
// Setters/Getters
////////////////////////////////////////////////

void Font_SetKerning(FontAsset *font, bool kerning) {
    PTR_NULLCHECK(font,);
    
    TTF_SetFontKerning(font->font, kerning ? 1 : 0);
}

bool Font_GetKerning(FontAsset *font) {
    PTR_NULLCHECK(font, false);

    return (bool)TTF_GetFontKerning(font->font);
}

/////////////////////////////////////////////////
// Utility functions
////////////////////////////////////////////////

Vector2i Font_CalculateTextSize(FontAsset *font, const char *text) {
    Vector2i size = {-1, -1};
    
    PTR_NULLCHECK(font, size);
    TTF_SizeText(font->font, text, &size.x, &size.y);
    
    return size;
}

#undef PTR_NULLCHECK