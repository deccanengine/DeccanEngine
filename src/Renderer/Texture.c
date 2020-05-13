/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Renderer.h>
#include <Deccan/Core.h>

void Texture_SetColor(TextureAsset *texture, Color color) {
    if(texture == NULL) { 
        return; 
    }
#ifdef DECCAN_RENDERER_SDL
    SDL_SetTextureColorMod(texture->texture[0], color.r, color.g, color.b);
#else

#endif
}

Vector2i Texture_GetSize(TextureAsset *texture) {
    Vector2i size;

    if(SDL_QueryTexture(texture->texture[0], NULL, NULL, &size.x, &size.y) > 0) {
        DE_REPORT("Cannot get texture size of texture: %s : %s", texture->name, SDL_GetError());
    }

    return size;
}

void Texture_Blit(Rect rect, double angle, Flip flip, TextureAsset *texture) {
    Texture_BlitScaled(rect, (Vector2f){0.0f, 0.0f}, angle, flip, texture);
}

void Texture_BlitScaled(Rect rect, Vector2f scale, double angle, Flip flip, TextureAsset *texture) {
    if(texture == NULL) { 
        return; 
    }

    Vector2f camera = Camera_GetPosition();
    SDL_Renderer *renderer = Renderer_GetRenderer();

#ifdef DECCAN_RENDERER_SDL
    SDL_Rect tgt = {
        rect.x - camera.x, 
        rect.y - camera.y, 
        rect.w, 
        rect.h
    };

    if((!tgt.w || !tgt.h) && SDL_QueryTexture(texture->texture[texture->current], NULL, NULL, &tgt.w, &tgt.h) > 0) {
        DE_REPORT("Cannot query texture: %s : %s", texture->name, SDL_GetError());
    }
    
    if(scale.x && scale.y) { 
        tgt.w *= scale.x;
        tgt.h *= scale.y;
    }
    
    SDL_RenderCopyEx(renderer, texture->texture[texture->current], NULL, &tgt, angle, NULL, flip);
#else

#endif

    if(texture->delay <= SDL_GetTicks() - texture->clock) {
        texture->clock = SDL_GetTicks();
        if(texture->current++ == texture->count - 1) {
            texture->current = 0;
        }
    }
}
    
void Texture_BlitPartial(Rect rect, Rect dim, double angle, Flip flip, TextureAsset *texture) {
    if(texture == NULL) { return; }
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
        if(SDL_QueryTexture(texture->texture[0], NULL, NULL, &src.w, &src.h) > 0) {
            DE_REPORT("Cannot query texture: %s :%s", texture->name, SDL_GetError());
        }
    }

    if(!tgt.w || !tgt.h) {
        tgt.w = src.w;
        tgt.h = src.h;
    }
    
    SDL_RenderCopyEx(renderer, texture->texture[0], &src, &tgt, angle, NULL, flip);
#else

#endif
}
