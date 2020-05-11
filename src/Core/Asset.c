/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Core.h>
#include <Deccan/Renderer.h>

static TextureAsset *_asset_textures = NULL;
static FontAsset *_asset_fonts = NULL;

void Asset_LoadTexture(const char *name, const char *path) {
    SDL_Surface *img;
    SDL_Texture *tex;

    img = IMG_Load(path);
    if(img == NULL) {
        DE_report("Cannot load image: %s: %s", path, IMG_GetError());
    }

#ifdef DECCAN_RENDERER_SDL
    tex = SDL_CreateTextureFromSurface(Renderer_GetRenderer(), img);
#else

#endif
    SDL_FreeSurface(img);

    if(tex == NULL) {
        DE_report("Cannot create texture: %s: %s", name, SDL_GetError());
    }

    stbds_shput(_asset_textures, name, tex);
}

void Asset_LoadFont(const char *name, const char *path) {
    TTF_Font *font;

    font = TTF_OpenFont(path, 20);
    if(font == NULL) {
        DE_report("Cannot load font: %s: %s", path, TTF_GetError());
    }

    stbds_shput(_asset_fonts, name, font);
}

SDL_Texture *Asset_GetTexture(const char *name) {
    for(int i=0; i<stbds_shlen(_asset_textures); i++) {
        if(!strcmp(name, _asset_textures[i].key)) {
            return _asset_textures[i].value;
        }
    }
    DE_report("Texture not found: %s", name);
}

TTF_Font *Asset_GetFont(const char *name) {
    for(int i=0; i<stbds_shlen(_asset_fonts); i++) {
        if(!strcmp(name, _asset_fonts[i].key)) {
            return _asset_fonts[i].value;
        }
    }
    DE_report("Font not found: %s", name);
}