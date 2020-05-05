/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "texture.h"
#include "../core/core.h"

void DE_Renderer_TextureSetColor(DE_Texture *texture, DE_Color color) {
    if(texture == NULL) { return; }
#ifdef DECCAN_RENDERER_SDL
    SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
#else

#endif
}

DE_Vector2i DE_Renderer_TextureGetSize(DE_Texture *texture) {
    DE_Vector2i size;
    if(SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y) > 0) {
        DE_report("Cannot get texture size: %s", SDL_GetError());
    }
    return size;
}

void DE_Renderer_TextureBlit(DE_Rect rect, double angle, int flip, DE_Texture *texture) {
    DE_Renderer_TextureBlitScaled(rect, (DE_Vector2f){0.0f, 0.0f}, angle, flip, texture);
}

void DE_Renderer_TextureBlitScaled(DE_Rect rect, DE_Vector2f scale, double angle, int flip, DE_Texture *texture) {
    if(texture == NULL) { return; }
    DE_GameInfo *engine = DE_Core_GetGlobalInfo();

#ifdef DECCAN_RENDERER_SDL
    SDL_Rect tgt = {
        rect.x - engine->camera.x, 
        rect.y - engine->camera.y, 
        rect.w, 
        rect.h
    };

    if((!tgt.w || !tgt.h) && SDL_QueryTexture(texture, NULL, NULL, &tgt.w, &tgt.h) > 0) {
        DE_report("Cannot query texture: %s", SDL_GetError());
    }
    
    if(scale.x && scale.y) { 
        tgt.w *= scale.x;
        tgt.h *= scale.y;
    }
    
    SDL_RenderCopyEx(engine->renderer, texture, NULL, &tgt, angle, NULL, flip);
#else

#endif
}
    
// Incomplete/broken (WIP).
void DE_Renderer_TextureBlitPartial(DE_Rect rect, DE_Rect dim, double angle, int flip, DE_Texture *texture) {
    if(texture == NULL) { return; }
    DE_GameInfo *engine = DE_Core_GetGlobalInfo();

#ifdef DECCAN_RENDERER_SDL
    SDL_Rect tgt = {
        rect.x - engine->camera.x, 
        rect.y - engine->camera.y, 
        rect.w,
        rect.h
    };

    if((!tgt.w || !tgt.h) && SDL_QueryTexture(texture, NULL, NULL, &tgt.w, &tgt.h) > 0) {
        DE_report("Cannot query texture: %s", SDL_GetError());
    }

    SDL_Rect src = {
        dim.x, dim.y, dim.w, dim.h
    };
    
    SDL_RenderCopyEx(engine->renderer, texture, &src, &tgt, angle, NULL, flip);
#else

#endif
}
