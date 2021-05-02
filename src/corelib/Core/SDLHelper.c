/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "SDLHelper.h"

DE_IMPL void deccan_sdl_init(void) {
    int flags = SDL_INIT_VIDEO;
    if (SDL_Init(flags) != 0) {
        DE_FATAL("Could not initialize SDL2: %s", SDL_GetError());
    }

    if (TTF_Init() != 0) {
        DE_FATAL("Could not initialize SDL2_ttf: %s", TTF_GetError());
    }
}
