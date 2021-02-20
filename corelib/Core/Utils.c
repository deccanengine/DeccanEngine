/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Utils.h"

void *DE_Alloc(size_t size, int count) {
    return SDL_malloc(size * count);
}

void *DE_Realloc(void *mem, size_t size) {
    return SDL_realloc(mem, size);
}

void DE_Free(void *mem) {
    if(!mem) return;
    else {
        SDL_free(mem);
        mem = NULL;
    }
}
