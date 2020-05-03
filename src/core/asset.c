/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "asset.h"

void DE_Asset_load_texture(const char *name, const char *path) {
    SDL_Surface *img;
    SDL_Texture *tex;

    img = IMG_Load(path);
    if(img == NULL) {
        DE_report("Cannot load image: %s: %s", path, IMG_GetError());
    }

#ifdef DECCAN_RENDERER_SDL
    tex = SDL_CreateTextureFromSurface(DE_Core_get_global_engine()->renderer, img);
#else

#endif
    SDL_FreeSurface(img);

    if(tex == NULL) {
        DE_report("Cannot create texture: %s: %s", name, SDL_GetError());
    }

    stbds_shput(DE_Core_get_global_engine()->textures, name, tex);
}

SDL_Texture *DE_Asset_get_texture(const char *name) {
    DE_Info *info = DE_Core_get_global_engine();
    for(int i=0; i<stbds_shlen(info->textures); i++) {
        if(!strcmp(name, info->textures[i].key)) {
            return info->textures[i].value;
        }
    }
    DE_report("Texture not found: %s", name);
}