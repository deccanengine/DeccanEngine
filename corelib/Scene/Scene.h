/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "../Core/Utils.h"
#include "../Core/String.h"
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

    void (*AtFirstFrame)(void);
    void (*AtStep)(void);
    void (*AtRender)(void);
    void (*AtEnd)(void);
} DeccanGameScene;

/////////////////////////////////////////////////
// Scene internals
////////////////////////////////////////////////

DeccanGameScene **DE_SceneGetSceneArray();
int DE_SceneGetSceneCount();
void DE_SceneFreeAll();
void DE_SceneUpdate();
void DE_SceneQuit();

/////////////////////////////////////////////////
// Constructor and destructor
////////////////////////////////////////////////

DeccanGameScene *DE_SceneNewScene(const char *name);
void DE_SceneAddScene(DeccanGameScene *scene, bool is_replacing);
void DE_SceneRemoveScene();

/////////////////////////////////////////////////
// Object handling
////////////////////////////////////////////////

void DE_SceneInstantiateObject(DeccanGameObject object);
DeccanGameObject DE_SceneGetObject(const char *name);
void DE_SceneIterateObject(void (*func)(DeccanGameObject this));
void DE_SceneIterateObjectOfType(const char *type, void (*func)(DeccanGameObject this));

/////////////////////////////////////////////////
// Scene status
////////////////////////////////////////////////

DeccanGameScene *DE_SceneCurrentScene();
void DE_ScenePauseScene(bool pause);
bool DE_SceneIsScenePaused();
