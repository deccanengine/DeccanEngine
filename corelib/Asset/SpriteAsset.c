/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "SpriteAsset.h"

#define PTR_NULLCHECK(x,y) if(!x) { return y; }

/////////////////////////////////////////////////
// Constructor/Destructor
////////////////////////////////////////////////

DeccanSpriteAsset *DE_SpriteNew(const char *name) {
    DeccanSpriteAsset *asset = DE_Alloc(sizeof(DeccanSpriteAsset), 1);
    asset->name  = DE_StringNew(name);
    asset->delay = 100.0f;
    asset->current = 0;
    asset->count   = 1;
    asset->texture = NULL;
    asset->clock   = SDL_GetTicks();
    asset->flags   = DECCAN_ANIMFLAG_ACTIVE;

    return asset;
}

void DE_SpriteDelete(DeccanSpriteAsset *asset) {
	if(!asset) return;

	for(int i=0; i<stbds_arrlen(asset->texture); i++) {
		if(asset->texture[i])
			SDL_DestroyTexture(asset->texture[i]);
	}

    DE_Free(asset->name);
    DE_Free(asset);
}

/////////////////////////////////////////////////
// Setters/Getters
////////////////////////////////////////////////

/*
 * Size
 */
void DE_SpriteGetSize(DeccanSpriteAsset *texture, vec2 size) {
    int32_t x, y;
    size[0] = 0;
    size[1] = 0;

    PTR_NULLCHECK(texture,);

    if(SDL_QueryTexture(texture->texture[texture->current], NULL, NULL, &x, &y) > 0) {
        DE_WARN("Cannot get texture size of texture: %s : %s", texture->name, SDL_GetError());
    }

    size[0] = (float)x;
    size[1] = (float)y;
}

/*
 * Animation loop
 */
void DE_SpriteSetAnimLoop(DeccanSpriteAsset *texture, bool loop) {
    PTR_NULLCHECK(texture,);

    int32_t flags = 0;

    if(texture->flags & DECCAN_ANIMFLAG_ACTIVE) { flags |= DECCAN_ANIMFLAG_ACTIVE; }
    if(loop) { flags |= DECCAN_ANIMFLAG_LOOP; }

    texture->flags = flags;
}

bool DE_SpriteGetAnimLoop(DeccanSpriteAsset *texture) {
    PTR_NULLCHECK(texture, false);
    return (bool)(texture->flags & DECCAN_ANIMFLAG_LOOP);
}

/*
 * Animation status
 */
void DE_SpriteSetAnimActive(DeccanSpriteAsset *texture, bool active) {
    PTR_NULLCHECK(texture,);

    int32_t flags = 0;

    if(active) { flags |= DECCAN_ANIMFLAG_ACTIVE; }
    if(texture->flags & DECCAN_ANIMFLAG_LOOP) { flags |= DECCAN_ANIMFLAG_LOOP; }

    texture->flags = flags;
}

bool DE_SpriteGetAnimActive(DeccanSpriteAsset *texture) {
    PTR_NULLCHECK(texture, false);
    return (bool)(texture->flags & DECCAN_ANIMFLAG_ACTIVE);
}

/*
 * Animation delay
 */
void DE_SpriteSetAnimDelay(DeccanSpriteAsset *texture, float ms) {
    PTR_NULLCHECK(texture,);
    texture->delay = ms;
}

float DE_SpriteGetAnimDelay(DeccanSpriteAsset *texture) {
    PTR_NULLCHECK(texture, -1.0f);
    return texture->delay;
}

#undef PTR_NULLCHECK
