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

DE_IMPL void DE_FlecsSystem(DeccanFlecsActionFunc iter, const char *name, const char *sign, DeccanFlecsType type) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    ecs_new_system(scene->world, 0, name ? name : "system", type, sign, iter);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void DE_FlecsUpdateWorld(void) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    ecs_progress(scene->world, 0);
}

////////////////////////////////////////////////////////////////////////////////
// Component
////////////////////////////////////////////////////////////////////////////////

DE_PRIV size_t GetComponentSize(ecs_entity_t id) {
    DeccanGameScene *scene = DE_SceneCurrentScene();

    const EcsComponent *comp = ecs_get_w_entity(scene->world, id, FLECS__EEcsComponent);
    return comp->size;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void DE_FlecsRegisterComponent(const char *name, size_t size, size_t alignment) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    ecs_new_component(scene->world, 0, name, size, alignment);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void DE_FlecsSetComponent(ecs_entity_t entity, const char *name, void *component) {
    DeccanGameScene *scene = DE_SceneCurrentScene();

    ecs_entity_t id = ecs_lookup(scene->world, name);
    size_t size = GetComponentSize(id);
    if (id == 0) {
        DE_WARN("Component %s is not a valid registered component in the scene", name);
        return;
    }

    ecs_set_ptr_w_entity(scene->world, entity, id, size, component);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void *DE_FlecsGetComponent(ecs_entity_t entity, const char *name) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    return ecs_get_mut_w_entity(scene->world, entity, ecs_lookup(scene->world, name), NULL);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void DE_FlecsRemoveComponent(ecs_entity_t entity, const char *name) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    ecs_entity_t component = ecs_lookup(scene->world, name);
    ecs_remove_entity(scene->world, entity, component);
}

////////////////////////////////////////////////////////////////////////////////
// Tag
////////////////////////////////////////////////////////////////////////////////

DE_IMPL uint64_t DE_FlecsRegisterTag(const char *name) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    ecs_entity_t id = ecs_new_entity(scene->world, 0, name, "0");
    return id;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void DE_FlecsSetTag(ecs_entity_t entity, const char *name) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    ecs_entity_t tag = ecs_lookup(scene->world, name);
    if (tag == 0)
        tag = DE_FlecsRegisterTag(name);

    ecs_type_t type = ecs_type_from_entity(scene->world, tag);
    ecs_add_type(scene->world, entity, type);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool DE_FlecsHasTag(ecs_entity_t entity, const char *name) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    ecs_entity_t tag = ecs_lookup(scene->world, name);
    if (tag == 0)
        return false;

    ecs_type_t type = ecs_type_from_entity(scene->world, tag);
    return ecs_has_type(scene->world, entity, type);
}

////////////////////////////////////////////////////////////////////////////////
// Iterator
////////////////////////////////////////////////////////////////////////////////

DE_IMPL void *DE_FlecsIterColumn(DeccanFlecsIter *it, const char *name, int index) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    ecs_entity_t id = ecs_lookup(scene->world, name);
    return ecs_column_w_size(it, GetComponentSize(id), index);
}
