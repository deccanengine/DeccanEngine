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

typedef struct DeccanGeometry {
    sg_buffer vbuf, ibuf;
    sg_image image;
    mat4s transform;
    float color[4];
    uint16_t index_count;
} DeccanGeometry;
