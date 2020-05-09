/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Renderer.h>
#include <Deccan/Core.h>

void Renderer_TextureSetColor(RawTexture *texture, Color color) {
    if(texture == NULL) { return; }
#ifdef DECCAN_RENDERER_SDL
    SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
#else

#endif
}

Vector2i Renderer_TextureGetSize(RawTexture *texture) {
    Vector2i size;
    if(SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y) > 0) {
        DE_report("Cannot get texture size: %s", SDL_GetError());
    }
    return size;
}

void Renderer_TextureBlit(Rect rect, double angle, Flip flip, RawTexture *texture) {
    Renderer_TextureBlitScaled(rect, (Vector2f){0.0f, 0.0f}, angle, flip, texture);
}

void Renderer_TextureBlitScaled(Rect rect, Vector2f scale, double angle, Flip flip, RawTexture *texture) {
    if(texture == NULL) { return; }
    GameInfo *engine = Core_GetGlobalInfo();
    Vector2f camera = Camera_GetPosition();
    SDL_Renderer *renderer = Renderer_GetRenderer();

#ifdef DECCAN_RENDERER_SDL
    SDL_Rect tgt = {
        rect.x - camera.x, 
        rect.y - camera.y, 
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
    
    SDL_RenderCopyEx(renderer, texture, NULL, &tgt, angle, NULL, flip);
#else

#endif
}
    
void Renderer_TextureBlitPartial(Rect rect, Rect dim, double angle, Flip flip, RawTexture *texture) {
    if(texture == NULL) { return; }
    GameInfo *engine = Core_GetGlobalInfo();
    Vector2f camera = Camera_GetPosition();
    SDL_Renderer *renderer = Renderer_GetRenderer();

#ifdef DECCAN_RENDERER_SDL
    SDL_Rect src = {
        dim.x, dim.y, dim.w, dim.h
    };

    SDL_Rect tgt = {
        rect.x - camera.x, 
        rect.y - camera.y, 
        rect.w,
        rect.h
    };

    if(!src.w || !src.h) {
        if(SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h) > 0) {
            DE_report("Cannot query texture: %s", SDL_GetError());
        }
    }

    if(!tgt.w || !tgt.h) {
        tgt.w = src.w;
        tgt.h = src.h;
    }
    
    SDL_RenderCopyEx(renderer, texture, &src, &tgt, angle, NULL, flip);
#else

#endif
}
