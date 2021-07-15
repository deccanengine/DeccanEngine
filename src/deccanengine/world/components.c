/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <deccanengine/world/components/transform.h>
#include <deccanengine/world/components/drawable_geometry.h>
#include <deccanengine/world/components/drawable_sprite.h>
#include <deccanengine/world/components/rigid_body.h>
#include <deccanengine/world/components/collider.h>
#include <deccanengine/world/components/legacy_collider.h>
#include "components.h"

////////////////////////////////////////////////////////////////////////////////
// Registrar
////////////////////////////////////////////////////////////////////////////////

void components_register_all(void) {
    deccan_flecs_register_component("Transform", sizeof(deccan_comp_transform_t), ECS_ALIGNOF(deccan_comp_transform_t));

    deccan_flecs_register_component("Collider", sizeof(deccan_comp_collider_t), ECS_ALIGNOF(deccan_comp_collider_t));

    deccan_flecs_register_component("DrawableGeometry", sizeof(deccan_comp_drawable_geometry_t),
        ECS_ALIGNOF(deccan_comp_drawable_geometry_t));

    deccan_flecs_register_component("DrawableSprite", sizeof(deccan_comp_drawable_sprite_t),
        ECS_ALIGNOF(deccan_comp_drawable_sprite_t));

    deccan_flecs_register_component("RigidBody", sizeof(deccan_comp_rigid_body_t),
        ECS_ALIGNOF(deccan_comp_rigid_body_t));

    deccan_flecs_register_component("BoxCollider", sizeof(deccan_comp_box_collider_t),
        ECS_ALIGNOF(deccan_comp_box_collider_t));
}
