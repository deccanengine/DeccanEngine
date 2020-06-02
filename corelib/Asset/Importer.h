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

int32_t Asset_GetSpriteIndex(const char *name);
SpriteAsset *Asset_LoadSprite(const char *name, const char *path);
SpriteAsset *Asset_LoadAnimatedSprite(const char *name, const char *path, ...);
SpriteAsset *Asset_GetSprite(const char *name);

/////////////////////////////////////////////////
// Font importer
////////////////////////////////////////////////

int32_t Asset_GetFontIndex(const char *name);
FontAsset *Asset_NewFontAsset(const char *name);
FontAsset *Asset_LoadFont(const char *name, const char *path);
FontAsset *Asset_GetFont(const char *name);