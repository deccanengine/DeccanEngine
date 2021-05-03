/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Object.h"
#include "Scene.h"
#include "../World/Flecs.h"

////////////////////////////////////////////////////////////////////////////////
// Initialization and instantiator functions
////////////////////////////////////////////////////////////////////////////////

DE_PRIV void object_none_func(deccan_game_object_t obj) {
    DE_UNUSED(obj);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_game_object_t deccan_object_new_object(const char *name) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();
    deccan_game_object_t obj;

    obj.entity = ecs_new_w_entity(scene->world, 0);

    deccan_object_info_t info;
    info.visible = true;
    info.active = true;
    info.to_remove = false;
    info.is_beginning = true;
    info.at_first_frame = object_none_func;
    info.at_beginning = object_none_func;
    info.at_step = object_none_func;
    info.at_render = object_none_func;
    info.at_end = object_none_func;

    deccan_object_set_name(obj, name);
    deccan_object_set_component(obj, "Info", &info);
    deccan_object_make_prefab(obj);

    return obj;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_delete_object(deccan_game_object_t obj) {
    deccan_object_info_t *info = deccan_object_get_component(obj, "Info");
    info->to_remove = true;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_free_object(deccan_game_object_t obj) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();
    deccan_object_info_t *info = deccan_object_get_component(obj, "Info");

    if (info->active)
        info->at_end(obj);

    /* Free */
    ecs_delete(scene->world, obj.entity);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_object_is_valid(deccan_game_object_t obj) {
    return deccan_object_has_tag(obj, "Info");
}

////////////////////////////////////////////////////////////////////////////////
// Prefab and hierarchy functions
////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_game_object_t deccan_object_make_copy(deccan_game_object_t object) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();

    deccan_game_object_t object_inst;
    object_inst.entity = ecs_new_w_entity(scene->world, ECS_INSTANCEOF | object.entity);

    deccan_object_info_t *info = deccan_object_get_component(object_inst, "Info");
    info->is_beginning = true;
    info->active = true;
    deccan_object_set_component(object_inst, "Info", info);

    return object_inst;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_make_prefab(deccan_game_object_t object) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();
    ecs_add_entity(scene->world, object.entity, EcsPrefab);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_set_parent(deccan_game_object_t object, deccan_game_object_t parent) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();
    ecs_add_entity(scene->world, object.entity, ECS_CHILDOF | parent.entity);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_add_child(deccan_game_object_t object, deccan_game_object_t child) {
    deccan_object_set_parent(child, object);
}

////////////////////////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_update(deccan_game_object_t obj) {
    deccan_object_info_t *info = deccan_object_get_component(obj, "Info");

    if (info->to_remove) {
        deccan_object_free_object(obj);
        return;
    }

    if (!info->active)
        return;

    if (info->is_beginning) {
        info->at_beginning(obj);
        info->is_beginning = false;
        deccan_object_set_component(obj, "Info", info);
    }
    else {
        info->at_step(obj);
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_render(deccan_game_object_t obj) {
    deccan_object_info_t *info = deccan_object_get_component(obj, "Info");

    if (!info->visible || !info->active)
        return;

    if (!info->is_beginning) {
        info->at_render(obj);
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_end(deccan_game_object_t obj) {
    deccan_object_info_t *info = deccan_object_get_component(obj, "Info");

    if (!info->active)
        return;

    info->at_end(obj);
}

////////////////////////////////////////////////////////////////////////////////
// Component
////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_set_component(deccan_game_object_t obj, const char *name, void *component) {
    deccan_flecs_set_component(obj.entity, name, component);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void *deccan_object_get_component(deccan_game_object_t obj, const char *name) {
    void *component = deccan_flecs_get_component(obj.entity, name);
    if (component == NULL) {
        DE_ERROR("Component %s does not exists on object %s", name, deccan_object_get_name(obj));
        return NULL;
    }
    return component;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_remove_component(deccan_game_object_t obj, const char *name) {
    return deccan_flecs_remove_component(obj.entity, name);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_set_name(deccan_game_object_t obj, const char *name) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();
    ecs_set_ptr_w_entity(scene->world, obj.entity, FLECS__EEcsName, sizeof(EcsName), &(EcsName){deccan_string_new(name)});
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL const char *deccan_object_get_name(deccan_game_object_t obj) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();
    EcsName *name = ecs_get_mut_w_entity(scene->world, obj.entity, FLECS__EEcsName, NULL);
    return name->value;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_set_tag(deccan_game_object_t obj, const char *name) {
    deccan_flecs_set_tag(obj.entity, name);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_object_has_tag(deccan_game_object_t obj, const char *name) {
    return deccan_flecs_has_tag(obj.entity, name);
}

////////////////////////////////////////////////////////////////////////////////
// Setters and Getters
////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_object_is_hidden(deccan_game_object_t obj) {
    deccan_object_info_t *info = deccan_object_get_component(obj, "Info");
    return info->visible;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_hide(deccan_game_object_t obj, bool hide) {
    deccan_object_info_t *info = deccan_object_get_component(obj, "Info");
    info->visible = hide;
    deccan_object_set_component(obj, "Info", info);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_object_is_active(deccan_game_object_t obj) {
    deccan_object_info_t *info = deccan_object_get_component(obj, "Info");
    return info->active;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_object_activate(deccan_game_object_t obj, bool act) {
    deccan_object_info_t *info = deccan_object_get_component(obj, "Info");
    info->active = act;
    deccan_object_set_component(obj, "Info", info);
}