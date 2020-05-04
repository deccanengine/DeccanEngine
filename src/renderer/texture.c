/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "texture.h"

void DE_Renderer_TextureSetColor(DE_Texture *texture, DE_Color color) {
#ifdef DECCAN_RENDERER_SDL
    SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
#else

#endif
}

void DE_Renderer_TextureBlit(DE_Vector2f pos, double angle, int flip, DE_Texture *texture) {
    DE_GameInfo *engine = DE_Core_GetGlobalInfo();

#ifdef DECCAN_RENDERER_SDL
    SDL_Rect rect = {pos.x - engine->camera.x, pos.y - engine->camera.y, 0, 0};
    if(SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h) > 0) {
        DE_report("Cannot query texture: %s", SDL_GetError());
    }
    SDL_RenderCopyEx(engine->renderer, texture, NULL, &rect, angle, NULL, flip);
#else

#endif
}

void DE_Renderer_TextureBlitScaled(DE_Vector2f pos, DE_Vector2f scale, double angle, int flip, DE_Texture *texture) {
    DE_GameInfo *engine = DE_Core_GetGlobalInfo();

#ifdef DECCAN_RENDERER_SDL
    SDL_Rect rect = {pos.x - engine->camera.x, pos.y - engine->camera.y, 0, 0};
    if(SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h) > 0) {
        DE_report("Cannot query texture: %s", SDL_GetError());
    }
    rect.w *= scale.x; rect.h *= scale.y;
    SDL_RenderCopyEx(engine->renderer, texture, NULL, &rect, angle, NULL, flip); 
#else

#endif
} 