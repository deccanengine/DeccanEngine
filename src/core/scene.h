#pragma once
#include "../config.h"
#include "core.h"

typedef struct Deccan_Scene Deccan_Scene;

Deccan_Scene *_priv_Scene_new_scene(const char *name, state_func_ptr(ab), state_func_ptr(as), state_func_ptr(ae));
void _priv_Scene_add_scene(Deccan_Scene *scene, bool is_replacing);
void _priv_Scene_remove_scene();

Deccan_Scene *_priv_Scene_current_scene();
void _priv_Scene_pause_scene(bool pause);
bool _priv_Scene_is_scene_paused();

typedef struct _priv_Scenes {
    Deccan_Scene *(*new_scene)(const char *name, state_func_ptr(ab), state_func_ptr(as), state_func_ptr(ae));
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