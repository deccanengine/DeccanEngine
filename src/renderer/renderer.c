/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "renderer.h"

void _priv_Renderer_clear(Deccan_Color color) {
    Deccan_Renderer.set_color(color);
    SDL_RenderClear(Deccan_Core.get_global_engine()->renderer);
}

void _priv_Renderer_set_color(Deccan_Color color) {
    SDL_SetRenderDrawColor(Deccan_Core.get_global_engine()->renderer, color.r, color.g, color.b, color.a);
}

void _priv_Renderer_draw_point(Deccan_Vector2i pos, Deccan_Color color) {
    Deccan_Renderer.set_color(color);
    SDL_RenderDrawPoint(Deccan_Core.get_global_engine()->renderer, pos.x, pos.y);
}

void _priv_Renderer_draw_rect(SDL_Rect rect, bool fill, Deccan_Color color) {
    Deccan_Renderer.set_color(color);
    if(fill) { SDL_RenderFillRect(Deccan_Core.get_global_engine()->renderer, &rect); }
    else { SDL_RenderDrawRect(Deccan_Core.get_global_engine()->renderer, &rect); }
}
