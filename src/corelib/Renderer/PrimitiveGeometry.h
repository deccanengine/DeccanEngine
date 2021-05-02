/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "RenderTypes.h"

////////////////////////////////////////////////////////////////////////////////
// Geometry resources
////////////////////////////////////////////////////////////////////////////////

DE_API deccan_geometry_t deccan_primitive_create_quad(void);
DE_API deccan_geometry_t deccan_primitive_create_triangle(void);
DE_API deccan_geometry_t deccan_primitive_create_cube(void);
