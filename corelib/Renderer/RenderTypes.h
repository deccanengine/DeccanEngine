/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "Color.h"

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct DeccanGeometry {
    sg_buffer vbuf, ibuf;
    uint16_t index_count;
} DeccanGeometry;

typedef struct DeccanMaterial {
    sg_image image;
    DeccanColor color;
} DeccanMaterial;

typedef struct DeccanDrawAction {
    DeccanGeometry *geometry;
    DeccanMaterial *material;
    mat4s transform;
} DeccanDrawAction;
