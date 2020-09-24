#include "Memory.h"

void *DE_Mem_New(size_t size, int count) {
    return SDL_malloc(size * count);
}

void *DE_Mem_Alloc(size_t size, int count) {
    return SDL_calloc(count, size);
}

void *DE_Mem_Realloc(void *mem, size_t size) {
    return SDL_realloc(mem, size);
}

void DE_Mem_Delete(void *mem) {
    if(!mem) return;
    else {
        SDL_free(mem);
        mem = NULL;
    }
}

char *DE_String_New(const char *source) {
    size_t len = strlen(source);
	char *string = DE_Mem_New(sizeof(char), len + 1);
    strncpy(string, source, len);
	string[len] = '\0';
    return string;
}
