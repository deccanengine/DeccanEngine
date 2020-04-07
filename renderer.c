#include "renderer.h"

void deccan_clear_screen(deccan_info *engine, deccan_color color) {
    deccan_set_render_color(engine, color);
    SDL_RenderClear(engine->renderer);
}

void deccan_set_render_color(deccan_info *engine, deccan_color color) {
    SDL_SetRenderDrawColor(engine->renderer, color.r, color.g, color.b, color.a);
}