/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Scene.h"
#include "../World/Flecs.h"

DE_PRIV struct {
    DeccanArray scenes;

    bool is_adding;
    bool is_removing;
    bool is_replacing;
    DeccanGameScene *changed_scene;
} SceneInfo = {.scenes = NULL, .is_adding = false, .is_removing = false, .changed_scene = NULL};

/////////////////////////////////////////////////
// Scene internals
////////////////////////////////////////////////

DE_IMPL void DE_SceneSysCreate(void) {
    DE_ArrayCreate(&SceneInfo.scenes);
}

DE_IMPL DeccanGameScene **DE_SceneGetSceneArray(void) {
    return (DeccanGameScene **)SceneInfo.scenes.data;
}

DE_IMPL int DE_SceneGetSceneCount(void) {
    return SceneInfo.scenes.length;
}

DE_IMPL void DE_SceneFreeAll(void) {
    DE_ArrayDestroy(&SceneInfo.scenes);
}

DE_IMPL void RegisterBaseComponent(DeccanGameScene *scene) {
    DE_FlecsRegisterComponent("Info", sizeof(DeccanObjectInfo), ECS_ALIGNOF(DeccanObjectInfo));
}

DE_IMPL void ObjectFirstFrame(DeccanGameObject object) {
    DeccanObjectInfo *info = DE_ObjectGetComponent(object, "Info");
    info->AtFirstFrame(object);
}

DE_IMPL void DE_SceneUpdate(void) {
    /* Add or remove scene (only one) */
    DE_SceneMakeChanges();

    /* Process Scene(s) and DeccanGameObject (s) */
    DeccanGameScene *scene = DE_SceneCurrentScene(); /* Current scene */

    /* First frame of the scene. Same as at_beginning for scene */
    if (scene->is_first_frame == true) {
        RegisterBaseComponent(scene);
        DE_ModuleSysIter(&scene->modsys, DE_SHELL_ATBEGINNING, true);
        DE_SceneIterateObject(ObjectFirstFrame);

        scene->is_first_frame = false;
    }

    /* AtStep of scenes and objects */
    DE_ModuleSysIter(&scene->modsys, DE_SHELL_ATSTEP, true);
    DE_FlecsUpdateWorld();
    DE_SceneIterateObject(DE_ObjectUpdate);

    /* AtPostStep (AtRender) of scenes and objects */
    DE_SceneIterateObject(DE_ObjectRender);
    DE_ModuleSysIter(&scene->modsys, DE_SHELL_ATPOSTSTEP, false);
}

DE_IMPL void DE_SceneQuit(void) {
    /* AtEnd of scenes and objects */
    DeccanGameScene *scene = DE_SceneCurrentScene();

    DE_ModuleSysIter(&scene->modsys, DE_SHELL_ATEND, false);
    DE_SceneIterateObject(DE_ObjectEnd);

    DE_ModuleSysDestroy(&scene->modsys);

    /* Dellocate everything */
    for (int i = 0; i < SceneInfo.scenes.length; i++) {
        DeccanGameScene *scene = SceneInfo.scenes.data[i];

        DE_SceneIterateObject(DE_ObjectDeleteObject);

        ecs_fini(scene->world);
        DE_Free(scene->name);
        DE_Free(scene);
    }
}

/////////////////////////////////////////////////
// Constructor and destructor
////////////////////////////////////////////////

DE_IMPL void SceneNoneFunc(void) {
}

DE_IMPL DeccanGameScene *DE_SceneNewScene(const char *name) {
    DeccanGameScene *scene = DE_Alloc(sizeof(DeccanGameScene), 1);
    scene->name = DE_StringNew(name);
    scene->is_paused = false;
    scene->world = ecs_init();
    scene->is_first_frame = true;

    DE_ModuleSysCreate(&scene->modsys);

    return scene;
}

DE_IMPL void DE_SceneAddScene(DeccanGameScene *scene, bool is_replacing) {
    if (scene == NULL) {
        DE_WARN("Invalid scene data");
        return;
    }

    SceneInfo.changed_scene = scene;
    SceneInfo.is_replacing = is_replacing;
    SceneInfo.is_adding = true;
}

DE_IMPL void DE_SceneRemoveScene(void) {
    SceneInfo.is_removing = true;
}

DE_IMPL void DE_SceneMakeChanges(void) {
    int32_t scene_count = SceneInfo.scenes.length;
    if (SceneInfo.is_adding) {
        SceneInfo.is_adding = false;

        if (scene_count != 0) {
            if (SceneInfo.is_replacing) {
                DE_ArrayRemoveLastItem(&SceneInfo.scenes);
            }
            else {
                DeccanGameScene *scene = SceneInfo.scenes.data[scene_count - 1];
                scene->is_paused = true;
            }
        }

        /* TODO: This should return a boolean? */ 
        DE_ArrayAddItem(&SceneInfo.scenes, (void *)SceneInfo.changed_scene);
    }
    else if (SceneInfo.is_removing) {
        SceneInfo.is_removing = false;

        if (scene_count > 1) {
            DE_ArrayRemoveLastItem(&SceneInfo.scenes);

            DeccanGameScene *scene = SceneInfo.scenes.data[scene_count - 1];
            scene->is_paused = false;
        }
    }
}

/////////////////////////////////////////////////
// Module systems
////////////////////////////////////////////////

DE_IMPL void DE_ScenePushModule(DeccanGameScene *scene, DeccanModule *mod) {
    DE_ModuleSysPush(&scene->modsys, mod);
}

/////////////////////////////////////////////////
// Object handling
////////////////////////////////////////////////

DE_IMPL void DE_SceneInstantiateObject(DeccanGameObject object) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    ecs_remove_entity(scene->world, object.entity, EcsPrefab);
}

DE_IMPL DeccanGameObject DE_SceneGetObject(const char *name) {
    DeccanGameScene *scene = DE_SceneCurrentScene();
    ecs_entity_t obj = ecs_lookup(scene->world, name);

    DeccanGameObject object;
    object.entity = obj;
    return object;
}

DE_IMPL void DE_SceneIterateObject(void (*func)(DeccanGameObject this)) {
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

DE_IMPL void DE_SceneIterateObjectOfType(const char *tag, void (*func)(DeccanGameObject this)) {
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

DE_IMPL DeccanGameScene *DE_SceneCurrentScene(void) {
    return (DeccanGameScene *)DE_ArrayGetLastItem(&SceneInfo.scenes);
}

DE_IMPL void DE_ScenePauseScene(bool pause) {
    DE_SceneCurrentScene()->is_paused = pause;
}

DE_IMPL bool DE_SceneIsScenePaused(void) {
    return DE_SceneCurrentScene()->is_paused;
}

DE_IMPL void DE_SceneSetCamera(DeccanCamera *camera) {
    DE_SceneCurrentScene()->camera = camera;
}

DE_IMPL DeccanCamera *DE_SceneGetCamera(void) {
    return DE_SceneCurrentScene()->camera;
}
