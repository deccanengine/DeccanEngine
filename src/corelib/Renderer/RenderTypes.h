/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "Color.h"
#include "Texture.h"

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct DeccanGeometry {
    sg_buffer vbuf, ibuf;
    uint16_t index_count;
} DeccanGeometry;

typedef struct DeccanMaterial {
    DeccanColor color;
} DeccanMaterial;

typedef struct DeccanDrawAction {
    DeccanGeometry *geometry;
    DeccanMaterial *material;
    DeccanTexture *texture; // TODO: array of textures
    mat4s transform;
} DeccanDrawAction;
