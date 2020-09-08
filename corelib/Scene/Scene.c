/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Scene.h"
#include "../Core/Core.h"

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

void Scene_Update() {
    /* Process Scene(s) and GameObject(s) */
    GameScene *scene = Scene_CurrentScene();  /* Current scene */

    /* First frame of the scene. Same as at_beginning for scene */
    if(scene->is_first_frame == true) {
        scene->AtFirstFrame();
        scene->is_first_frame = false;

        /* First frame of objects */
        for(int i = 0; i < stbds_arrlen(scene->objects); i++) {
            GameObject *obj = scene->objects[i];
            obj->AtFirstFrame(obj);
        }
    }

    /* AtStep of scenes and objects */
    scene->AtStep();

    for(int i=0; i<stbds_arrlen(scene->objects); i++) {
        Object_Update(scene->objects[i]);
    }

    /* AtRender of scenes and objects */
    scene->AtRender();

    for(int i=0; i<stbds_arrlen(scene->objects); i++) {
        Object_Render(scene->objects[i]);
    }
}

void Scene_Quit() {
    /* at_end of scenes and objects */
    GameScene *currentScene = Scene_CurrentScene();
    currentScene->AtEnd();

    for(int i = 0; i < stbds_arrlen(currentScene->objects); i++) {
        Object_End(currentScene->objects[i]);
    }

    /* Dellocate everything */
    for(int i = 0; i < stbds_arrlen(SceneInfo.scenes); i++) {
        GameScene *scene = SceneInfo.scenes[i];

        for(int j = 0; j < stbds_arrlen(scene->objects); j++) {
            Object_DeleteObject(scene->objects[i]);
        }

        DE_Mem_Delete(scene->name);
        DE_Mem_Delete(scene);
    }
}

/////////////////////////////////////////////////
// Constructor and destructor
////////////////////////////////////////////////

GameScene *Scene_NewScene(const char *name) {
    GameScene *scene = DE_Mem_New(sizeof(GameScene), 1);

    scene->name = DE_String_New(name);
    scene->is_paused = false;
    scene->objects = NULL;

    scene->is_first_frame = true;
    scene->AtFirstFrame = NULL_VOIDFUNC;
    scene->AtStep = NULL_VOIDFUNC;
    scene->AtRender = NULL_VOIDFUNC;
    scene->AtEnd = NULL_VOIDFUNC;

    return scene;
}

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
