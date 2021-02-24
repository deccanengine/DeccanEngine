/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once

#include "../Config.h"
#include "Utils.h"
#include "String.h"

typedef struct DeccanAsset {
    const char *key;
    void *value;
} DeccanAsset;

DE_API void DE_AssetLoadAsset(const char *type, const char *name, void *asset);
DE_API void *DE_AssetGetAsset(const char *type, const char *name);
