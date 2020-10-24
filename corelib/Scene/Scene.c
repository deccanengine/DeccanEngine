/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Scene.h"
#include "Flecs.h"

static struct {
    DeccanGameScene **scenes;
} SceneInfo = {
    .scenes = NULL
};

/////////////////////////////////////////////////
// Scene internals
////////////////////////////////////////////////

DeccanGameScene **DE_SceneGetSceneArray() {
    return SceneInfo.scenes;
}

int DE_SceneGetSceneCount() {
    return stbds_arrlen(SceneInfo.scenes);
}

void DE_SceneFreeAll() {
    stbds_arrfree(SceneInfo.scenes);
}

void DE_SceneUpdate() {
    /* Process Scene(s) and DeccanGameObject(s) */
    DeccanGameScene *scene = DE_SceneCurrentScene();  /* Current scene */

    /* First frame of the scene. Same as at_beginning for scene */
    if(scene->is_first_frame == true) {
        scene->AtFirstFrame();
        scene->is_first_frame = false;

        /* First frame of objects */
        for(int i = 0; i < stbds_arrlen(scene->objects); i++) {
            DeccanGameObject *obj = scene->objects[i];
            obj->AtFirstFrame(obj);
        }
    }

    /* AtStep of scenes and objects */
    scene->AtStep();
    ecs_progress(scene->world, 0);

    for(int i=0; i<stbds_arrlen(scene->objects); i++) {
        DE_ObjectUpdate(scene->objects[i]);
    }

    /* AtRender of scenes and objects */
    scene->AtRender();

    for(int i=0; i<stbds_arrlen(scene->objects); i++) {
        DE_ObjectRender(scene->objects[i]);
    }
}

void DE_SceneQuit() {
    /* at_end of scenes and objects */
    DeccanGameScene *currentScene = DE_SceneCurrentScene();
    currentScene->AtEnd();

    for(int i = 0; i < stbds_arrlen(currentScene->objects); i++) {
        DE_ObjectEnd(currentScene->objects[i]);
    }

    /* Dellocate everything */
    for(int i = 0; i < stbds_arrlen(SceneInfo.scenes); i++) {
        DeccanGameScene *scene = SceneInfo.scenes[i];

        for(int j = 0; j < stbds_arrlen(scene->objects); j++) {
            DE_ObjectDeleteObject(scene->objects[i]);
        }

        ecs_fini(scene->world);
        DE_Mem_Delete(scene->name);
        DE_Mem_Delete(scene);
    }
}

/////////////////////////////////////////////////
// Constructor and destructor
////////////////////////////////////////////////

DeccanGameScene *DE_SceneNewScene(const char *name) {
    DeccanGameScene *scene = DE_Mem_New(sizeof(DeccanGameScene), 1);

    scene->name = DE_String_New(name);
    scene->is_paused = false;
    scene->objects = NULL;
    scene->components = NULL;
    scene->world = ecs_init();

    scene->is_first_frame = true;
    scene->AtFirstFrame = NULL_VOIDFUNC;
    scene->AtStep = NULL_VOIDFUNC;
    scene->AtRender = NULL_VOIDFUNC;
    scene->AtEnd = NULL_VOIDFUNC;

    ecs_new_component(scene->world, 0, "DeccanGameObject", sizeof(DeccanGameObject), ECS_ALIGNOF(DeccanGameObject));

    return scene;
}

void DE_SceneAddScene(DeccanGameScene *scene, bool is_replacing) {
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

void DE_SceneRemoveScene() {
    int32_t sceneCount = stbds_arrlen(SceneInfo.scenes);

    if(sceneCount > 1) {
        stbds_arrpop(SceneInfo.scenes);
        SceneInfo.scenes[sceneCount - 1]->is_paused = false;
    }
}

/////////////////////////////////////////////////
// Object handling
////////////////////////////////////////////////

void DE_SceneInstantiateObject(DeccanGameObject *object) {
    if(object == NULL) return;
    DeccanGameScene *scene = DE_SceneCurrentScene();
    stbds_arrput(scene->objects, object);
}

DeccanGameObject *DE_SceneGetObject(const char *name) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    ecs_entity_t obj = ecs_lookup(scene->world, name);
    return ecs_get_mut_w_entity(scene->world, obj, ecs_lookup(scene->world, "DeccanGameObject"), NULL);
}

void DE_SceneIterateObject(void (*func)(DeccanGameObject *this)) {
    DeccanGameScene *scene = DE_SceneCurrentScene();

    ecs_query_t *query = ecs_query_new(scene->world, "DeccanGameObject");
    ecs_iter_t it = ecs_query_iter(query);

    while(ecs_query_next(&it)) {
        DeccanGameObject *obj = ecs_column_w_size(&it, sizeof(DeccanGameObject), 1);

        for(int i = 0; i < it.count; i++) {
            func(&obj[i]);
        }
    }
}

void DE_SceneIterateObjectOfType(const char *tag, void (*func)(DeccanGameObject *this)) {
    DeccanGameScene *scene = DE_SceneCurrentScene();

    ecs_query_t *query = ecs_query_new(scene->world, "DeccanGameObject");
    ecs_iter_t it = ecs_query_iter(query);

    while(ecs_query_next(&it)) {
        DeccanGameObject *obj = ecs_column_w_size(&it, sizeof(DeccanGameObject), 1);

        for(int i = 0; i < it.count; i++) {
            if(DE_ObjectHasTag(&obj[i], tag)) {
                func(&obj[i]);
            }
        }
    }
}

/////////////////////////////////////////////////
// Scene status
////////////////////////////////////////////////

DeccanGameScene *DE_SceneCurrentScene() {
    return SceneInfo.scenes[stbds_arrlen(SceneInfo.scenes) - 1];
}

void DE_ScenePauseScene(bool pause) {
    SceneInfo.scenes[stbds_arrlen(SceneInfo.scenes) - 1]->is_paused = pause;
}

bool DE_SceneIsScenePaused() {
    return SceneInfo.scenes[stbds_arrlen(SceneInfo.scenes) - 1]->is_paused;
}
