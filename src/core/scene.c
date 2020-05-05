/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "scene.h"
#include "core.h"

#define void_func(x) void (*x)(void)

DE_GameScene *DE_Scene_NewScene(const char *name, void_func(af), void_func(as), void_func(ar), void_func(ae)) {
    DE_GameScene *scene = DE_new(DE_GameScene, 1);
    
    scene->name = DE_newstring(name);
    scene->is_paused = false;
    scene->objects = NULL;
    scene->object_count = 0;
    
    scene->is_first_frame = true;
    scene->AtFirstFrame = af;
    scene->AtStep = as;
    scene->AtRender = ar;
    scene->AtEnd = ae;

    return scene;
}

#undef void_func

void DE_Scene_AddScene(DE_GameScene *scene, bool is_replacing) {
    DE_GameInfo *engine = DE_Core_GetGlobalInfo();
    
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

void DE_Scene_RemoveScene() {
    DE_GameInfo *engine = DE_Core_GetGlobalInfo();
    if(engine->scene_count > 1) { 
        stbds_arrpop(engine->scenes);
        engine->scenes[engine->scene_count-1]->is_paused = false;
    }
}

DE_GameScene *DE_Scene_CurrentScene() {
    DE_GameInfo *engine = DE_Core_GetGlobalInfo();
    return engine->scenes[engine->scene_count-1];
}

void DE_Scene_PauseScene(bool pause) {
    DE_GameInfo *engine = DE_Core_GetGlobalInfo();
    engine->scenes[engine->scene_count-1]->is_paused = pause;
}

bool DE_Scene_IsScenePaused() {
    DE_GameInfo *engine = DE_Core_GetGlobalInfo();
    return engine->scenes[engine->scene_count-1]->is_paused;
}