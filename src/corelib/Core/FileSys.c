/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "FileSys.h"
#include "Utils.h"

DE_IMPL SDL_RWops *DE_FSLocateFile(const char *file_name, bool is_binary) {
    SDL_RWops *file = SDL_RWFromFile(file_name, (is_binary ? "rb" : "r"));
    if (file == NULL) {
        DE_ERROR("File '%s' not found: %s", file_name, SDL_GetError());
        return NULL;
    }

    return file;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL const char *DE_FSGetFileContent(SDL_RWops *file) {
    int64_t size = SDL_RWsize(file);

    if (size > 0) {
        char *content = DE_Alloc(sizeof(char), size + 1);
        SDL_RWread(file, content, sizeof(char), size + 1);
        content[size] = '\0';

        return content;
    }

    if (size != 0) {
        DE_ERROR("Cannot seek into RW: %s", SDL_GetError());
    }

    return NULL;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL const char *DE_FSGetFileExtension(const char *file_name) {
    const char *ext = strrchr(file_name, '.');
    if (ext) {
        return ext + 1;
    }

    return NULL;
}
