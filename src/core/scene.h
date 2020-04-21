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

typedef struct Deccan_Scene {
    char *name;

    bool is_paused;
    bool is_first_frame;

    Deccan_GameObject **objects;
    int object_count;

    void_func(at_first_frame);
    void_func(at_step);
    void_func(at_render);
    void_func(at_end);
} Deccan_Scene;

Deccan_Scene *_priv_Scene_new_scene(const char *name, void_func(af), void_func(as), void_func(ar), void_func(ae));
void _priv_Scene_add_scene(Deccan_Scene *scene, bool is_replacing);
void _priv_Scene_remove_scene();

Deccan_Scene *_priv_Scene_current_scene();
void _priv_Scene_pause_scene(bool pause);
bool _priv_Scene_is_scene_paused();

#ifdef __STDC__

    typedef struct _priv_Scenes {
        Deccan_Scene *(*new_scene)(const char *name, void_func(af), void_func(as), void_func(ar), void_func(ae));
        void (*add_scene)(Deccan_Scene *scene, bool is_replacing);
        void (*remove_scene)();

        Deccan_Scene *(*current_scene)();
        void (*pause_scene)(bool pause);
        bool (*is_scene_paused)();
    } _priv_Scenes;

    static _priv_Scenes Deccan_Scenes = {
        _priv_Scene_new_scene,
        _priv_Scene_add_scene,
        _priv_Scene_remove_scene,
        _priv_Scene_current_scene,
        _priv_Scene_pause_scene,
        _priv_Scene_is_scene_paused
    };

#elif __cplusplus

#endif

#undef void_func