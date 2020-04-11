#include "renderer.h"

void _priv_Renderer_clear(deccan_Color color) {
    deccan_Renderer.set_color(color);
    SDL_RenderClear(deccan_Core.get_global_engine()->renderer);
}

void _priv_Renderer_set_color(deccan_Color color) {
    SDL_SetRenderDrawColor(deccan_Core.get_global_engine()->renderer, color.r, color.g, color.b, color.a);
}