/* Deccan Game Engine - C11 2D SDL Game Engine.
* Copyright 2020, 2021 Ayush Bardhan Tripathy
*
* This software is licensed under MIT License.
* See LICENSE.md included with this package for more info.
*/

#include <deccanengine/world/world.h>
#include <deccanengine/world/flecs.h>

#include "world_internal.h"
#include "flecs_internal.h"
#include "components.h"
#include "systems.h"
#include "default_assets.h"

DE_PRIV struct {
    zpl_array(deccan_scene_t *) scenes;

    bool is_adding;
    bool is_removing;
    bool is_replacing;
    deccan_scene_t *changed_scene;

    deccan_asset_manager_t manager;
} scene_info = {
    .scenes = NULL,
    .is_adding = false,
    .is_removing = false,
    .changed_scene = NULL
};

////////////////////////////////////////////////////////////////////////////////
// World
////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_world_add_scene(deccan_scene_t *scene, bool is_replacing) {
    if (scene == NULL) {
        DE_WARN("Invalid scene data");
        return;
    }

    scene_info.changed_scene = scene;
    scene_info.is_replacing = is_replacing;
    scene_info.is_adding = true;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_world_remove_scene(void) {
    scene_info.is_removing = true;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_scene_t *deccan_world_get_current_scene(void) {
    return zpl_array_back(scene_info.scenes);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL int deccan_world_get_scene_count(void) {
    return zpl_array_count(scene_info.scenes);
}

////////////////////////////////////////////////////////////////////////////////
// World internals
////////////////////////////////////////////////////////////////////////////////

void world_create(void) {
    zpl_array_init(scene_info.scenes, deccan_zpl_allocator());

    // TODO: also for individual scenes?
    scene_info.manager = make_default_asset_manager();
    deccan_asset_set_manager_inst(&scene_info.manager);
    load_default_assets();
}

////////////////////////////////////////////////////////////////////////////////

void world_free_all_scene(void) {
    zpl_array_free(scene_info.scenes);

    deccan_asset_destroy_manager(&scene_info.manager);
}

////////////////////////////////////////////////////////////////////////////////

DE_PRIV void object_first_frame_cb(deccan_object_t object) {
    deccan_object_info_t *info = deccan_object_get_component(object, "Info");
    info->cb[DE_OBJECT_ATFIRSTFRAME](object);
}

////////////////////////////////////////////////////////////////////////////////

DE_PRIV inline void scenelayer_stage(deccan_scenelayer_t *mod, deccan_scenelayer_stage_t stage) {
    if (stage < 0 && stage > DE_SCENE_LAYER_STAGE_COUNT) {
        DE_WARN("Module stage (%d) does not exists", stage);
        return;
    }

    mod->cb[stage](deccan_world_get_current_scene());
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void scenelayer_sys_iter(scenelayer_sys_t *modsys, deccan_scenelayer_stage_t stage, bool order) {
    if (order) {
        for (int i = 0; i < zpl_array_count(modsys->mods); i += 1) {
            scenelayer_stage(modsys->mods[i], stage);
        }
    }
    else {
        for (int i = zpl_array_count(modsys->mods) - 1; i >= 0; i -= 1) {
            scenelayer_stage(modsys->mods[i], stage);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void world_update(void) {
    /* Add or remove scene (only one) */
    world_make_scene_changes();

    /* Process Scene(s) and deccan_object_t (s) */
    deccan_scene_t *scene = deccan_world_get_current_scene(); /* Current scene */

    /* First frame of the scene. Same as at_beginning for scene */
    if (scene->is_first_frame == true) {
        deccan_flecs_register_component("Info", sizeof(deccan_object_info_t), ECS_ALIGNOF(deccan_object_info_t));

        components_register_all();
        systems_register_all();

        scenelayer_sys_iter(&scene->modsys, DE_SCENE_LAYER_ATBEGINNING, true);
        deccan_scene_iterate_object(scene, object_first_frame_cb);

        scene->is_first_frame = false;
    }

    /* AtStep of scenes and objects */
    scenelayer_sys_iter(&scene->modsys, DE_SCENE_LAYER_ATSTEP, true);
    flecs_update_world();
    deccan_scene_iterate_object(scene, deccan_object_update);

    /* AtPostStep (AtRender) of scenes and objects */
    deccan_scene_iterate_object(scene, deccan_object_render);
    scenelayer_sys_iter(&scene->modsys, DE_SCENE_LAYER_ATPOSTSTEP, false);
}

////////////////////////////////////////////////////////////////////////////////

DE_PRIV inline void scenelayer_sys_destroy(scenelayer_sys_t *modsys) {
    for (int i = 0; i < zpl_array_count(modsys->mods); i += 1) {
        deccan_scenelayer_destroy(modsys->mods[i]);
    }

    zpl_array_free(modsys->mods);
}

 void world_quit_scene(void) {
    /* AtEnd of scenes and objects */
    deccan_scene_t *scene = deccan_world_get_current_scene();

    scenelayer_sys_iter(&scene->modsys, DE_SCENE_LAYER_ATEND, false);
    deccan_scene_iterate_object(scene, deccan_object_end);

    scenelayer_sys_destroy(&scene->modsys);

    /* Dellocate everything */
    for (int i = 0; i < deccan_world_get_scene_count(); i += 1) {
        deccan_scene_t *scene = scene_info.scenes[i];

        deccan_scene_iterate_object(scene, deccan_object_delete_object);

        ecs_fini(scene->world);
        deccan_free(scene->name);
        deccan_free(scene);
    }
}

////////////////////////////////////////////////////////////////////////////////

void world_make_scene_changes(void) {
    int32_t scene_count = deccan_world_get_scene_count();
    if (scene_info.is_adding) {
        scene_info.is_adding = false;

        if (scene_count != 0) {
            if (scene_info.is_replacing) {
                zpl_array_pop(scene_info.scenes);
            }
            else {
                deccan_scene_t *scene = scene_info.scenes[scene_count - 1];
                scene->is_paused = true;
            }
        }

        zpl_array_append(scene_info.scenes, scene_info.changed_scene);
    }
    else if (scene_info.is_removing) {
        scene_info.is_removing = false;

        if (scene_count > 1) {
            zpl_array_pop(scene_info.scenes);

            deccan_scene_t *scene = scene_info.scenes[scene_count - 1];
            scene->is_paused = false;
        }
    }
}
