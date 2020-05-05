/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "renderer.h"

void DE_Renderer_Clear(DE_Color color) {
    DE_Renderer_SetColor(color);
#ifdef DECCAN_RENDERER_SDL
    SDL_RenderClear(DE_Core_GetGlobalInfo()->renderer);
#else

#endif
}

void DE_Renderer_SetTarget(DE_Texture *target) {
    DE_GameInfo *engine = DE_Core_GetGlobalInfo(); 
    if(target == NULL) { target = engine->target; }

#ifdef DECCAN_RENDERER_SDL
    if(SDL_SetRenderTarget(engine->renderer, target) != 0) {
        DE_report("Cannot set render target: %s", SDL_GetError());
    }
#else

#endif
}

void DE_Renderer_SetColor(DE_Color color) {
#ifdef DECCAN_RENDERER_SDL
    SDL_SetRenderDrawColor(DE_Core_GetGlobalInfo()->renderer, color.r, color.g, color.b, color.a);
#else

#endif
}

void DE_Renderer_SetPixelSize(DE_Vector2f size) {
#ifdef DECCAN_RENDERER_SDL
    SDL_RenderSetScale(DE_Core_GetGlobalInfo()->renderer, size.x, size.y);
#else

#endif
}

void DE_Renderer_SetBlendMode(int blend_mode) {
#ifdef DECCAN_RENDERER_SDL
    if(SDL_SetRenderDrawBlendMode(DE_Core_GetGlobalInfo()->renderer, blend_mode) != 0) {
        DE_report("Cannot set blend mode: %s", SDL_GetError());
    }
#else

#endif
}

DE_Texture *DE_Renderer_GetTarget() {
    DE_Texture *target;
#ifdef DECCAN_RENDERER_SDL
    target = SDL_GetRenderTarget(DE_Core_GetGlobalInfo()->renderer);
    if(target == NULL) {
        DE_error("Render target is NULL");
    }
#else

#endif
    return target;
}

DE_Color DE_Renderer_GetColor() {
    DE_Color color = {0, 0, 0, 0};
#ifdef DECCAN_RENDERER_SDL
    SDL_GetRenderDrawColor(DE_Core_GetGlobalInfo()->renderer, &color.r, &color.g, &color.b, &color.a);
#else

#endif
    return color;
}

DE_Vector2f DE_Renderer_GetPixelSize() {
    DE_Vector2f size = {0.0f, 0.0f};
#ifdef DECCAN_RENDERER_SDL
    SDL_RenderGetScale(DE_Core_GetGlobalInfo()->renderer, &size.x, &size.y);
#else

#endif
    return size;
}

DE_BlendMode DE_Renderer_GetBlendMode() {
    SDL_BlendMode blend = SDL_BLENDMODE_NONE;
#ifdef DECCAN_RENDERER_SDL
    SDL_GetRenderDrawBlendMode(DE_Core_GetGlobalInfo()->renderer, &blend);
#else

#endif
    return blend;
} 