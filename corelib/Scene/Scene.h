/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "../Core/Memory.h"
#include "Object.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct DeccanComponent {
    char *key;
    ecs_entity_t id;
    size_t size;
} DeccanComponent;

typedef struct GameScene {
    char *name;
    bool is_paused;
    bool is_first_frame;

    ecs_world_t *world;

    GameObject **objects;
    DeccanComponent *components;

    void (*AtFirstFrame)(void);
    void (*AtStep)(void);
    void (*AtRender)(void);
    void (*AtEnd)(void);
} GameScene;

static inline void NULL_VOIDFUNC() { }

/////////////////////////////////////////////////
// Scene internals
////////////////////////////////////////////////

GameScene **Scene_GetSceneArray();
int Scene_GetSceneCount();
void Scene_FreeAll();
void Scene_Update();
void Scene_Quit();

/////////////////////////////////////////////////
// Constructor and destructor
////////////////////////////////////////////////

GameScene *Scene_NewScene(const char *name);
void Scene_AddScene(GameScene *scene, bool is_replacing);
void Scene_RemoveScene();

/////////////////////////////////////////////////
// Object handling
////////////////////////////////////////////////

void Scene_InstantiateObject(GameObject *object);
GameObject *Scene_GetObject(const char *name);
void Scene_IterateObject(void (*func)(GameObject *this));
void Scene_IterateObjectOfType(const char *type, void (*func)(GameObject *this));

/////////////////////////////////////////////////
// Scene status
////////////////////////////////////////////////

GameScene *Scene_CurrentScene();
void Scene_PauseScene(bool pause);
bool Scene_IsScenePaused();
