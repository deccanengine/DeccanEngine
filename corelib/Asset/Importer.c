/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "../Core.h"
#include "../Renderer/Renderer.h"

static struct {
    SpriteAsset **textures;
    FontAsset **fonts;
} Asset_Info = {
    .textures = NULL,
    .fonts = NULL
};

/////////////////////////////////////////////////
// SpriteAsset
////////////////////////////////////////////////

int32_t Asset_GetSpriteIndex(const char *name) {
    for(int32_t i=0; i<stbds_arrlen(Asset_Info.textures); i++) {
        if(!strcmp(name, Asset_Info.textures[i]->name)) {
            return i;
        }
    }
    return -1;            
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

    int32_t index = Asset_GetSpriteIndex(name);
    if(index != -1) {
        /* Found the texture */
        asset = Asset_Info.textures[index];

        stbds_arrput(asset->texture, tex);
        asset->count++;
    }
    else {
        /* Create new texture */
        asset = Sprite_New(name);
        stbds_arrput(asset->texture, tex);
        stbds_arrput(Asset_Info.textures, asset);
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
    int index = Asset_GetSpriteIndex(name);
    if(index == -1) {
        DE_REPORT("Sprite not found: %s", name);
    }
    return Asset_Info.textures[index];    
}

/////////////////////////////////////////////////
// FontAsset
////////////////////////////////////////////////

int32_t Asset_GetFontIndex(const char *name) {
    for(int32_t i=0; i<stbds_arrlen(Asset_Info.fonts); i++) {
        if(!strcmp(name, Asset_Info.fonts[i]->name)) {
            return i;
        }
    }
    return -1;
}

FontAsset *Asset_LoadFont(const char *name, const char *path) {
    FontAsset *asset = NULL;
    TTF_Font *font;

    font = TTF_OpenFont(path, 20);
    if(font == NULL) {
        DE_REPORT("Cannot load font: %s: %s", path, TTF_GetError());
        return asset;
    }

    int32_t index = Asset_GetFontIndex(name);
    if(index != -1) {
        asset = Asset_Info.fonts[index];
        asset->font = font;
    }
    else {
        asset = Font_New(name);
        asset->font = font;
        stbds_arrput(Asset_Info.fonts, asset);
    }

    return asset;
}

FontAsset *Asset_GetFont(const char *name) {
    int32_t index = Asset_GetFontIndex(name);
    if(index == -1) {
        DE_REPORT("Font not found: %s", name);
    }
    return Asset_Info.fonts[index];
}