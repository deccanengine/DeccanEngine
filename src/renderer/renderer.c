/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "renderer.h"

void DE_Renderer_clear(DE_Color color) {
    DE_Renderer_set_color(color);
    SDL_RenderClear(DE_Core_get_global_engine()->renderer);
}

void DE_Renderer_set_target(DE_Texture *target) {
    DE_Info *engine = DE_Core_get_global_engine(); 
    if(target == NULL) { target = engine->target; }
    if(SDL_SetRenderTarget(engine->renderer, target) != 0) {
        printf("here?\n");
    }
}

void DE_Renderer_set_color(DE_Color color) {
    SDL_SetRenderDrawColor(DE_Core_get_global_engine()->renderer, color.r, color.g, color.b, color.a);
}

void DE_Renderer_set_pixel_size(DE_Vector2f size) {
    SDL_RenderSetScale(DE_Core_get_global_engine()->renderer, size.x, size.y);
}

void DE_Renderer_set_blend_mode(int blend_mode) {
    if(SDL_SetRenderDrawBlendMode(DE_Core_get_global_engine()->renderer, blend_mode) != 0) {
        DE_report("Cannot set blend mode: %s", SDL_GetError());
    }
}

DE_Texture *DE_Renderer_get_target() {
    return SDL_GetRenderTarget(DE_Core_get_global_engine()->renderer);
}

DE_Color DE_Renderer_get_color() {
    DE_Color color;
    SDL_GetRenderDrawColor(DE_Core_get_global_engine()->renderer, &color.r, &color.g, &color.b, &color.a);
    return color;
}

DE_Vector2f DE_Renderer_get_pixel_size() {
    DE_Vector2f size;
    SDL_RenderGetScale(DE_Core_get_global_engine()->renderer, &size.x, &size.y);
    return size;
}

DE_BlendMode DE_Renderer_get_blend_mode() {
    SDL_BlendMode blend;
    SDL_GetRenderDrawBlendMode(DE_Core_get_global_engine()->renderer, &blend);
    return blend;
} 