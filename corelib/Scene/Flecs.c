/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Flecs.h"

static struct {
    DeccanComponent *components;
} Flecs_Info = {
    .components = NULL
};

void DE_Flecs_RegisterComponent(const char *name, size_t size, size_t alignment) {
    GameScene *scene = Scene_CurrentScene();

    DeccanComponent component = {0};
    component.key  = DE_String_New(name);
    component.size = size;
    component.id  = ecs_new_component(scene->world, 0, component.key, component.size, alignment);

    stbds_shputs(Flecs_Info.components, component);
}

DeccanComponent DE_Flecs_LookupComponent(const char *name) {
    return stbds_shgets(Flecs_Info.components, name);
}
