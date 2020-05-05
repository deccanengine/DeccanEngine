/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "object.h"

#define void_func(x) void (*x)(void)

typedef struct DE_GameScene {
    char *name;
    bool is_paused;
    bool is_first_frame;

    DE_GameObject **objects;
    int object_count;

    void_func(AtFirstFrame);
    void_func(AtStep);
    void_func(AtRender);
    void_func(AtEnd);
} DE_GameScene;

DE_GameScene *DE_Scene_NewScene(const char *name, void_func(af), void_func(as), void_func(ar), void_func(ae));
void DE_Scene_AddScene(DE_GameScene *scene, bool is_replacing);
void DE_Scene_RemoveScene();

DE_GameScene *DE_Scene_CurrentScene();
void DE_Scene_PauseScene(bool pause);
bool DE_Scene_IsScenePaused();

#undef void