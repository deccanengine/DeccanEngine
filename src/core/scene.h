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

typedef struct DE_Scene {
    char *name;

    bool is_paused;
    bool is_first_frame;

    DE_GameObject **objects;
    int object_count;

    void_func(at_first_frame);
    void_func(at_step);
    void_func(at_render);
    void_func(at_end);
} DE_Scene;

DE_Scene *DE_Scenes_new_scene(const char *name, void_func(af), void_func(as), void_func(ar), void_func(ae));
void DE_Scenes_add_scene(DE_Scene *scene, bool is_replacing);
void DE_Scenes_remove_scene();

DE_Scene *DE_Scenes_current_scene();
void DE_Scenes_pause_scene(bool pause);
bool DE_Scenes_is_scene_paused();

#undef void