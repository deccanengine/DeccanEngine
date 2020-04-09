#include "renderer.h"

void deccan_clear_screen(deccan_color color) {
    deccan_set_render_color(color);
    SDL_RenderClear(deccan_get_global_engine()->renderer);
}

void deccan_set_render_color(deccan_color color) {
    SDL_SetRenderDrawColor(deccan_get_global_engine()->renderer, color.r, color.g, color.b, color.a);
}