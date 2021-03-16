/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct DeccanTexture {
    int32_t width, height;
    int pixel_format;
    sg_image image;
} DeccanTexture;

typedef struct DeccanSurface {
    const void *data;
    size_t size;
    int format;
} DeccanSurface;

/////////////////////////////////////////////////
// Texture
////////////////////////////////////////////////

DE_API void DE_TextureCreateFromMem(
    DeccanTexture *texture, int32_t width, int32_t height, size_t count, DeccanSurface *surfaces);
DE_API void DE_TextureCreateBlankRGBA(DeccanTexture *texture, int32_t width, int32_t height, uint32_t color);
DE_API void DE_TextureDestroy(DeccanTexture *texture);
