#include "renderer.h"

void _priv_Renderer_clear(Deccan_Color color) {
    Deccan_Renderer.set_color(color);
    SDL_RenderClear(Deccan_Core.get_global_engine()->renderer);
}

void _priv_Renderer_set_color(Deccan_Color color) {
    SDL_SetRenderDrawColor(Deccan_Core.get_global_engine()->renderer, color.r, color.g, color.b, color.a);
}