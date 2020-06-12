/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Scene.h"
#include "../Core.h"

static struct {
    GameScene **scenes;
} SceneInfo = {
    .scenes = NULL
};

/////////////////////////////////////////////////
// Scene internals
////////////////////////////////////////////////

GameScene **Scene_GetSceneArray() {
    return SceneInfo.scenes;
}

int Scene_GetSceneCount() {
    return stbds_arrlen(SceneInfo.scenes);
}

void Scene_FreeAll() {
    stbds_arrfree(SceneInfo.scenes);
}

/////////////////////////////////////////////////
// Constructor and destructor
////////////////////////////////////////////////

GameScene *Scene_NewScene(const char *name) {
    GameScene *scene = DE_NEW(GameScene, 1);
    
    scene->name = DE_NEWSTRING(name);
    scene->is_paused = false;
    scene->objects = NULL;
    
    scene->is_first_frame = true;
    scene->AtFirstFrame = NULL_VOIDFUNC;
    scene->AtStep = NULL_VOIDFUNC;
    scene->AtRender = NULL_VOIDFUNC;
    scene->AtEnd = NULL_VOIDFUNC;

    return scene;
}

#undef void_func

void Scene_AddScene(GameScene *scene, bool is_replacing) {
    if(scene == NULL) { 
        DE_REPORT("Invalid scene data"); 
        return; 
    }

    int32_t sceneCount = stbds_arrlen(SceneInfo.scenes);

    if(sceneCount != 0) {
        if(is_replacing) { 
            stbds_arrpop(SceneInfo.scenes); 
        }
        else { 
            SceneInfo.scenes[sceneCount - 1]->is_paused = true; 
        }
    }
    
    if(stbds_arrput(SceneInfo.scenes, scene) != scene) {
        DE_REPORT("Cannot add scene: %s\n", scene->name);
        return;
    }
}

void Scene_RemoveScene() {
    int32_t sceneCount = stbds_arrlen(SceneInfo.scenes);

    if(sceneCount > 1) { 
        stbds_arrpop(SceneInfo.scenes);
        SceneInfo.scenes[sceneCount - 1]->is_paused = false;
    }
}

/////////////////////////////////////////////////
// Scene status
////////////////////////////////////////////////

GameScene *Scene_CurrentScene() {
    return SceneInfo.scenes[stbds_arrlen(SceneInfo.scenes) - 1];
}

void Scene_PauseScene(bool pause) {
    SceneInfo.scenes[stbds_arrlen(SceneInfo.scenes) - 1]->is_paused = pause;
}

bool Scene_IsScenePaused() {
    return SceneInfo.scenes[stbds_arrlen(SceneInfo.scenes) - 1]->is_paused;
}