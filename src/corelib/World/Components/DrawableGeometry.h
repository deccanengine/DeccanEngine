/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../Config.h"
#include "../../Renderer/RenderTypes.h"
#include "../../Renderer/Texture.h"

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct deccan_comp_drawable_geometry_t {
    deccan_geometry_t geometry;
    deccan_texture_t *texture;
    deccan_material_t material;
} deccan_comp_drawable_geometry_t;
