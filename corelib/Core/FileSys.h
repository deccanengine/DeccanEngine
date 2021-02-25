/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "../Config.h"

SDL_RWops *DE_FSLocateFile(const char *file_name, bool is_binary);
const char *DE_FSGetFileContent(SDL_RWops *file);
const char *DE_FSGetFileExtension(const char *file_name);
