/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "../Math/Vector2.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

typedef enum {
    AnimActive = 1,
    AnimLoop = 2
} AnimFlag;

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct SpriteAsset {
    const char *name;
    RawTexture **texture;
    uint32_t count;
    uint32_t current;
    float delay;
    float clock;
    AnimFlag flags;
} SpriteAsset;

// To do: destructor

/////////////////////////////////////////////////
// Constructor/Destructor
////////////////////////////////////////////////

SpriteAsset *Sprite_New(const char *name);

/////////////////////////////////////////////////
// Setters/Getters
////////////////////////////////////////////////

Vector2 Sprite_GetSize(SpriteAsset *texture);

void Sprite_SetAnimLoop(SpriteAsset *texture, bool loop);
bool Sprite_GetAnimLoop(SpriteAsset *texture);

void Sprite_SetAnimActive(SpriteAsset *texture, bool active);
bool Sprite_GetAnimActive(SpriteAsset *texture);

void Sprite_SetAnimDelay(SpriteAsset *texture, float ms);
float Sprite_GetAnimDelay(SpriteAsset *texture);