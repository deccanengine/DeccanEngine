/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Scene.h"
#include "../World/Flecs.h"

DE_PRIV struct {
    zpl_array(deccan_game_scene_t *) scenes;

    bool is_adding;
    bool is_removing;
    bool is_replacing;
    deccan_game_scene_t *changed_scene;
} scene_info = {
    .scenes = NULL, 
    .is_adding = false, 
    .is_removing = false, 
    .changed_scene = NULL
};

////////////////////////////////////////////////////////////////////////////////
// Scene internals
////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_scene_sys_create(void) {
    zpl_array_init(scene_info.scenes, deccan_z_p_l_allocator());
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_game_scene_t **deccan_scene_get_scene_array(void) {
    return scene_info.scenes;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL int deccan_scene_get_scene_count(void) {
    return zpl_array_count(scene_info.scenes);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_scene_free_all(void) {
    zpl_array_free(scene_info.scenes);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void RegisterBaseComponent(deccan_game_scene_t *scene) {
    deccan_flecs_register_component("Info", sizeof(deccan_object_info_t), ECS_ALIGNOF(deccan_object_info_t));
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void ObjectFirstFrame(deccan_game_object_t object) {
    deccan_object_info_t *info = deccan_object_get_component(object, "Info");
    info->AtFirstFrame(object);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_scene_update(void) {
    /* Add or remove scene (only one) */
    deccan_scene_make_changes();

    /* Process Scene(s) and deccan_game_object_t (s) */
    deccan_game_scene_t *scene = deccan_scene_current_scene(); /* Current scene */

    /* First frame of the scene. Same as at_beginning for scene */
    if (scene->is_first_frame == true) {
        RegisterBaseComponent(scene);
        deccan_module_sys_iter(&scene->modsys, DE_SHELL_ATBEGINNING, true);
        deccan_scene_iterate_object(ObjectFirstFrame);

        scene->is_first_frame = false;
    }

    /* AtStep of scenes and objects */
    deccan_module_sys_iter(&scene->modsys, DE_SHELL_ATSTEP, true);
    deccan_flecs_update_world();
    deccan_scene_iterate_object(deccan_object_update);

    /* AtPostStep (AtRender) of scenes and objects */
    deccan_scene_iterate_object(deccan_object_render);
    deccan_module_sys_iter(&scene->modsys, DE_SHELL_ATPOSTSTEP, false);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_scene_quit(void) {
    /* AtEnd of scenes and objects */
    deccan_game_scene_t *scene = deccan_scene_current_scene();

    deccan_module_sys_iter(&scene->modsys, DE_SHELL_ATEND, false);
    deccan_scene_iterate_object(deccan_object_end);

    deccan_module_sys_destroy(&scene->modsys);

    /* Dellocate everything */
    for (int i = 0; i < deccan_scene_get_scene_count(); i += 1) {
        deccan_game_scene_t *scene = scene_info.scenes[i];

        deccan_scene_iterate_object(deccan_object_delete_object);

        ecs_fini(scene->world);
        deccan_free(scene->name);
        deccan_free(scene);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Constructor and destructor
////////////////////////////////////////////////////////////////////////////////

DE_IMPL void SceneNoneFunc(void) { }

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_game_scene_t *deccan_scene_new_scene(const char *name) {
    deccan_game_scene_t *scene = deccan_alloc(sizeof(deccan_game_scene_t), 1);
    scene->name = deccan_string_new(name);
    scene->is_paused = false;
    scene->world = ecs_init();
    scene->is_first_frame = true;

    deccan_module_sys_create(&scene->modsys);

    return scene;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_scene_add_scene(deccan_game_scene_t *scene, bool is_replacing) {
    if (scene == NULL) {
        DE_WARN("Invalid scene data");
        return;
    }

    scene_info.changed_scene = scene;
    scene_info.is_replacing = is_replacing;
    scene_info.is_adding = true;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_scene_remove_scene(void) {
    scene_info.is_removing = true;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_scene_make_changes(void) {
    int32_t scene_count = deccan_scene_get_scene_count();
    if (scene_info.is_adding) {
        scene_info.is_adding = false;

        if (scene_count != 0) {
            if (scene_info.is_replacing) {
                zpl_array_pop(scene_info.scenes);
            }
            else {
                deccan_game_scene_t *scene = scene_info.scenes[scene_count - 1];
                scene->is_paused = true;
            }
        }

        zpl_array_append(scene_info.scenes, scene_info.changed_scene);
    }
    else if (scene_info.is_removing) {
        scene_info.is_removing = false;

        if (scene_count > 1) {
            zpl_array_pop(scene_info.scenes);

            deccan_game_scene_t *scene = scene_info.scenes[scene_count - 1];
            scene->is_paused = false;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////
// Module systems
////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_scene_push_module(deccan_game_scene_t *scene, deccan_module_t *mod) {
    deccan_module_sys_push(&scene->modsys, mod);
}

/////////////////////////////////////////////////////////////////////////////////
// Object handling
////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_scene_instantiate_object(deccan_game_object_t object) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();
    ecs_remove_entity(scene->world, object.entity, EcsPrefab);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_game_object_t deccan_scene_get_object(const char *name) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();
    ecs_entity_t obj = ecs_lookup(scene->world, name);

    deccan_game_object_t object;
    object.entity = obj;
    return object;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_scene_iterate_object(void (*func)(deccan_game_object_t this)) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();

    ecs_query_t *query = ecs_query_new(scene->world, "Info");
    ecs_iter_t it = ecs_query_iter(query);

    while (ecs_query_next(&it)) {
        for (int i = 0; i < it.count; i++) {
            ecs_entity_t entity = it.entities[i];

            deccan_game_object_t object;
            object.entity = entity;

            func(object);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_scene_iterate_object_of_type(const char *tag, void (*func)(deccan_game_object_t this)) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();

    ecs_query_t *query = ecs_query_new(scene->world, "Info");
    ecs_iter_t it = ecs_query_iter(query);

    while (ecs_query_next(&it)) {
        for (int i = 0; i < it.count; i++) {
            ecs_entity_t entity = it.entities[i];

            deccan_game_object_t object;
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

DE_IMPL deccan_game_scene_t *deccan_scene_current_scene(void) {
    return zpl_array_back(scene_info.scenes); 
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_scene_pause_scene(bool pause) {
    deccan_scene_current_scene()->is_paused = pause;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_scene_is_scene_paused(void) {
    return deccan_scene_current_scene()->is_paused;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_scene_set_camera(deccan_camera_t *camera) {
    deccan_scene_current_scene()->camera = camera;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_camera_t *deccan_scene_get_camera(void) {
    return deccan_scene_current_scene()->camera;
}