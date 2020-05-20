/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Renderer.h>
#include <Deccan/Core.h>

#define PTR_NULLCHECK(x,y) if(!x) { return y; }

void Font_SetKerning(FontAsset *font, bool kerning) {
    PTR_NULLCHECK(font,);
    
    TTF_SetFontKerning(font->font, kerning ? 1 : 0);
}

bool Font_GetKerning(FontAsset *font) {
    PTR_NULLCHECK(font, false);

    return (bool)TTF_GetFontKerning(font->font);
}

Vector2i Font_CalculateTextSize(FontAsset *font, const char *text) {
    Vector2i size = {-1, -1};
    
    PTR_NULLCHECK(font, size);
    TTF_SizeText(font->font, text, &size.x, &size.y);
    
    return size;
}

SpriteAsset *Font_FastText(FontAsset *font, const char *text, Color color) {
    PTR_NULLCHECK(font, NULL);

	SDL_Renderer *renderer = Renderer_GetRenderer();
    
    SDL_Color scol = {
        color.r, 
        color.g, 
        color.b, 
        color.a
    };

    SDL_Surface *surf = TTF_RenderText_Solid(font->font, text, scol);
    if(surf == NULL) {
        DE_REPORT("Cannot generate font text surface: %s", TTF_GetError());
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
    if(tex == NULL) {
        DE_REPORT("Cannot create text texture: %s", SDL_GetError());
    }
 
    SpriteAsset *asset = Asset_NewSpriteAsset("__font_generated_fase_text_texture__");
    stbds_arrput(asset->texture, tex);

    return asset;
}

SpriteAsset *Font_Text(FontAsset *font, const char *text, FontStyle style, Color color) {
    Font_OutlinedText(font, text, style, -1, color);
}

SpriteAsset *Font_OutlinedText(FontAsset *font, const char *text, FontStyle style, int32_t outline, Color color) {
    PTR_NULLCHECK(font, NULL);
    
    SDL_Renderer *renderer = Renderer_GetRenderer();
    
    SDL_Color scol = {
        color.r, 
        color.g, 
        color.b, 
        color.a
    };
	
	int cstyle = TTF_GetFontStyle(font->font);
	TTF_SetFontStyle(font->font, style);

    int coutline;
    if(outline != -1) {
        coutline = TTF_GetFontOutline(font->font);
        TTF_SetFontOutline(font->font, outline);
    }

    SDL_Surface *surf = TTF_RenderText_Blended(font->font, text, scol);
    if(surf == NULL) {
        DE_REPORT("Cannot generate font text surface: %s", TTF_GetError());
    }

    if(outline != -1) {
        TTF_SetFontOutline(font->font, coutline);
    }
	
	TTF_SetFontStyle(font->font, cstyle);

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
    if(tex == NULL) {
        DE_REPORT("Cannot create text texture: %s", SDL_GetError());
    }
 
    SpriteAsset *asset = Asset_NewSpriteAsset("__font_generated_text_texture__");
    stbds_arrput(asset->texture, tex);

    return asset;
}