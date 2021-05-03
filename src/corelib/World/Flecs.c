/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Flecs.h"

////////////////////////////////////////////////////////////////////////////////
// System
////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_flecs_system(deccan_flecs_action_func_t iter, const char *name, const char *sign, deccan_flecs_type_t type) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();
    ecs_new_system(scene->world, 0, name ? name : "system", type, sign, iter);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_flecs_update_world(void) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();
    ecs_progress(scene->world, 0);
}

////////////////////////////////////////////////////////////////////////////////
// Component
////////////////////////////////////////////////////////////////////////////////

DE_PRIV size_t GetComponentSize(ecs_entity_t id) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();

    const EcsComponent *comp = ecs_get_w_entity(scene->world, id, FLECS__EEcsComponent);
    return comp->size;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_flecs_register_component(const char *name, size_t size, size_t alignment) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();
    ecs_new_component(scene->world, 0, name, size, alignment);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_flecs_set_component(ecs_entity_t entity, const char *name, void *component) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();

    ecs_entity_t id = ecs_lookup(scene->world, name);
    size_t size = GetComponentSize(id);
    if (id == 0) {
        DE_WARN("Component %s is not a valid registered component in the scene", name);
        return;
    }

    ecs_set_ptr_w_entity(scene->world, entity, id, size, component);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void *deccan_flecs_get_component(ecs_entity_t entity, const char *name) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();
    return ecs_get_mut_w_entity(scene->world, entity, ecs_lookup(scene->world, name), NULL);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_flecs_remove_component(ecs_entity_t entity, const char *name) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();
    ecs_entity_t component = ecs_lookup(scene->world, name);
    ecs_remove_entity(scene->world, entity, component);
}

////////////////////////////////////////////////////////////////////////////////
// Tag
////////////////////////////////////////////////////////////////////////////////

DE_IMPL uint64_t deccan_flecs_register_tag(const char *name) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();
    ecs_entity_t id = ecs_new_entity(scene->world, 0, name, "0");
    return id;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_flecs_set_tag(ecs_entity_t entity, const char *name) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();
    ecs_entity_t tag = ecs_lookup(scene->world, name);
    if (tag == 0)
        tag = deccan_flecs_register_tag(name);

    ecs_type_t type = ecs_type_from_entity(scene->world, tag);
    ecs_add_type(scene->world, entity, type);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_flecs_has_tag(ecs_entity_t entity, const char *name) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();
    ecs_entity_t tag = ecs_lookup(scene->world, name);
    if (tag == 0)
        return false;

    ecs_type_t type = ecs_type_from_entity(scene->world, tag);
    return ecs_has_type(scene->world, entity, type);
}

////////////////////////////////////////////////////////////////////////////////
// Iterator
////////////////////////////////////////////////////////////////////////////////

DE_IMPL void *deccan_flecs_iter_column(deccan_flecs_iter_t *it, const char *name, int index) {
    deccan_game_scene_t *scene = deccan_scene_current_scene();
    ecs_entity_t id = ecs_lookup(scene->world, name);
    return ecs_column_w_size(it, GetComponentSize(id), index);
}
