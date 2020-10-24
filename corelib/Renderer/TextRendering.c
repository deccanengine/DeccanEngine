/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "TextRendering.h"
#include "Renderer.h"

#define PTR_NULLCHECK(x,y) if(!x) { return y; }

DeccanSpriteAsset *DE_FontFastText(DeccanFontAsset *font, const char *text, DeccanColor color) {
    PTR_NULLCHECK(font, NULL);

	SDL_Renderer *renderer = DE_RendererGetRenderer();

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

    DeccanSpriteAsset *asset = DE_SpriteNew("__font_generated_fase_text_texture__");
    stbds_arrput(asset->texture, tex);

    return asset;
}

DeccanSpriteAsset *DE_FontText(DeccanFontAsset *font, const char *text, FontStyle style, DeccanColor color) {
    return DE_FontOutlinedText(font, text, style, -1, color);
}

DeccanSpriteAsset *DE_FontOutlinedText(DeccanFontAsset *font, const char *text, FontStyle style, int32_t outline, DeccanColor color) {
    PTR_NULLCHECK(font, NULL);

    SDL_Renderer *renderer = DE_RendererGetRenderer();

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

    DeccanSpriteAsset *asset = DE_SpriteNew("__font_generated_text_texture__");
    stbds_arrput(asset->texture, tex);

    return asset;
}
