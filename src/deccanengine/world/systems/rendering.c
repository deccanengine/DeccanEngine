/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <deccanengine/world/flecs.h>
#include <deccanengine/renderer/render_types.h>
#include <deccanengine/renderer/generic_pipeline.h>
#include <deccanengine/world/components/transform.h>
#include <deccanengine/world/components/drawable_geometry.h>
#include <deccanengine/world/components/drawable_sprite.h>
#include <deccanengine/core/asset/asset_manager.h>
#include <deccanengine/core/maths.h>

////////////////////////////////////////////////////////////////////////////////
// Rendering systems
////////////////////////////////////////////////////////////////////////////////

DE_PRIV void WorldSpriteRendering(deccan_flecs_iter_t *it) {
    deccan_comp_transform_t *transform = deccan_flecs_iter_column(it, "Transform", 1);
    deccan_comp_drawable_sprite_t *sprrender = deccan_flecs_iter_column(it, "DrawableSprite", 2);

    for (int i = 0; i < it->count; i++) {
        mat4s transmat = deccan_mat4_compose(transform->position, transform->scale, transform->rotation);
        deccan_geometry_t *quad = deccan_asset_get_raw(deccan_asset_get("geometry", "quad"));

        deccan_draw_action_t action;
        action.geometry = quad;
        action.transform = transmat;
        action.material = &sprrender[i].material;
        action.texture = sprrender[i].texture;

        deccan_generic_pipeline_draw(action);
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_PRIV void WorldArbitaryGeometryRendering(deccan_flecs_iter_t *it) {
    deccan_comp_transform_t *transform = deccan_flecs_iter_column(it, "Transform", 1);
    deccan_comp_drawable_geometry_t *arbrender = deccan_flecs_iter_column(it, "DrawableGeometry", 2);

    for (int i = 0; i < it->count; i++) {
        mat4s transmat = deccan_mat4_compose(transform->position, transform->scale, transform->rotation);

        deccan_draw_action_t action;
        action.geometry = &arbrender[i].geometry;
        action.transform = transmat;
        action.material = &arbrender[i].material;
        action.texture = arbrender[i].texture;

        deccan_generic_pipeline_draw(action);
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void system_init_rendering(void) {
    deccan_flecs_register_system(WorldSpriteRendering, "DrawableSpriteRendering", "Transform, DrawableSprite", EcsOnUpdate);

    deccan_flecs_register_system(WorldArbitaryGeometryRendering, "DrawableGeometryRendering", "Transform, DrawableGeometry", EcsOnUpdate);
}
