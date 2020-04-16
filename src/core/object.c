/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "object.h"

#define obj_func(x) void (*x)(Deccan_GameObject *object)

Deccan_GameObject *_priv_Object_new_object(
    const char *name, const char *type, 
    obj_func(ab), obj_func(as), obj_func(ar), obj_func(ae)) {
    Deccan_GameObject *obj = malloc(sizeof(Deccan_GameObject*));
    obj->name = malloc(sizeof(char*)*strlen(name)); strcpy(obj->name, name);
    obj->type = malloc(sizeof(char*)*strlen(type)); strcpy(obj->type, type);
    obj->at_beginning = ab;
    obj->at_step = as;
    obj->at_render = ar;
    obj->at_end = ae;
    return obj;
}

#undef obj_func

void _priv_Object_instantiate_object(Deccan_GameObject *object) {
    Deccan_Scene *scene = Deccan_Scenes.current_scene(); 
    stbds_arrput(scene->objects, object);
    scene->object_count++;
}