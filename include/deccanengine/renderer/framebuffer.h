/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct deccan_framebuffer_info_t {
    vec2s dim;
} deccan_framebuffer_info_t;

typedef struct deccan_framebuffer_t {
    deccan_framebuffer_info_t info;
    sg_image color_img, depth_img;
    sg_pass pass;
} deccan_framebuffer_t;

////////////////////////////////////////////////////////////////////////////////
// Framebuffer
////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_framebuffer_create(deccan_framebuffer_t *fb);
DE_API void deccan_framebuffer_destroy(deccan_framebuffer_t *fb);
DE_API void deccan_framebuffer_update(deccan_framebuffer_t *fb);
