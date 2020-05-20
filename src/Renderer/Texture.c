/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Renderer.h>
#include <Deccan/Core.h>

void Sprite_SetColor(SpriteAsset *texture, Color color) {
    if(texture == NULL) { 
        return; 
    }
#ifdef DECCAN_RENDERER_SDL
    SDL_SetTextureColorMod(texture->texture[0], color.r, color.g, color.b);
#else

#endif
}

Vector2i Sprite_GetSize(SpriteAsset *texture) {
    Vector2i size;

    if(SDL_QueryTexture(texture->texture[0], NULL, NULL, &size.x, &size.y) > 0) {
        DE_REPORT("Cannot get texture size of texture: %s : %s", texture->name, SDL_GetError());
    }

    return size;
}

void Sprite_SetAnimLoop(SpriteAsset *texture, bool loop) {
    int32_t flags = 0;

    if(texture->flags & AnimActive) { flags |= AnimActive; }
    if(loop) { flags |= AnimLoop; }

    texture->flags = flags;
}

bool Sprite_GetAnimLoop(SpriteAsset *texture) {
    return (bool)(texture->flags & AnimLoop);
}

void Sprite_SetAnimActive(SpriteAsset *texture, bool active) {
    int32_t flags = 0;

    if(active) { flags |= AnimActive; }
    if(texture->flags & AnimLoop) { flags |= AnimLoop; }

    texture->flags = flags;
}

bool Sprite_GetAnimActive(SpriteAsset *texture) {
    return (bool)(texture->flags & AnimActive);
}

void Sprite_SetAnimDelay(SpriteAsset *texture, float ms) {
    texture->delay = ms;
}

float Sprite_GetAnimDelay(SpriteAsset *texture) {
    return texture->delay;
}

void BlitInternal(Rect rect, Rect dim, Vector2f scale, double angle, Flip flip, SpriteAsset *texture) {
    if(texture == NULL) { 
        return; 
    }
    
    Vector2f camera = Camera_GetPosition();

#ifdef DECCAN_RENDERER_SDL
    SDL_Renderer *renderer = Renderer_GetRenderer();

    /* Source rect */
    SDL_Rect src = {
        dim.x, dim.y, dim.w, dim.h
    };

    /* Destination(target) rect */
    SDL_Rect tgt = {
        rect.x - camera.x, 
        rect.y - camera.y, 
        rect.w,
        rect.h
    };

    int width, height;
    /* Get the default width and height */
    if(SDL_QueryTexture(texture->texture[texture->current], NULL, NULL, &width, &height) > 0) {
        DE_REPORT("Cannot query texture: %s :%s", texture->name, SDL_GetError());
    }
    
    if(!src.w) { src.w = width;  }
    if(!src.h) { src.h = height; }
    if(!tgt.w) { tgt.w = width;  }
    if(!tgt.h) { tgt.h = height; }

    if(scale.x) { tgt.w *= scale.x; }
    if(scale.y) { tgt.h *= scale.y; }
    
    SDL_RenderCopyEx(renderer, texture->texture[texture->current], &src, &tgt, angle, NULL, flip);
#else

#endif
    
    /* Check if animation is active */
    if(texture->flags & AnimActive) {
        /* Change frame only if delay is reached */
        if(texture->delay <= SDL_GetTicks() - texture->clock) {
            texture->clock = SDL_GetTicks();

            /* Reached final frame */
            if(texture->current == texture->count - 1) {
                /* If looping is allowed then set to first(0 index) frame */
                if(texture->flags & AnimLoop) {
                    texture->current = 0;
                }
            }
            else {
                /* Simply increment frame */
                texture->current++;
            }
        }
    }
}

void Sprite_Blit(Rect rect, double angle, Flip flip, SpriteAsset *texture) {
    BlitInternal(rect, (Rect){0, 0, 0, 0}, (Vector2f){0.0f, 0.0f}, angle, flip, texture);
}

void Sprite_BlitScaled(Rect rect, Vector2f scale, double angle, Flip flip, SpriteAsset *texture) {
    BlitInternal(rect, (Rect){0, 0, 0, 0}, scale, angle, flip, texture);
}
    
void Sprite_BlitPartial(Rect rect, Rect dim, double angle, Flip flip, SpriteAsset *texture) {
    BlitInternal(rect, dim, (Vector2f){0, 0}, angle, flip, texture);
}

void Sprite_BlitPartialScaled(Rect rect, Rect dim, Vector2f scale, double angle, Flip flip, SpriteAsset *texture) {
    BlitInternal(rect, dim, scale, angle, flip, texture);
}
