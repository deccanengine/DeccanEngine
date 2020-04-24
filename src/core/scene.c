/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "scene.h"
#include "core.h"

#define void_func(x) void (*x)(void)

Deccan_Scene *_priv_Scene_new_scene(const char *name, void_func(af), void_func(as), void_func(ar), void_func(ae)) {
    Deccan_Scene *scene = DE_new(Deccan_Scene, 1);
    
    scene->name = DE_newstring(name);
    scene->is_paused = false;
    scene->is_first_frame = true;
    scene->objects = NULL;
    scene->object_count = 0;
    scene->at_first_frame = af;
    scene->at_step = as;
    scene->at_render = ar;
    scene->at_end = ae;

    return scene;
}

#undef void_func

void _priv_Scene_add_scene(Deccan_Scene *scene, bool is_replacing) {
    Deccan_Info *engine = Deccan_Core.get_global_engine();
    
    if(scene == NULL) { DE_report("Invalid scene data"); return; }

    if(engine->scene_count != 0) {
        if(is_replacing) { stbds_arrpop(engine->scenes); engine->scene_count--; }
        else { engine->scenes[engine->scene_count-1]->is_paused = true; }
    }
    
    if(stbds_arrput(engine->scenes, scene) != scene) {
        DE_report("Cannot add scene: %s\n", scene->name);
        return;
    }
    engine->scene_count++;
}

void _priv_Scene_remove_scene() {
    Deccan_Info *engine = Deccan_Core.get_global_engine();
    if(engine->scene_count > 1) { 
        stbds_arrpop(engine->scenes);
        engine->scenes[engine->scene_count-1]->is_paused = false;
    }
}

Deccan_Scene *_priv_Scene_current_scene() {
    Deccan_Info *engine = Deccan_Core.get_global_engine();
    return engine->scenes[engine->scene_count-1];
}

void _priv_Scene_pause_scene(bool pause) {
    Deccan_Info *engine = Deccan_Core.get_global_engine();
    engine->scenes[engine->scene_count-1]->is_paused = pause;
}

bool _priv_Scene_is_scene_paused() {
    Deccan_Info *engine = Deccan_Core.get_global_engine();
    return engine->scenes[engine->scene_count-1]->is_paused;
}