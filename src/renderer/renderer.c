/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "renderer.h"

void _priv_Renderer_clear(Deccan_Color color) {
    _priv_Renderer_set_color(color);
    SDL_RenderClear(Deccan_Core.get_global_engine()->renderer);
}

void _priv_Renderer_set_color(Deccan_Color color) {
    SDL_SetRenderDrawColor(Deccan_Core.get_global_engine()->renderer, color.r, color.g, color.b, color.a);
}

void _priv_Renderer_set_pixel_size(Deccan_Vector2f size) {
    SDL_RenderSetScale(Deccan_Core.get_global_engine()->renderer, size.x, size.y);
}

Deccan_Color _priv_Renderer_get_color() {
    Deccan_Color color;
    SDL_GetRenderDrawColor(Deccan_Core.get_global_engine()->renderer, &color.r, &color.g, &color.b, &color.a);
    return color;
}

Deccan_Vector2f _priv_Renderer_get_pixel_size() {
    Deccan_Vector2f size;
    SDL_RenderGetScale(Deccan_Core.get_global_engine()->renderer, &size.x, &size.y);
    return size;
}