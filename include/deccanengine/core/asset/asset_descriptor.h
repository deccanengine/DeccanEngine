/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../config.h"

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct asset_callbacks_t {
    void *(*create)(const unsigned char *mem, size_t size);
    bool (*destroy)(void *asset);
} asset_callbacks_t;

typedef struct deccan_asset_descriptor_t {
    const char *key;
    const char **ext; /* Unused for now! */
    bool is_binary;   /* Unused for now! */
    asset_callbacks_t calls;
} deccan_asset_descriptor_t;
