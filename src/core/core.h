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

#ifdef DECCAN_REPORTS_ENABLED
FILE *DE_logfile;
#endif

typedef struct Deccan_Info {
    /* Core engine */
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool is_running;

    /* Settings */
    Deccan_Vector2i win_mode;
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

void DE_Core_set_global_engine(Deccan_Info *engine);
Deccan_Info *DE_Core_get_global_engine();

int  DE_Core_init(const char *title, Deccan_Vector2i mode);
void DE_Core_quit();
void DE_Core_run(float fps);

void DE_Core_set_title(const char *name);
void DE_Core_set_mode(Deccan_Vector2i mode);
void DE_Core_set_fullscreen();
void DE_Core_set_vsync_status(bool vsync);
void DE_Core_set_framerate_limit(float fps);

const char *DE_Core_get_title();
Deccan_Vector2i DE_Core_get_mode();
bool DE_Core_get_fullscreen_status();
bool DE_Core_get_vsync_status();
float DE_Core_get_framerate_limit();
float DE_Core_get_average_framerate();

#ifdef __STDC__

    typedef struct DE_Core {
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
    } DE_Core;

    static DE_Core Deccan_Core = {
        DE_Core_set_global_engine, 
        DE_Core_get_global_engine,
        
        DE_Core_init,
        DE_Core_quit,
        DE_Core_run,
        
        DE_Core_set_title,
        DE_Core_set_mode,
        DE_Core_set_fullscreen,
        DE_Core_set_vsync_status,
        DE_Core_set_framerate_limit,

        DE_Core_get_title,
        DE_Core_get_mode,
        DE_Core_get_fullscreen_status,
        DE_Core_get_vsync_status,
        DE_Core_get_framerate_limit,
        DE_Core_get_average_framerate
    };

#elif __cplusplus

#endif