/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "scene.h"

Deccan_Scene *_priv_Scene_new_scene(const char *name, state_func_ptr(ab), state_func_ptr(as), state_func_ptr(ae)) {
    Deccan_Scene *scene = malloc(sizeof(Deccan_Scene));
    
    scene->name = malloc(sizeof(char*)*strlen(name)); strcpy(scene->name, name);
    scene->is_paused = false;
    scene->is_first_frame = true;
    scene->objects = NULL;
    scene->at_begining = ab;
    scene->at_step = as;
    scene->at_end = ae;

    return scene;
}

void _priv_Scene_add_scene(Deccan_Scene *scene, bool is_replacing) {
    if(stbds_arrlen(Deccan_Core.get_global_engine()->scenes) != 0) {
        if(is_replacing) { stbds_arrpop(Deccan_Core.get_global_engine()->scenes); }
        else {
            Deccan_Core.get_global_engine()->scenes[stbds_arrlen(Deccan_Core.get_global_engine()->scenes)-1]->is_paused = true;
        }
    }
    stbds_arrput(Deccan_Core.get_global_engine()->scenes, scene);
}

void _priv_Scene_remove_scene(Deccan_Scene *scene) {
    if(stbds_arrlen(Deccan_Core.get_global_engine()->scenes) > 1) { 
        stbds_arrpop(Deccan_Core.get_global_engine()->scenes);
        Deccan_Core.get_global_engine()->scenes[stbds_arrlen(Deccan_Core.get_global_engine()->scenes)-1]->is_paused = false;
    }
}

Deccan_Scene *_priv_Scene_current_scene() {
    return Deccan_Core.get_global_engine()->scenes[stbds_arrlen(Deccan_Core.get_global_engine()->scenes)-1];
}

void _priv_Scene_pause_scene(bool pause) {
    Deccan_Core.get_global_engine()->scenes[stbds_arrlen(Deccan_Core.get_global_engine()->scenes)-1]->is_paused = pause;
}

bool _priv_Scene_is_scene_paused() {
    return Deccan_Core.get_global_engine()->scenes[stbds_arrlen(Deccan_Core.get_global_engine()->scenes)-1]->is_paused;
}