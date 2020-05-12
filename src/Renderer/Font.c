/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Renderer.h>
#include <Deccan/Core.h>

TextureAsset *Font_Text(FontAsset *font, const char *text, Color color) {
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

    TextureAsset *asset = DE_NEW(TextureAsset, 1);
    asset->name = DE_NEWSTRING("__font_generated_text_texture__");
    asset->texture = tex;

    return asset;
}