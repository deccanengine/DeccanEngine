/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once

#include "../config.h"
#include "scene.h"
#include "input.h"
#include "object.h"
#include "../utils/timer.h"
#include "../utils/vector.h"

typedef struct Deccan_Info {
    /* Core engine */
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool is_running;

    /* Settings */
    bool is_fullscreen;
    bool vsync_enabled;
    float fps_req;
    float fps_avg;

    /* Input system */
    SDL_Event event;
    uint8_t curr_keys [SDL_NUM_SCANCODES];
    uint8_t prev_keys [SDL_NUM_SCANCODES];

    /* Scene manager */
    Deccan_Scene **scenes;
    int scene_count;

    /* Asset manager */
    struct {
        char *key;
        SDL_Texture *value;
    } *textures;

    /* Renderer */
    Deccan_Vector2i camera;
} Deccan_Info;

void _priv_Core_set_global_engine(Deccan_Info *engine);
Deccan_Info *_priv_Core_get_global_engine();

int  _priv_Core_init(const char *title, Deccan_Vector2i mode);
void _priv_Core_quit();
void _priv_Core_run(float fps);

void _priv_Core_set_title(const char *name);
void _priv_Core_set_mode(Deccan_Vector2i mode);
void _priv_Core_set_fullscreen();
void _priv_Core_set_vsync_status(bool vsync);
void _priv_Core_set_framerate_limit(float fps);

const char *_priv_Core_get_title();
Deccan_Vector2i _priv_Core_get_mode();
bool _priv_Core_get_fullscreen_status();
bool _priv_Core_get_vsync_status();
float _priv_Core_get_framerate_limit();
float _priv_Core_get_average_framerate();

#ifdef __STDC__

    typedef struct _priv_Core {
        void (*set_global_engine)(Deccan_Info *engine);
        Deccan_Info* (*get_global_engine)();

        int  (*init)(const char *title, Deccan_Vector2i mode);
        void (*quit)();
        void (*run)(float fps);

        void (*set_title)(const char *name);
        void (*set_mode)(Deccan_Vector2i mode);
        void (*set_fullscreen)();
        void (*set_vsync_status)(bool vsync);
        void (*set_framerate_limit)(float fps);

        const char *(*get_title)();
        Deccan_Vector2i (*get_mode)();
        bool  (*get_fullscreen_status)();
        bool  (*get_vsync_status)();
        float (*get_framerate_limit)();
        float (*get_average_framerate)();
    } _priv_Core;

    static _priv_Core Deccan_Core = {
        _priv_Core_set_global_engine, 
        _priv_Core_get_global_engine,
        
        _priv_Core_init,
        _priv_Core_quit,
        _priv_Core_run,
        
        _priv_Core_set_title,
        _priv_Core_set_mode,
        _priv_Core_set_fullscreen,
        _priv_Core_set_vsync_status,
        _priv_Core_set_framerate_limit,

        _priv_Core_get_title,
        _priv_Core_get_mode,
        _priv_Core_get_fullscreen_status,
        _priv_Core_get_vsync_status,
        _priv_Core_get_framerate_limit,
        _priv_Core_get_average_framerate
    };

#elif __cplusplus

#endif