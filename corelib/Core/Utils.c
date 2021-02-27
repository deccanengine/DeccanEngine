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

DE_PRIV void *SXAllocFunc(void *ptr, size_t size, uint32_t align, const char *file, const char *func, uint32_t line, void *user_data) {
    DE_UNUSED(align);
    DE_UNUSED(file);
    DE_UNUSED(func);
    DE_UNUSED(line);
    DE_UNUSED(user_data);

    if (size == 0 && ptr != NULL) {
        DE_Free(ptr);
        return NULL;
    }
    else if (ptr == NULL) {
        return DE_Alloc(size, 1);
    }
    else {
        return DE_Realloc(ptr, size);
    }

    return NULL;
}

DE_IMPL sx_alloc *DE_GetSXAlloc() {
    static sx_alloc alloc = { SXAllocFunc , NULL };
    return &alloc;
}
