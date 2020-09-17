/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Flecs.h"

void DE_Flecs_RegisterComponent(const char *name, size_t size, size_t alignment) {
    GameScene *scene = Scene_CurrentScene();

    DeccanComponent component = {0};
    component.key  = DE_String_New(name);
    component.size = size;
    component.id  = ecs_new_component(scene->world, 0, component.key, component.size, alignment);

    stbds_shputs(scene->components, component);
}

DeccanComponent DE_Flecs_LookupComponent(const char *name) {
    GameScene *scene = Scene_CurrentScene();
    return stbds_shgets(scene->components, name);
}

uint64_t DE_Flecs_RegisterTag(const char *name) {
    GameScene *scene = Scene_CurrentScene();
    ecs_entity_t id = ecs_new_entity(scene->world, 0, name, "0");
    return id;
}

void DE_Flecs_System(DeccanSysFunc iter, const char *name, const char *sign, DeccanEcsType type) {
    GameScene *scene = Scene_CurrentScene();
    ecs_entity_t sys = ecs_new_system(scene->world, 0, name ? name : "system", type, sign, iter);
}

void DE_Flecs_SetTag(ecs_entity_t entity, const char *name) {
    GameScene *scene = Scene_CurrentScene();
    ecs_entity_t tag = ecs_lookup(scene->world, name);
    if(tag == 0)
        tag = DE_Flecs_RegisterTag(name);

    ecs_type_t type = ecs_type_from_entity(scene->world, tag);
    ecs_add_type(scene->world, entity, type);
}

bool DE_Flecs_HasTag(ecs_entity_t entity, const char *name) {
    GameScene *scene = Scene_CurrentScene();
    ecs_entity_t tag = ecs_lookup(scene->world, name);
    if(tag == 0)
        return false;

    ecs_type_t type = ecs_type_from_entity(scene->world, tag);
    return ecs_has_type(scene->world, entity, type);
}

void *DE_Flecs_IterColumn(DeccanSysIter *it, const char *name, int index) {
    return ecs_column_w_size(it, DE_Flecs_LookupComponent(name).size, index);
}
