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

DE_API int32_t DE_AssetGetSpriteIndex(const char *name);
DE_API DeccanSpriteAsset *DE_AssetLoadSprite(const char *name, const char *path);
DE_API DeccanSpriteAsset *DE_AssetLoadAnimatedSprite(const char *name, const char *path, ...);
DE_API DeccanSpriteAsset *DE_AssetGetSprite(const char *name);

/////////////////////////////////////////////////
// Font importer
////////////////////////////////////////////////

DE_API int32_t DE_AssetGetFontIndex(const char *name);
DE_API DeccanFontAsset *DE_AssetNewDeccanFontAsset(const char *name);
DE_API DeccanFontAsset *DE_AssetLoadFont(const char *name, const char *path);
DE_API DeccanFontAsset *DE_AssetGetFont(const char *name);
