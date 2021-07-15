/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <deccanengine/world/world.h>
#include <deccanengine/world/flecs.h>

#include "flecs_internal.h"

////////////////////////////////////////////////////////////////////////////////
// Registrars
////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_flecs_register_system(deccan_flecs_action_func_t iter, const char *name, const char *sign, deccan_flecs_type_t type) {
    deccan_scene_t *scene = deccan_world_get_current_scene();

    ecs_system_init(scene->world, &(ecs_system_desc_t){
        .entity = {
            .name = name,
            .add = { type },
        },
        .query.filter.expr = sign,
        .callback = iter,
    });
}

DE_IMPL void deccan_flecs_register_component(const char *name, size_t size, size_t alignment) {
    deccan_scene_t *scene = deccan_world_get_current_scene();

    ecs_component_init(scene->world, &(ecs_component_desc_t){
        .entity.name = name,
        .size = size,
        .alignment = alignment,
    });
}

DE_IMPL uint64_t deccan_flecs_register_tag(const char *name) {
    deccan_scene_t *scene = deccan_world_get_current_scene();

    ecs_entity_t id = ecs_entity_init(scene->world, &(ecs_entity_desc_t){
        .name = name,
    });

    return id;
}

////////////////////////////////////////////////////////////////////////////////
// World
////////////////////////////////////////////////////////////////////////////////

void flecs_update_world(void) {
    deccan_scene_t *scene = deccan_world_get_current_scene();
    ecs_progress(scene->world, 0);
}

////////////////////////////////////////////////////////////////////////////////
// Component
////////////////////////////////////////////////////////////////////////////////

DE_PRIV size_t get_component_size(ecs_entity_t id) {
    deccan_scene_t *scene = deccan_world_get_current_scene();

    const EcsComponent *comp = ecs_get_w_entity(scene->world, id, FLECS__EEcsComponent);
    return comp->size;
}

////////////////////////////////////////////////////////////////////////////////

void flecs_set_component(ecs_entity_t entity, const char *name, void *component) {
    deccan_scene_t *scene = deccan_world_get_current_scene();

    ecs_entity_t id = ecs_lookup(scene->world, name);
    size_t size = get_component_size(id);
    if (id == 0) {
        DE_WARN("Component %s is not a valid registered component in the scene", name);
        return;
    }

    ecs_set_ptr_w_entity(scene->world, entity, id, size, component);
}

////////////////////////////////////////////////////////////////////////////////

void *flecs_get_component(ecs_entity_t entity, const char *name) {
    deccan_scene_t *scene = deccan_world_get_current_scene();
    return ecs_get_mut_w_entity(scene->world, entity, ecs_lookup(scene->world, name), NULL);
}

////////////////////////////////////////////////////////////////////////////////

void flecs_remove_component(ecs_entity_t entity, const char *name) {
    deccan_scene_t *scene = deccan_world_get_current_scene();
    ecs_entity_t component = ecs_lookup(scene->world, name);
    ecs_remove_entity(scene->world, entity, component);
}

////////////////////////////////////////////////////////////////////////////////
// Tag
////////////////////////////////////////////////////////////////////////////////

void flecs_set_tag(ecs_entity_t entity, const char *name) {
    deccan_scene_t *scene = deccan_world_get_current_scene();
    ecs_entity_t tag = ecs_lookup(scene->world, name);
    if (tag == 0)
        tag = deccan_flecs_register_tag(name);

    ecs_type_t type = ecs_type_from_entity(scene->world, tag);
    ecs_add_type(scene->world, entity, type);
}

////////////////////////////////////////////////////////////////////////////////

bool flecs_has_tag(ecs_entity_t entity, const char *name) {
    deccan_scene_t *scene = deccan_world_get_current_scene();
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
    deccan_scene_t *scene = deccan_world_get_current_scene();
    ecs_entity_t id = ecs_lookup(scene->world, name);
    return ecs_term_w_size(it, get_component_size(id), index);
}
