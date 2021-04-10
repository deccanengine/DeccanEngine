/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Utils.h"

DE_IMPL void *DE_Alloc(size_t size, int count) {
    return SDL_malloc(size * count);
}

DE_IMPL void *DE_Realloc(void *mem, size_t size) {
    return SDL_realloc(mem, size);
}

DE_IMPL void DE_Free(void *mem) {
    if (!mem)
        return;
    else {
        SDL_free(mem);
        mem = NULL;
    }
}
