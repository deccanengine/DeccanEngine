/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../config.h"
#include "../../physics/physics.h"

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct deccan_comp_box_collider_t {
    double width;
    double height;
    double edge_radius;

    /* Private */
    cpShape *_shape;
} deccan_comp_box_collider_t;
