/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Renderer.h>
#include <Deccan/Core.h>

SDL_Texture *DE_Renderer_FontText(TTF_Font *font, const char *text, DE_Color color) {
    SDL_Color scol = {color.r, color.g, color.b, color.a};
    SDL_Surface *surf = TTF_RenderText_Solid(font, text, scol);
    if(surf == NULL) {
        DE_report("Cannot generate font text surface: %s", TTF_GetError());
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(DE_Core_GetGlobalInfo()->renderer, surf);
    if(tex == NULL) {
        DE_report("Cannot create text texture: %s", SDL_GetError());
    }

    return tex;
}