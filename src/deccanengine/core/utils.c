/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <deccanengine/core/utils.h>

DE_IMPL void *deccan_alloc(size_t size, int count) {
    return SDL_malloc(size * count);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void *deccan_realloc(void *mem, size_t size) {
    return SDL_realloc(mem, size);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_free(void *mem) {
    if (!mem)
        return;
    else {
        SDL_free(mem);
        mem = NULL;
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL zpl_allocator deccan_zpl_allocator(void) {
    // TODO: make allocator
    return zpl_heap_allocator();
}
