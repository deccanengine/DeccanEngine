/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include <deccanengine/config.h>
#include <deccanengine/renderer/texture.h>

////////////////////////////////////////////////////////////////////////////////
// Sprite asset
////////////////////////////////////////////////////////////////////////////////

void *sprite_asset_create(const unsigned char *mem, size_t size);
bool sprite_asset_destroy(void *asset);
