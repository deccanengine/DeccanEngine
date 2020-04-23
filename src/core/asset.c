/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "asset.h"

void _priv_Asset_load_texture(const char *name, const char *path) {
    SDL_Surface *img;
    SDL_Texture *tex;

    img = IMG_Load(path);
    if(img == NULL) {
        Deccan_Log.report("Cannot load image: %s: %s", path, IMG_GetError());
    }

    tex = SDL_CreateTextureFromSurface(Deccan_Core.get_global_engine()->renderer, img);
    SDL_FreeSurface(img);

    if(tex == NULL) {
        Deccan_Log.report("Cannot create texture: %s: %s", name, SDL_GetError());
    }

    stbds_shput(Deccan_Core.get_global_engine()->textures, name, tex);
}

SDL_Texture *_priv_Asset_get_texture(const char *name) {
    Deccan_Info *info = Deccan_Core.get_global_engine();
    for(int i=0; i<stbds_shlen(info->textures); i++) {
        if(!strcmp(name, info->textures[i].key)) {
            return info->textures[i].value;
        }
    }
    Deccan_Log.report("Texture not found: %s", name);
}