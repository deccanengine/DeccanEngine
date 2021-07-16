/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <deccanengine/physics/physics.h>
#include <deccanengine/world/world.h>
#include <deccanengine/world/scene_layer.h>
#include <deccanengine/core/core.h>
#include "transform_sync.h"

DE_PRIV void iterate_object(deccan_scene_t *scene, void (*func)(deccan_flecs_iter_t *iter)) {
    ecs_query_t *query = ecs_query_new(scene->world, "Transform, RigidBody");
    ecs_iter_t it = ecs_query_iter(query);

    while (ecs_query_next(&it)) {
        for (int i = 0; i < it.count; i++) {
            func(&it);
        }
    }
}

DE_PRIV void physics_init(deccan_scene_t *scene) {
    cpVect gravity = cpv(0, -9.6);
    scene->physics_space = cpSpaceNew();
    cpSpaceSetGravity(scene->physics_space, gravity);
}

DE_PRIV void physics_quit(deccan_scene_t *scene) {
    cpSpaceFree(scene->physics_space);
}

DE_PRIV void physics_step(deccan_scene_t *scene) {
    float fps_limit = deccan_core_get_framerate_limit();
    cpSpaceStep(scene->physics_space, (float)(1.0f / fps_limit));

    iterate_object(scene, physics_sync_gameobject_it);
}

DE_PRIV void physics_poststep(deccan_scene_t *scene) {
    iterate_object(scene, physics_sync_physicsbody_it);
}

DE_IMPL deccan_scenelayer_t *deccan_physics_layer(void) {
    deccan_scenelayer_t *physics = deccan_scenelayer_create(&(deccan_scenelayer_desc_t){
        .name = "physics",
        .cb = {
            [DE_SCENE_LAYER_ATBEGINNING] = physics_init,
            [DE_SCENE_LAYER_ATSTEP] = physics_step,
            [DE_SCENE_LAYER_ATPOSTSTEP] = physics_poststep,
            [DE_SCENE_LAYER_ATEND] = physics_quit,
        }
    });

    return physics;
}
