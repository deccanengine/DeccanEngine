/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include <deccanengine/config.h>
#include <deccanengine/renderer/render_types.h>

////////////////////////////////////////////////////////////////////////////////
// Geometry resources
////////////////////////////////////////////////////////////////////////////////

deccan_geometry_t *primitive_create_quad(void);
deccan_geometry_t *primitive_create_triangle(void);
deccan_geometry_t *primitive_create_cube(void);
