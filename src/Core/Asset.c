/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Asset.h>

void DE_Asset_LoadTexture(const char *name, const char *path) {
    SDL_Surface *img;
    SDL_Texture *tex;

    img = IMG_Load(path);
    if(img == NULL) {
        DE_report("Cannot load image: %s: %s", path, IMG_GetError());
    }

#ifdef DECCAN_RENDERER_SDL
    tex = SDL_CreateTextureFromSurface(DE_Core_GetGlobalInfo()->renderer, img);
#else

#endif
    SDL_FreeSurface(img);

    if(tex == NULL) {
        DE_report("Cannot create texture: %s: %s", name, SDL_GetError());
    }

    stbds_shput(DE_Core_GetGlobalInfo()->textures, name, tex);
}

void DE_Asset_LoadFont(const char *name, const char *path) {
    TTF_Font *font;

    font = TTF_OpenFont(path, 20);
    if(font == NULL) {
        DE_report("Cannot load font: %s: %s", path, TTF_GetError());
    }

    stbds_shput(DE_Core_GetGlobalInfo()->fonts, name, font);
}

SDL_Texture *DE_Asset_GetTexture(const char *name) {
    DE_GameInfo *info = DE_Core_GetGlobalInfo();
    for(int i=0; i<stbds_shlen(info->textures); i++) {
        if(!strcmp(name, info->textures[i].key)) {
            return info->textures[i].value;
        }
    }
    DE_report("Texture not found: %s", name);
}

TTF_Font *DE_Asset_GetFont(const char *name) {
    DE_GameInfo *info = DE_Core_GetGlobalInfo();
    for(int i=0; i<stbds_shlen(info->fonts); i++) {
        if(!strcmp(name, info->fonts[i].key)) {
            return info->fonts[i].value;
        }
    }
    DE_report("Font not found: %s", name);
}