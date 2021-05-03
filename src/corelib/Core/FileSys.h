/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "../Config.h"

////////////////////////////////////////////////////////////////////////////////
// File actions
////////////////////////////////////////////////////////////////////////////////

DE_API SDL_RWops *deccan_fs_locate_file(const char *file_name, bool is_binary);
DE_API const char *deccan_fs_get_file_content(SDL_RWops *file);
DE_API const char *deccan_fs_get_file_extension(const char *file_name);
