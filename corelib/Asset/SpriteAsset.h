/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "../Core/Utils.h"
#include "../Core/String.h"

/* Texture structure depends on backend */
#ifdef DECCAN_RENDERER_SDL
    typedef SDL_Texture DeccanRawTexture;
#endif

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

typedef enum {
    DECCAN_ANIMFLAG_ACTIVE = 1,
    DECCAN_ANIMFLAG_LOOP   = 2
} DeccanSpriteAnimFlag;

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct DeccanSpriteAsset {
    char *name;
    DeccanRawTexture **texture;
    uint32_t count;
    uint32_t current;
    float delay;
    float clock;
    DeccanSpriteAnimFlag flags;
} DeccanSpriteAsset;

/////////////////////////////////////////////////
// Constructor/Destructor
////////////////////////////////////////////////

DeccanSpriteAsset *DE_SpriteNew(const char *name);
void DE_SpriteDelete(DeccanSpriteAsset *asset);

/////////////////////////////////////////////////
// Setters/Getters
////////////////////////////////////////////////

void DE_SpriteGetSize(DeccanSpriteAsset *texture, vec2 size);

void DE_SpriteSetAnimLoop(DeccanSpriteAsset *texture, bool loop);
bool DE_SpriteGetAnimLoop(DeccanSpriteAsset *texture);

void DE_SpriteSetAnimActive(DeccanSpriteAsset *texture, bool active);
bool DE_SpriteGetAnimActive(DeccanSpriteAsset *texture);

void DE_SpriteSetAnimDelay(DeccanSpriteAsset *texture, float ms);
float DE_SpriteGetAnimDelay(DeccanSpriteAsset *texture);
