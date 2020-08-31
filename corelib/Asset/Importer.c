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
		SpriteAsset *value;
	} *textures;
    struct {
		const char *key;
		FontAsset *value;
	} *fonts;
} Asset_Info = {
    .textures = NULL,
    .fonts = NULL
};

/////////////////////////////////////////////////
// SpriteAsset
////////////////////////////////////////////////

int32_t Asset_GetSpriteIndex(const char *name) {
    return stbds_shgeti(Asset_Info.textures, name);
}

RawTexture *LoadSprite(const char *path) {
    SDL_Surface *img;
    SDL_Texture *tex;

	int32_t width, height, fmt = STBI_rgb_alpha;
	unsigned char *data;

	/* We dont need to collect the number of channels
	 * Just ask for 4 channels here. If alpha is absent
	 * stb_image will handle it. */
	data = stbi_load(path, &width, &height, NULL, fmt);
	if(data == NULL) {
		DE_REPORT("Cannot load image: %s\n", path);
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
		DE_REPORT("Cannot process image: %s\n", path);
		stbi_image_free(data);
	}

	tex = SDL_CreateTextureFromSurface(Renderer_GetRenderer(), img);

    SDL_FreeSurface(img);
	stbi_image_free(data);

    return tex;
}

SpriteAsset *Asset_LoadSprite(const char *name, const char *path) {
    SpriteAsset *asset = NULL;
    RawTexture *tex = LoadSprite(path);

    if(tex == NULL) {
        DE_REPORT("Cannot create texture: %s: %s", name, SDL_GetError());
        return asset;
    }

    asset = Asset_GetSprite(name);
	if(asset) {
        /* Found the texture */
        stbds_arrput(asset->texture, tex);
        asset->count++;
    }
    else {
        /* Create new texture */
        asset = Sprite_New(name);
        stbds_arrput(asset->texture, tex);
        stbds_shput(Asset_Info.textures, asset->name, asset);
    }

    return asset;
}

SpriteAsset *Asset_LoadAnimatedSprite(const char *name, const char *path, ...) {
    va_list args;
    SpriteAsset *asset;

    va_start(args, path);

    char *this = (char*)path; /* Current path */

    do {
        asset = Asset_LoadSprite(name, this); /* Load the current frame */
        this  = va_arg(args, char *);         /* Next frame path */
    } while(this != NULL);
    va_end(args);

    return asset;
}

SpriteAsset *Asset_GetSprite(const char *name) {
	return stbds_shget(Asset_Info.textures, name);
}

/////////////////////////////////////////////////
// FontAsset
////////////////////////////////////////////////

int32_t Asset_GetFontIndex(const char *name) {
    return stbds_shgeti(Asset_Info.fonts, name);
}

FontAsset *Asset_LoadFont(const char *name, const char *path) {
    FontAsset *asset = NULL;
    TTF_Font *font;

    font = TTF_OpenFont(path, 20);
    if(font == NULL) {
        DE_REPORT("Cannot load font: %s: %s", path, TTF_GetError());
        return asset;
    }

    asset = Asset_GetFont(name);
    if(asset) {
		/* First dellocate the existsing font and then replace with new one */
		TTF_CloseFont(asset->font);
        asset->font = font;
    }
    else {
        asset = Font_New(name);
        asset->font = font;
        stbds_shput(Asset_Info.fonts, asset->name, asset);
    }

    return asset;
}

FontAsset *Asset_GetFont(const char *name) {
    return stbds_shget(Asset_Info.fonts, name);
}
