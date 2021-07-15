/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "color.h"
#include "texture.h"

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct deccan_geometry_t {
    sg_buffer vbuf, ibuf;
    uint16_t index_count;
} deccan_geometry_t;

typedef struct deccan_material_t {
    deccan_color_t color;
} deccan_material_t;

typedef struct deccan_draw_action_t {
    deccan_geometry_t *geometry;
    deccan_material_t *material;
    deccan_texture_t *texture; // TODO: array of textures
    mat4s transform;
} deccan_draw_action_t;
