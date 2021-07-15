/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <deccanengine/world/scene.h>
#include <deccanengine/world/flecs.h>
#include <deccanengine/world/world.h>

////////////////////////////////////////////////////////////////////////////////
// Constructor and destructor
////////////////////////////////////////////////////////////////////////////////

DE_PRIV void scenelayer_sys_create(scenelayer_sys_t *modsys) {
    zpl_array_init(modsys->mods, deccan_zpl_allocator());
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_scene_t *deccan_scene_new_scene(deccan_scene_desc_t *info) {
    deccan_scene_t *scene = deccan_alloc(sizeof(deccan_scene_t), 1);

    scene->name = deccan_string_new(info->name);
    scene->is_paused = false;
    scene->world = ecs_init();
    scene->is_first_frame = true;

    scenelayer_sys_create(&scene->modsys);
    for (int i = 0; i < MAX_ADD_MODULES && info->layers[i] != NULL; i += 1) {
        deccan_scene_push_layer(scene, info->layers[i]);
    }

    return scene;
}

/////////////////////////////////////////////////////////////////////////////////
// Module systems
////////////////////////////////////////////////////////////////////////////////

DE_PRIV void scenelayer_sys_push(scenelayer_sys_t *modsys, deccan_scenelayer_t *mod) {
    zpl_array_append(modsys->mods, mod);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_scene_push_layer(deccan_scene_t *scene, deccan_scenelayer_t *mod) {
    scenelayer_sys_push(&scene->modsys, mod);
}

/////////////////////////////////////////////////////////////////////////////////
// Object handling
////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_object_t deccan_scene_instantiate_object(deccan_scene_t *scene, const char *name, deccan_object_t object) {
    deccan_object_t inst = deccan_object_make_copy(object);
    ecs_remove_entity(scene->world, inst.entity, EcsPrefab);
    if (name) {
        deccan_object_set_name(inst, name);
    }
    return inst;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_object_t deccan_scene_get_object(deccan_scene_t *scene, const char *name) {
    ecs_entity_t obj = ecs_lookup(scene->world, name);

    deccan_object_t object;
    object.entity = obj;
    return object;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_scene_iterate_object(deccan_scene_t *scene, void (*func)(deccan_object_t this)) {
    ecs_query_t *query = ecs_query_new(scene->world, "Info");
    ecs_iter_t it = ecs_query_iter(query);

    while (ecs_query_next(&it)) {
        for (int i = 0; i < it.count; i++) {
            ecs_entity_t entity = it.entities[i];

            deccan_object_t object;
            object.entity = entity;

            func(object);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_scene_iterate_object_of_type(deccan_scene_t *scene, const char *tag, void (*func)(deccan_object_t this)) {
    ecs_query_t *query = ecs_query_new(scene->world, "Info");
    ecs_iter_t it = ecs_query_iter(query);

    while (ecs_query_next(&it)) {
        for (int i = 0; i < it.count; i++) {
            ecs_entity_t entity = it.entities[i];

            deccan_object_t object;
            object.entity = entity;

            if (deccan_object_has_tag(object, tag)) {
                func(object);
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////
// Scene status
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_scene_pause_scene(deccan_scene_t *scene, bool pause) {
    scene->is_paused = pause;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_scene_is_scene_paused(deccan_scene_t *scene) {
    return scene->is_paused;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_scene_set_camera(deccan_scene_t *scene, deccan_camera_t *camera) {
    scene->camera = camera;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_camera_t *deccan_scene_get_camera(deccan_scene_t *scene) {
    return scene->camera;
}
