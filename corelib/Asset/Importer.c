/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Importer.h"
#include "../Core/Core.h"
#include "../Renderer/Renderer.h"

static struct {
    struct AssetTextureStorage {
		const char *key;
		DeccanSpriteAsset *value;
	} *textures;
    struct {
		const char *key;
		DeccanFontAsset *value;
	} *fonts;
} Asset_Info = {
    .textures = NULL,
    .fonts = NULL
};

/////////////////////////////////////////////////
// DeccanSpriteAsset
////////////////////////////////////////////////

int32_t DE_AssetGetSpriteIndex(const char *name) {
    return stbds_shgeti(Asset_Info.textures, name);
}

DeccanRawTexture *LoadSprite(const char *path) {
    SDL_Surface *img;
    SDL_Texture *tex;

	int32_t width, height, fmt = STBI_rgb_alpha;
	unsigned char *data;

	/* We dont need to collect the number of channels
	 * Just ask for 4 channels here. If alpha is absent
	 * stb_image will handle it. */
	data = stbi_load(path, &width, &height, NULL, fmt);
	if(data == NULL) {
		DE_WARN("Cannot load image: %s", path);
	}

	/* 3-channel calculation is never used but,
	 * let it be here for future */
	int32_t depth, pitch;
	uint32_t pixel_fmt;
	if(fmt == STBI_rgb) {
		depth = 24;
		pitch = 3 * width;
		pixel_fmt = SDL_PIXELFORMAT_RGB24;
	}
	else {
		depth = 32;
		pitch = 4 * width;
		pixel_fmt = SDL_PIXELFORMAT_RGBA32;
	}

	img = SDL_CreateRGBSurfaceWithFormatFrom((void*)data, width, height, depth, pitch, pixel_fmt);
	if(img == NULL) {
		DE_WARN("Cannot process image: %s", path);
		stbi_image_free(data);
	}

	tex = SDL_CreateTextureFromSurface(DE_RendererGetRenderer(), img);

    SDL_FreeSurface(img);
	stbi_image_free(data);

    return tex;
}

DeccanSpriteAsset *DE_AssetLoadSprite(const char *name, const char *path) {
    DeccanSpriteAsset *asset = NULL;
    DeccanRawTexture *tex = LoadSprite(path);

    if(tex == NULL) {
        DE_WARN("Cannot create texture: %s: %s", name, SDL_GetError());
        return asset;
    }

    asset = DE_AssetGetSprite(name);
	if(asset) {
        /* Found the texture */
        stbds_arrput(asset->texture, tex);
        asset->count++;
    }
    else {
        /* Create new texture */
        asset = DE_SpriteNew(name);
        stbds_arrput(asset->texture, tex);
        stbds_shput(Asset_Info.textures, asset->name, asset);
    }

    return asset;
}

DeccanSpriteAsset *DE_AssetLoadAnimatedSprite(const char *name, const char *path, ...) {
    va_list args;
    DeccanSpriteAsset *asset;

    va_start(args, path);

    char *this = (char*)path; /* Current path */

    do {
        asset = DE_AssetLoadSprite(name, this); /* Load the current frame */
        this  = va_arg(args, char *);         /* Next frame path */
    } while(this != NULL);
    va_end(args);

    return asset;
}

DeccanSpriteAsset *DE_AssetGetSprite(const char *name) {
	return stbds_shget(Asset_Info.textures, name);
}

/////////////////////////////////////////////////
// DeccanFontAsset
////////////////////////////////////////////////

int32_t DE_AssetGetFontIndex(const char *name) {
    return stbds_shgeti(Asset_Info.fonts, name);
}

DeccanFontAsset *DE_AssetLoadFont(const char *name, const char *path) {
    DeccanFontAsset *asset = NULL;
    TTF_Font *font;

    font = TTF_OpenFont(path, 20);
    if(font == NULL) {
        DE_WARN("Cannot load font: %s: %s", path, TTF_GetError());
        return asset;
    }

    asset = DE_AssetGetFont(name);
    if(asset) {
		/* First dellocate the existsing font and then replace with new one */
		TTF_CloseFont(asset->font);
        asset->font = font;
    }
    else {
        asset = DE_FontNew(name);
        asset->font = font;
        stbds_shput(Asset_Info.fonts, asset->name, asset);
    }

    return asset;
}

DeccanFontAsset *DE_AssetGetFont(const char *name) {
    return stbds_shget(Asset_Info.fonts, name);
}
