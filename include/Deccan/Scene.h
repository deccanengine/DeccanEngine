/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include <Deccan/Config.h>
#include <Deccan/Object.h>

#define void_func(x) void (*x)(void)

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct GameScene {
    char *name;
    bool is_paused;
    bool is_first_frame;

    GameObject **objects;
    int object_count;

    void_func(AtFirstFrame);
    void_func(AtStep);
    void_func(AtRender);
    void_func(AtEnd);
} GameScene;

/////////////////////////////////////////////////
// Scene internals
////////////////////////////////////////////////

GameScene **Scene_GetSceneArray();
int Scene_GetSceneCount();
void Scene_FreeAll();

/////////////////////////////////////////////////
// Constructor and destructor
////////////////////////////////////////////////

GameScene *Scene_NewScene(const char *name, void_func(af), void_func(as), void_func(ar), void_func(ae));
void Scene_AddScene(GameScene *scene, bool is_replacing);
void Scene_RemoveScene();

/////////////////////////////////////////////////
// Scene status
////////////////////////////////////////////////

GameScene *Scene_CurrentScene();
void Scene_PauseScene(bool pause);
bool Scene_IsScenePaused();

#undef void_func