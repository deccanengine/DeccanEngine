#pragma once

#include "config.h"
#include "input.h"
#include "utils/log.h"
#include "utils/timer.h"

typedef struct {
    char *name;

    bool is_paused;
    bool is_first_frame;

    state_func_ptr(at_begining);
    state_func_ptr(at_step);
    state_func_ptr(at_end);
} deccan_Scene;

typedef struct deccan_Info {
    /* Core engine */
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool is_running;

    /* Settings */
    bool is_fullscreen;
    float required_fps;

    /* Input system */
    SDL_Event event;
    uint8_t *key_states;

    /* Scene manager */
    deccan_Scene **scenes;

    /* Asset manager */
    struct {
        char *key;
        SDL_Texture *value;
    } *textures;
} deccan_Info;

void _priv_Core_set_global_engine(deccan_Info *engine);
deccan_Info *_priv_Core_get_global_engine();

int  _priv_Core_init(const char *title, int32_t width, int32_t height);
void _priv_Core_quit();
void _priv_Core_run(float fps);

void _priv_Core_set_mode(int32_t width, int32_t height);
void _priv_Core_set_fullscreen();
void _priv_Core_set_framerate_limit(float fps);

bool _priv_Core_get_fullscreen_status();
float _priv_Core_get_framerate_limit();

typedef struct _priv_Core {
    void (*set_global_engine)(deccan_Info *engine);
    deccan_Info* (*get_global_engine)();

    int  (*init)(const char *title, int32_t width, int32_t height);
    void (*quit)();
    void (*run)(float fps);

    void (*set_mode)(int32_t width, int32_t height);
    void (*set_fullscreen)();
    void (*set_framerate_limit)(float fps);

    bool  (*get_fullscreen_status)();
    float (*get_framerate_limit)();
} _priv_Core;

static _priv_Core deccan_Core = {
    _priv_Core_set_global_engine, 
    _priv_Core_get_global_engine,
    _priv_Core_init,
    _priv_Core_quit,
    _priv_Core_run,
    _priv_Core_set_mode,
    _priv_Core_set_fullscreen,
    _priv_Core_set_framerate_limit,
    _priv_Core_get_fullscreen_status,
    _priv_Core_get_framerate_limit
};

deccan_Scene *_priv_Scene_new_scene(const char *name, state_func_ptr(ab), state_func_ptr(as), state_func_ptr(ae));
void _priv_Scene_add_scene(deccan_Scene *scene, bool is_replacing);
void _priv_Scene_remove_scene();

deccan_Scene *_priv_Scene_current_scene();
void _priv_Scene_pause_scene(bool pause);
bool _priv_Scene_is_scene_paused();

typedef struct _priv_Scene {
    deccan_Scene *(*new_scene)(const char *name, state_func_ptr(ab), state_func_ptr(as), state_func_ptr(ae));
    void (*add_scene)(deccan_Scene *scene, bool is_replacing);
    void (*remove_scene)();

    deccan_Scene *(*current_scene)();
    void (*pause_scene)(bool pause);
    bool (*is_scene_paused)();
} _priv_Scene;

static _priv_Scene deccan_Scenes = {
    _priv_Scene_new_scene,
    _priv_Scene_add_scene,
    _priv_Scene_remove_scene,
    _priv_Scene_current_scene,
    _priv_Scene_pause_scene,
    _priv_Scene_is_scene_paused
};