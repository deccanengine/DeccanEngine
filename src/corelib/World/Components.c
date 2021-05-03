/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Components.h"

////////////////////////////////////////////////////////////////////////////////
// Registrar
////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_components_register_all(void) {
    deccan_flecs_register_component("Transform", sizeof(deccan_comp_transform_t), ECS_ALIGNOF(deccan_comp_transform_t));

    deccan_flecs_register_component("Collider", sizeof(deccan_comp_collider_t), ECS_ALIGNOF(deccan_comp_collider_t));

    deccan_flecs_register_component("DrawableGeometry", sizeof(deccan_comp_drawable_geometry_t), 
        ECS_ALIGNOF(deccan_comp_drawable_geometry_t));

    deccan_flecs_register_component("DrawableSprite", sizeof(deccan_comp_drawable_sprite_t), 
        ECS_ALIGNOF(deccan_comp_drawable_sprite_t));
}
