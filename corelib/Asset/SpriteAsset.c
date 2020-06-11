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

SpriteAsset *Sprite_New(const char *name) {
    SpriteAsset *asset = DE_NEW(SpriteAsset, 1); 
    asset->name  = DE_NEWSTRING(name);
    asset->delay = 100.0f;
    asset->current = 0;
    asset->count   = 1;
    asset->texture = NULL;
    asset->clock   = SDL_GetTicks();
    asset->flags   = AnimActive;

    return asset;
}

/////////////////////////////////////////////////
// Setters/Getters
////////////////////////////////////////////////

/*
 * Size
 */
Vector2 Sprite_GetSize(SpriteAsset *texture) {
    PTR_NULLCHECK(texture, ((Vector2){0,0}));

    int32_t x, y;

    if(SDL_QueryTexture(texture->texture[texture->current], NULL, NULL, &x, &y) > 0) {
        DE_REPORT("Cannot get texture size of texture: %s : %s", texture->name, SDL_GetError());
    }

    return (Vector2){(float)x, (float)y};
}

/*
 * Animation loop
 */
void Sprite_SetAnimLoop(SpriteAsset *texture, bool loop) {
    PTR_NULLCHECK(texture,);
    
    int32_t flags = 0;

    if(texture->flags & AnimActive) { flags |= AnimActive; }
    if(loop) { flags |= AnimLoop; }

    texture->flags = flags;
}

bool Sprite_GetAnimLoop(SpriteAsset *texture) {
    PTR_NULLCHECK(texture, false);
    return (bool)(texture->flags & AnimLoop);
}

/*
 * Animation status
 */
void Sprite_SetAnimActive(SpriteAsset *texture, bool active) {
    PTR_NULLCHECK(texture,);

    int32_t flags = 0;

    if(active) { flags |= AnimActive; }
    if(texture->flags & AnimLoop) { flags |= AnimLoop; }

    texture->flags = flags;
}

bool Sprite_GetAnimActive(SpriteAsset *texture) {
    PTR_NULLCHECK(texture, false);
    return (bool)(texture->flags & AnimActive);
}

/*
 * Animation delay
 */
void Sprite_SetAnimDelay(SpriteAsset *texture, float ms) {
    PTR_NULLCHECK(texture,);
    texture->delay = ms;
}

float Sprite_GetAnimDelay(SpriteAsset *texture) {
    PTR_NULLCHECK(texture, -1.0f);
    return texture->delay;
}

#undef PTR_NULLCHECK