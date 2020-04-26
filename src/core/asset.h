/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "core.h"

void DE_Asset_load_texture(const char *name, const char *path);
SDL_Texture *DE_Asset_get_texture(const char *name);

#ifdef __STDC__

    typedef struct DE_Asset {
        void (*load_texture)(const char *name, const char *path);
        SDL_Texture* (*get_texture)(const char *name);
    } DE_Asset;

    static DE_Asset Deccan_Asset = {
        DE_Asset_load_texture,
        DE_Asset_get_texture
    };

#elif __cplusplus

#endif