#include "renderer.h"

void deccan_renderer_clear(deccan_Color color) {
    deccan_renderer_set_color(color);
    SDL_RenderClear(deccan_get_global_engine()->renderer);
}

void deccan_renderer_set_color(deccan_Color color) {
    SDL_SetRenderDrawColor(deccan_get_global_engine()->renderer, color.r, color.g, color.b, color.a);
}