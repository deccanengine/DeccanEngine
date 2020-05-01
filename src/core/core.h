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
#include "../physics/shape.h"
#include "../utils/message.h"
#include "../utils/timer.h"
#include "../utils/vector.h"

#ifdef DECCAN_REPORTS_ENABLED
FILE *DE_logfile;
#endif

#ifndef DECCAN_MSG_LENGTH
    #define DECCAN_MSG_LENGTH 50
#endif

#ifndef DECCAN_MSG_COUNT
    #define DECCAN_MSG_COUNT 100
#endif

typedef struct DE_Info {
    /* Core engine */
    SDL_Window *window;
    SDL_Renderer *renderer;
    DE_Texture *target;
    bool is_running;

    /* Settings */
    DE_Vector2i win_mode;
    bool is_fullscreen;
    bool vsync_enabled;
    float fps_req;
    float fps_avg;

    /* Input system */
    SDL_Event event;
    uint8_t curr_keys [SDL_NUM_SCANCODES];
    uint8_t prev_keys [SDL_NUM_SCANCODES];

    /* Scene manager */
    DE_Scene **scenes;
    int scene_count;

    /* Asset manager */
    struct {
        char *key;
        SDL_Texture *value;
    } *textures;

    /* Messaging */
    DE_MsgBuf msg;

    /* Renderer */
    DE_Vector2i camera;
    DE_PosRect  camera_bounds;
} DE_Info;

void DE_Core_set_global_engine(DE_Info *engine);
DE_Info *DE_Core_get_global_engine();

int  DE_Core_init(const char *title, DE_Vector2i mode);
void DE_Core_quit();
void DE_Core_run(float fps);

void DE_Core_set_title(const char *name);
void DE_Core_set_mode(DE_Vector2i mode);
void DE_Core_set_fullscreen();
void DE_Core_set_vsync_status(bool vsync);
void DE_Core_set_framerate_limit(float fps);

const char *DE_Core_get_title();
DE_Vector2i DE_Core_get_mode();
bool DE_Core_get_fullscreen_status();
bool DE_Core_get_vsync_status();
float DE_Core_get_framerate_limit();
float DE_Core_get_average_framerate();

void DE_Core_send_message(const char *msg);
bool DE_Core_receive_message(const char *msg);