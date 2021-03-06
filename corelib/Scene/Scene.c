/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Scene.h"
#include "Flecs.h"

static struct {
    DeccanGameScene **scenes;

    bool is_adding;
    bool is_removing;
    bool is_replacing;
    DeccanGameScene *changed_scene;
} SceneInfo = {.scenes = NULL, .is_adding = false, .is_removing = false, .changed_scene = NULL};

/////////////////////////////////////////////////
// Scene internals
////////////////////////////////////////////////

DeccanGameScene **DE_SceneGetSceneArray(void) {
    return SceneInfo.scenes;
}

int DE_SceneGetSceneCount(void) {
    return stbds_arrlen(SceneInfo.scenes);
}

void DE_SceneFreeAll(void) {
    stbds_arrfree(SceneInfo.scenes);
}

void RegisterBaseComponent(DeccanGameScene *scene) {
    DE_FlecsRegisterComponent("Info", sizeof(DeccanObjectInfo), ECS_ALIGNOF(DeccanObjectInfo));
}

void ObjectFirstFrame(DeccanGameObject object) {
    DeccanObjectInfo *info = DE_ObjectGetComponent(object, "Info");
    info->AtFirstFrame(object);
}

void DE_SceneUpdate(void) {
    /* Add or remove scene (only one) */
    DE_SceneMakeChanges();

    /* Process Scene(s) and DeccanGameObject (s) */
    DeccanGameScene *scene = DE_SceneCurrentScene(); /* Current scene */

    /* First frame of the scene. Same as at_beginning for scene */
    if (scene->is_first_frame == true) {
        RegisterBaseComponent(scene);

        scene->AtFirstFrame();
        scene->is_first_frame = false;

        /* First frame of objects */
        DE_SceneIterateObject(ObjectFirstFrame);
    }

    /* AtStep of scenes and objects */
    scene->AtStep();
    ecs_progress(scene->world, 0);
    DE_SceneIterateObject(DE_ObjectUpdate);
    
    /* AtRender of scenes and objects */
    scene->AtRender();
    DE_SceneIterateObject(DE_ObjectRender);
}

void DE_SceneQuit(void) {
    /* at_end of scenes and objects */
    DeccanGameScene *currentScene = DE_SceneCurrentScene();
    currentScene->AtEnd();

    DE_SceneIterateObject(DE_ObjectEnd);

    /* Dellocate everything */
    for (int i = 0; i < stbds_arrlen(SceneInfo.scenes); i++) {
        DeccanGameScene *scene = SceneInfo.scenes[i];

        DE_SceneIterateObject(DE_ObjectDeleteObject);

        ecs_fini(scene->world);
        DE_Free(scene->name);
        DE_Free(scene);
    }
}

/////////////////////////////////////////////////
// Constructor and destructor
////////////////////////////////////////////////

void SceneNoneFunc(void) {
}

DeccanGameScene *DE_SceneNewScene(const char *name) {
    DeccanGameScene *scene = DE_Alloc(sizeof(DeccanGameScene), 1);

    scene->name = DE_StringNew(name);
    scene->is_paused = false;
    scene->world = ecs_init();

    scene->is_first_frame = true;
    scene->AtFirstFrame = SceneNoneFunc;
    scene->AtStep = SceneNoneFunc;
    scene->AtRender = SceneNoneFunc;
    scene->AtEnd = SceneNoneFunc;

    return scene;
}

void DE_SceneAddScene(DeccanGameScene *scene, bool is_replacing) {
    if (scene == NULL) {
        DE_WARN("Invalid scene data");
        return;
    }

    SceneInfo.changed_scene = scene;
    SceneInfo.is_replacing = is_replacing;
    SceneInfo.is_adding = true;
}

void DE_SceneRemoveScene(void) {
    SceneInfo.is_removing = true;
}

void DE_SceneMakeChanges(void) {
    int32_t sceneCount = stbds_arrlen(SceneInfo.scenes);
    if (SceneInfo.is_adding) {
        SceneInfo.is_adding = false;

        if (sceneCount != 0) {
            if (SceneInfo.is_replacing) {
                stbds_arrpop(SceneInfo.scenes);
            }
            else {
                SceneInfo.scenes[sceneCount - 1]->is_paused = true;
            }
        }

        if (stbds_arrput(SceneInfo.scenes, SceneInfo.changed_scene) != SceneInfo.changed_scene) {
            DE_WARN("Cannot add scene: %s", SceneInfo.changed_scene->name);
        }
    }
    else if (SceneInfo.is_removing) {
        SceneInfo.is_removing = false;

        if (sceneCount > 1) {
            stbds_arrpop(SceneInfo.scenes);
            SceneInfo.scenes[sceneCount - 1]->is_paused = false;
        }
    }
}

/////////////////////////////////////////////////
// Object handling
////////////////////////////////////////////////

void DE_SceneInstantiateObject(DeccanGameObject object) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    ecs_remove_entity(scene->world, object.entity, EcsPrefab);
}

DeccanGameObject DE_SceneGetObject(const char *name) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    ecs_entity_t obj = ecs_lookup(scene->world, name);

    DeccanGameObject object;
    object.entity = obj;
    return object;
}

void DE_SceneIterateObject(void (*func)(DeccanGameObject this)) {
    DeccanGameScene *scene = DE_SceneCurrentScene();

    ecs_query_t *query = ecs_query_new(scene->world, "Info");
    ecs_iter_t it = ecs_query_iter(query);

    while (ecs_query_next(&it)) {
        for (int i = 0; i < it.count; i++) {
            ecs_entity_t entity = it.entities[i];

            DeccanGameObject object;
            object.entity = entity;

            func(object);
        }
    }
}

void DE_SceneIterateObjectOfType(const char *tag, void (*func)(DeccanGameObject this)) {
    DeccanGameScene *scene = DE_SceneCurrentScene();

    ecs_query_t *query = ecs_query_new(scene->world, "Info");
    ecs_iter_t it = ecs_query_iter(query);

    while (ecs_query_next(&it)) {
        for (int i = 0; i < it.count; i++) {
            ecs_entity_t entity = it.entities[i];

            DeccanGameObject object;
            object.entity = entity;

            if (DE_ObjectHasTag(object, tag)) {
                func(object);
            }
        }
    }
}

/////////////////////////////////////////////////
// Scene status
////////////////////////////////////////////////

DeccanGameScene *DE_SceneCurrentScene(void) {
    return SceneInfo.scenes[stbds_arrlen(SceneInfo.scenes) - 1];
}

void DE_ScenePauseScene(bool pause) {
    SceneInfo.scenes[stbds_arrlen(SceneInfo.scenes) - 1]->is_paused = pause;
}

bool DE_SceneIsScenePaused(void) {
    return SceneInfo.scenes[stbds_arrlen(SceneInfo.scenes) - 1]->is_paused;
}

DE_IMPL void DE_SceneSetCamera(DeccanCamera *camera) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    scene->camera = camera;
}

DE_IMPL DeccanCamera *DE_SceneGetCamera() {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    return scene->camera;
}
