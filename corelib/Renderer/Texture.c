/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Texture.h"
#include "Camera.h"
#include "../Asset/SpriteAsset.h"
#include "../Core/Core.h"

// To be replaced with better and practical functions
/*
void DE_SpriteSetDeccanColor(DeccanSpriteAsset *texture, DeccanColor color) {
    if(texture == NULL) {
        return;
    }
#ifdef DECCAN_RENDERER_SDL
    SDL_SetTextureDeccanColorMod(texture->texture[0], color.r, color.g, color.b);
#else

#endif
}
*/

void BlitInternal(vec4 rect, vec4 dim, vec2 scale, double angle, Flip flip, DeccanSpriteAsset *texture) {
    if(texture == NULL) {
        return;
    }

    vec2 camera; DE_CameraGetPosition(camera);

#ifdef DECCAN_RENDERER_SDL
    SDL_Renderer *renderer = DE_RendererGetRenderer();

    /* Source rect */
    SDL_Rect src = {
        dim[0], dim[1], dim[2], dim[3]
    };

    /* Destination(target) rect */
    SDL_Rect tgt = {
        rect[0] - camera[0],
        rect[1] - camera[1],
        rect[2],
        rect[3]
    };

    //int width, height;
    /* Get the default width and height */
    //if(SDL_QueryTexture(texture->texture[texture->current], NULL, NULL, &width, &height) > 0) {
    //    DE_WARN("Cannot query texture: %s :%s", texture->name, SDL_GetError());
    //}

    vec2 size; DE_SpriteGetSize(texture, size);

    if(!src.w) { src.w = size[0]; }
    if(!src.h) { src.h = size[1]; }
    if(!tgt.w) { tgt.w = size[0]; }
    if(!tgt.h) { tgt.h = size[1]; }

    if(scale[0]) { tgt.w *= scale[0]; }
    if(scale[1]) { tgt.h *= scale[1]; }

    SDL_RenderCopyEx(renderer, texture->texture[texture->current], &src, &tgt, angle, NULL, flip);
#else

#endif

    /* Check if animation is active */
    if(texture->flags & DECCAN_ANIMFLAG_ACTIVE) {
        /* Change frame only if delay is reached */
        if(texture->delay <= SDL_GetTicks() - texture->clock) {
            texture->clock = SDL_GetTicks();

            /* Reached final frame */
            if(texture->current == texture->count - 1) {
                /* If looping is allowed then set to first(0 index) frame */
                if(texture->flags & DECCAN_ANIMFLAG_LOOP) {
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

void DE_SpriteBlit(vec4 rect, double angle, Flip flip, DeccanSpriteAsset *texture) {
    BlitInternal(rect, (vec4){0, 0, 0, 0}, (vec2){0.0f, 0.0f}, angle, flip, texture);
}

void DE_SpriteBlitScaled(vec4 rect, vec2 scale, double angle, Flip flip, DeccanSpriteAsset *texture) {
    BlitInternal(rect, (vec4){0, 0, 0, 0}, scale, angle, flip, texture);
}

void DE_SpriteBlitPartial(vec4 rect, vec4 dim, double angle, Flip flip, DeccanSpriteAsset *texture) {
    BlitInternal(rect, dim, (vec2){0, 0}, angle, flip, texture);
}

void DE_SpriteBlitPartialScaled(vec4 rect, vec4 dim, vec2 scale, double angle, Flip flip, DeccanSpriteAsset *texture) {
    BlitInternal(rect, dim, scale, angle, flip, texture);
}
