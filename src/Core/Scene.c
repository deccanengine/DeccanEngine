/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Scene.h>
#include <Deccan/Core.h>

static struct {
    GameScene **scenes;
    int sceneCount;
} SceneInfo = {
    .scenes = NULL,
    .sceneCount = 0
};

GameScene **Scene_GetSceneArray() {
    return SceneInfo.scenes;
}

int Scene_GetSceneCount() {
    return SceneInfo.sceneCount;
}

void Scene_FreeAll() {
    stbds_arrfree(SceneInfo.scenes);
}

#define void_func(x) void (*x)(void)

GameScene *Scene_NewScene(const char *name, void_func(af), void_func(as), void_func(ar), void_func(ae)) {
    GameScene *scene = DE_NEW(GameScene, 1);
    
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

void Scene_AddScene(GameScene *scene, bool is_replacing) {
    if(scene == NULL) { DE_report("Invalid scene data"); return; }

    if(SceneInfo.sceneCount != 0) {
        if(is_replacing) { stbds_arrpop(SceneInfo.scenes); SceneInfo.sceneCount--; }
        else { SceneInfo.scenes[SceneInfo.sceneCount-1]->is_paused = true; }
    }
    
    if(stbds_arrput(SceneInfo.scenes, scene) != scene) {
        DE_report("Cannot add scene: %s\n", scene->name);
        return;
    }
    SceneInfo.sceneCount++;
}

void Scene_RemoveScene() {
    if(SceneInfo.sceneCount > 1) { 
        stbds_arrpop(SceneInfo.scenes);
        SceneInfo.scenes[SceneInfo.sceneCount-1]->is_paused = false;
    }
}

GameScene *Scene_CurrentScene() {
    return SceneInfo.scenes[SceneInfo.sceneCount-1];
}

void Scene_PauseScene(bool pause) {
    SceneInfo.scenes[SceneInfo.sceneCount-1]->is_paused = pause;
}

bool Scene_IsScenePaused() {
    return SceneInfo.scenes[SceneInfo.sceneCount-1]->is_paused;
}