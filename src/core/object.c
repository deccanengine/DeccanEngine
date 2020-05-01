/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "object.h"
#include "scene.h"

void DE_GameObject_Msg_send(DE_GameObject *obj, const char *msg) {
    DE_Msg_send(&obj->msg, msg);
}

bool DE_GameObject_Msg_receive(DE_GameObject *obj, const char *msg) {
    return DE_Msg_receive(&obj->msg, msg);
}

#define obj_func(x) void (*x)(DE_GameObject *object)

DE_GameObject *DE_Object_new_object(
    const char *name, const char *type, 
    obj_func(af), obj_func(ab), obj_func(as), obj_func(ar), obj_func(ae)) {
    
    DE_GameObject *obj = DE_new(DE_GameObject, 1);
    
    obj->info.name = DE_newstring(name);
    obj->info.type = DE_newstring(type);
    
    DE_Msg_init(&obj->msg, DECCAN_OBJ_MSG_COUNT, DECCAN_OBJ_MSG_LENGTH);
    obj->SendMessage = DE_GameObject_Msg_send;
    obj->ReceiveMessage = DE_GameObject_Msg_receive;
    
    obj->is_beginning = true;
    obj->at_first_frame = af;
    obj->at_beginning = ab;
    obj->at_step = as;
    obj->at_render = ar;
    obj->at_end = ae;

    return obj;
}

#undef obj_func

void DE_Object_instantiate_object(DE_GameObject *object) {
    DE_Scene *scene = DE_Scenes_current_scene(); 
    if(object == NULL) { return; }
    if(stbds_arrput(scene->objects, object) != object) {
        DE_report("Cannot instantiate object: %s", object->info.name); return;
    }
    scene->object_count++;
}

DE_GameObject *DE_Object_get_object(const char *name) {
    DE_Scene *scene = DE_Scenes_current_scene();
    for(int i=0; i<scene->object_count; i++) {
        if(!strcmp(scene->objects[i]->info.name, name)) {
            return scene->objects[i];
        }
    }
    DE_report("GameObject not found: %s", name);
}

void DE_Object_get_object_of_type(const char *name, void(*func)(DE_GameObject *obj)) {
    DE_Scene *scene = DE_Scenes_current_scene();
    for(int i=0; i<scene->object_count; i++) {
        if(!strcmp(scene->objects[i]->info.type, name)) {
            func(scene->objects[i]);
        }
    }
}