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

/* Raw texture structure */
typedef SDL_Texture DeccanRawTexture;

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

typedef enum { DECCAN_ANIMFLAG_ACTIVE = 1, DECCAN_ANIMFLAG_LOOP = 2 } DeccanSpriteAnimFlag;

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

DE_API DeccanSpriteAsset *DE_SpriteNew(const char *name);
DE_API void DE_SpriteDelete(DeccanSpriteAsset *asset);

/////////////////////////////////////////////////
// Setters/Getters
////////////////////////////////////////////////

DE_API void DE_SpriteGetSize(DeccanSpriteAsset *texture, vec2 size);

DE_API void DE_SpriteSetAnimLoop(DeccanSpriteAsset *texture, bool loop);
DE_API bool DE_SpriteGetAnimLoop(DeccanSpriteAsset *texture);

DE_API void DE_SpriteSetAnimActive(DeccanSpriteAsset *texture, bool active);
DE_API bool DE_SpriteGetAnimActive(DeccanSpriteAsset *texture);

DE_API void DE_SpriteSetAnimDelay(DeccanSpriteAsset *texture, float ms);
DE_API float DE_SpriteGetAnimDelay(DeccanSpriteAsset *texture);
