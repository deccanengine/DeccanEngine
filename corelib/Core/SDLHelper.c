#include "SDLHelper.h"

void DE_SDLInit(void) {
    int flags = SDL_INIT_VIDEO;
    if (SDL_Init(flags) != 0) {
        DE_FATAL("Could not initialize SDL2: %s", SDL_GetError());
    }

    if (TTF_Init() != 0) {
        DE_FATAL("Could not initialize SDL2_ttf: %s", TTF_GetError());
    }
}
