/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "SpriteAsset.h"
#include "FontAsset.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Sprite importer
////////////////////////////////////////////////

int32_t DE_AssetGetSpriteIndex(const char *name);
DeccanSpriteAsset *DE_AssetLoadSprite(const char *name, const char *path);
DeccanSpriteAsset *DE_AssetLoadAnimatedSprite(const char *name, const char *path, ...);
DeccanSpriteAsset *DE_AssetGetSprite(const char *name);

/////////////////////////////////////////////////
// Font importer
////////////////////////////////////////////////

int32_t DE_AssetGetFontIndex(const char *name);
DeccanFontAsset *DE_AssetNewDeccanFontAsset(const char *name);
DeccanFontAsset *DE_AssetLoadFont(const char *name, const char *path);
DeccanFontAsset *DE_AssetGetFont(const char *name);
