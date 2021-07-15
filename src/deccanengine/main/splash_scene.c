/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <deccanengine/core/core.h>
#include <deccanengine/core/timer.h>
#include <deccanengine/core/asset/asset_manager.h>
#include <deccanengine/renderer/color.h>
#include <deccanengine/renderer/renderer.h>
#include <deccanengine/world/world.h>
#include <deccanengine/world/scene_layer.h>
#include <deccanengine/world/camera.h>
#include <deccanengine/world/components/transform.h>
#include <deccanengine/world/components/drawable_sprite.h>

bool fade_signal = false;
deccan_timer_t timer;
deccan_camera_t camera;

DE_PRIV void logo_begin(deccan_object_t this) {
    deccan_object_set_component(this, "Transform", &(deccan_comp_transform_t){
        .position = { .x = 0.0f, .y = 0.0f, .z = 0.0f },
        .scale = { .x = 1.0f, .y = 0.25f, .z = 1.0f },
        .rotation = { .z = 0.0f },
    });

    deccan_object_set_component(this, "DrawableSprite", &(deccan_comp_drawable_sprite_t){
        .texture = deccan_asset_get_raw(deccan_asset_get("texture", "_logo_internal")),
        .material = {
            .color = { 255, 255, 255, 255 },
        },
    });
}

DE_PRIV void logo_step(deccan_object_t this) {
    deccan_comp_drawable_sprite_t *drspr = deccan_object_get_component(this, "DrawableSprite");

    if (fade_signal) {
        drspr->material.color.a -= 3;
        if (drspr->material.color.a <= 0) {
            fade_signal = false;
            deccan_world_remove_scene();
        }
    }
}

DE_PRIV void scene_begin(deccan_scene_t *scene) {
    deccan_object_t logo = deccan_object_new_object(&(deccan_object_desc_t){
        .name = "logo show",
        .cb = {
            [DE_OBJECT_ATBEGINNING] = logo_begin,
            [DE_OBJECT_ATSTEP] = logo_step,
        },
    });

    deccan_scene_instantiate_object(scene, NULL, logo);

    deccan_renderer_set_clear_color((vec4s){26.0f / 255.0f, 26.0f / 255.0f, 26.0f / 255.0f, 1.0f});

    deccan_camera_init(&camera, 0.1f, 100.0f);
    vec2s viewport = deccan_core_get_resolution();
    camera.cam.position = (vec3s){0.0f, 0.0f, 1.0f};
    deccan_camera_set_viewport(&camera, viewport);
    deccan_camera_set_ortho(&camera, 1.0f);
    deccan_scene_set_camera(scene, &camera);

    deccan_timer_start(&timer);
}

DE_PRIV void scene_step(deccan_scene_t *scene) {
    DE_UNUSED(scene);

    float time = deccan_timer_get_time(&timer).milliseconds;
    if (time >= 2000.0f) {
        fade_signal = true;
        deccan_timer_stop(&timer);
    }

}

void add_splash_scene(void) {
    deccan_scenelayer_t *scene_mod = deccan_scenelayer_create(&(deccan_scenelayer_desc_t){
        .name = "scene_mod",
        .cb = {
            [DE_SCENE_LAYER_ATBEGINNING] = scene_begin,
            [DE_SCENE_LAYER_ATSTEP] = scene_step,
        },
    });

    deccan_scene_t *scene = deccan_scene_new_scene(&(deccan_scene_desc_t){
        .name = "splash_scene",
        .layers = { scene_mod },
    });

    deccan_world_add_scene(scene, false);
}
