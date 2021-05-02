/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct DeccanFramebufferInfo {
    vec2s dim;
} DeccanFramebufferInfo;

typedef struct DeccanFramebuffer {
    DeccanFramebufferInfo info;
    sg_image color_img, depth_img;
    sg_pass pass;
} DeccanFramebuffer;

////////////////////////////////////////////////////////////////////////////////
// Framebuffer
////////////////////////////////////////////////////////////////////////////////

DE_API void DE_FramebufferCreate(DeccanFramebuffer *fb);
DE_API void DE_FramebufferDestroy(DeccanFramebuffer *fb);
DE_API void DE_FramebufferUpdate(DeccanFramebuffer *fb);
