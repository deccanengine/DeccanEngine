/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "../Core/Module/Module.h"
#include "../Core/Utils.h"
#include "../Core/String.h"
#include "../World/Camera.h"
#include "Object.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct DeccanDeccanGameScene {
    char *name;
    bool is_paused;
    bool is_first_frame;

    ecs_world_t *world;
    DeccanCamera *camera;

    DeccanModuleSys modsys;
} DeccanGameScene;

/////////////////////////////////////////////////
// Scene internals
////////////////////////////////////////////////

DE_API DeccanGameScene **DE_SceneGetSceneArray(void);
DE_API int DE_SceneGetSceneCount(void);
DE_API void DE_SceneFreeAll(void);
DE_API void DE_SceneUpdate(void);
DE_API void DE_SceneQuit(void);

/////////////////////////////////////////////////
// Constructor and destructor
////////////////////////////////////////////////

DE_API DeccanGameScene *DE_SceneNewScene(const char *name);
DE_API void DE_SceneAddScene(DeccanGameScene *scene, bool is_replacing);
DE_API void DE_SceneRemoveScene(void);
DE_API void DE_SceneMakeChanges(void);

/////////////////////////////////////////////////
// Module systems
////////////////////////////////////////////////

DE_API void DE_ScenePushModule(DeccanGameScene *scene, DeccanModule *mod);

/////////////////////////////////////////////////
// Object handling
////////////////////////////////////////////////

DE_API void DE_SceneInstantiateObject(DeccanGameObject object);
DE_API DeccanGameObject DE_SceneGetObject(const char *name);
DE_API void DE_SceneIterateObject(void (*func)(DeccanGameObject this));
DE_API void DE_SceneIterateObjectOfType(const char *type, void (*func)(DeccanGameObject this));

/////////////////////////////////////////////////
// Scene status
////////////////////////////////////////////////

DE_API DeccanGameScene *DE_SceneCurrentScene(void);
DE_API void DE_ScenePauseScene(bool pause);
DE_API bool DE_SceneIsScenePaused(void);

DE_API void DE_SceneSetCamera(DeccanCamera *camera);
DE_API DeccanCamera *DE_SceneGetCamera(void);
