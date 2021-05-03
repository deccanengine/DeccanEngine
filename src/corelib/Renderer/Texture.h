/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "../Core/Utils.h"

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct deccan_texture_t {
    int32_t width, height;
    int pixel_format;
    sg_image image;
} deccan_texture_t;

typedef struct deccan_surface_t {
    const void *data;
    size_t size;
    int format;
} deccan_surface_t;

////////////////////////////////////////////////////////////////////////////////
// Texture
////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_texture_create_from_mem(
    deccan_texture_t *texture, int32_t width, int32_t height, size_t count, deccan_surface_t *surfaces);
DE_API void deccan_texture_create_blank_r_g_b_a(deccan_texture_t *texture, int32_t width, int32_t height, uint32_t color);
DE_API void deccan_texture_destroy(deccan_texture_t *texture);
