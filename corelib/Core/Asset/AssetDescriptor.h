/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../Config.h"

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct AssetCallbacks {
    void *(*Create)(void *mem, size_t size);
    void (*Destroy)(void *asset);
} AssetCallbacks;

typedef struct DeccanAssetDescriptor {
    const char *key;
    const char **ext; /* Unused for now! */
    bool is_binary;   /* Unused for now! */
    AssetCallbacks calls;
} DeccanAssetDescriptor;
