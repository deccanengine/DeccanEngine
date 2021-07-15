/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../config.h"
#include "../object.h"

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef enum deccan_rigid_body_type_t {
    DECCAN_RIGID_BODY_DYNAMIC,
    DECCAN_RIGID_BODY_KINEMATIC,
    DECCAN_RIGID_BODY_STATIC
} deccan_rigid_body_type_t;

typedef struct deccan_comp_rigid_body_t {
    deccan_rigid_body_type_t type;
    double mass;
    double moment;

    /* Private */
    cpBody *_body;
} deccan_comp_rigid_body_t;

////////////////////////////////////////////////////////////////////////////////
// Force and Impulse
////////////////////////////////////////////////////////////////////////////////

void deccan_comp_rigid_body_apply_force_world(deccan_object_t obj, vec2s force, vec2s point);
void deccan_comp_rigid_body_apply_force_local(deccan_object_t obj, vec2s force, vec2s point);

void deccan_comp_rigid_body_apply_impulse_world(deccan_object_t obj, vec2s force, vec2s point);
void deccan_comp_rigid_body_apply_impulse_local(deccan_object_t obj, vec2s force, vec2s point);
