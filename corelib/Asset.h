/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once

#include "Config.h"

typedef struct DeccanAsset {
    const char *key;
    void *value;
} DeccanAsset;

void  DE_Asset_LoadAsset(const char *type, const char *name, void *asset);
void* DE_Asset_GetAsset(const char *type, const char *name);
