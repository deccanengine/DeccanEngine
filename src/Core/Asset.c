/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Core.h>
#include <Deccan/Renderer.h>

static struct {
    TextureAsset **textures;
    FontAsset **fonts;
} Asset_Info = {
    .textures = NULL,
    .fonts = NULL
};

TextureAsset *Asset_NewTextureAsset(const char *name) {
    TextureAsset *asset = DE_NEW(TextureAsset, 1); 
    asset->name  = DE_NEWSTRING(name);
    asset->delay = 100.0f;
    asset->current = 0;
    asset->count   = 1;
    asset->texture = NULL;
    asset->clock   = SDL_GetTicks();

    return asset;
}

int32_t Asset_GetTextureIndex(const char *name) {
    for(int32_t i=0; i<stbds_arrlen(Asset_Info.textures); i++) {
        if(!strcmp(name, Asset_Info.textures[i]->name)) {
            return i;
        }
    }
    return -1;            
}

RawTexture *LoadTexture(const char *path) {
    SDL_Surface *img;
    SDL_Texture *tex;

    img = IMG_Load(path);
    if(img == NULL) {
        DE_REPORT("Cannot load image: %s: %s", path, IMG_GetError());
    }

#ifdef DECCAN_RENDERER_SDL
    tex = SDL_CreateTextureFromSurface(Renderer_GetRenderer(), img);
#else

#endif
    SDL_FreeSurface(img);

    return tex;
}

void Asset_LoadTexture(const char *name, const char *path) {
    RawTexture *tex = LoadTexture(path);
    if(tex == NULL) {
        DE_REPORT("Cannot create texture: %s: %s", name, SDL_GetError());
        return;
    }

    int32_t index = Asset_GetTextureIndex(name);
    if(index != -1) {
        /* Found the texture */
        stbds_arrput(Asset_Info.textures[index]->texture, tex);
        Asset_Info.textures[index]->count++;
    }
    else {
        /* Create new texture */
        TextureAsset *asset = Asset_NewTextureAsset(name);
        stbds_arrput(asset->texture, tex);
        stbds_arrput(Asset_Info.textures, asset);
    }
}

TextureAsset *Asset_GetTexture(const char *name) {
    int index = Asset_GetTextureIndex(name);
    if(index == -1) {
        DE_REPORT("Texture not found: %s", name);
    }
    return Asset_Info.textures[index];    
}

int32_t Asset_GetFontIndex(const char *name) {
    for(int32_t i=0; i<stbds_arrlen(Asset_Info.fonts); i++) {
        if(!strcmp(name, Asset_Info.fonts[i]->name)) {
            return i;
        }
    }
    return -1;
}

FontAsset *Asset_NewFontAsset(const char *name) {
    FontAsset *asset = DE_NEW(FontAsset, 1);
    asset->name = DE_NEWSTRING(name);
    return asset;
}

void Asset_LoadFont(const char *name, const char *path) {
    TTF_Font *font;

    font = TTF_OpenFont(path, 20);
    if(font == NULL) {
        DE_REPORT("Cannot load font: %s: %s", path, TTF_GetError());
    }

    int32_t index = Asset_GetFontIndex(name);
    if(index != -1) {
        Asset_Info.fonts[index]->font = font;
    }
    else {
        FontAsset *asset = Asset_NewFontAsset(name);
        asset->font = font;
        stbds_arrput(Asset_Info.fonts, asset);
    }
}

FontAsset *Asset_GetFont(const char *name) {
    int32_t index = Asset_GetFontIndex(name);
    if(index == -1) {
        DE_REPORT("Font not found: %s", name);
    }
    return Asset_Info.fonts[index];
}