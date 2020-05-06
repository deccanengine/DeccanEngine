/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once

#include "../config.h"
#include "scene.h"
#include "object.h"
#include "../physics/shape.h"
#include "../renderer/color.h"
#include "../utils/message.h"
#include "../utils/timer.h"
#include "../utils/vector.h"

#ifndef DECCAN_MSG_LENGTH
    #define DECCAN_MSG_LENGTH 50
#endif

#ifndef DECCAN_MSG_COUNT
    #define DECCAN_MSG_COUNT 100
#endif

typedef struct DE_GameInfo {
    /* Core engine */
#ifdef DECCAN_RENDERER_SDL
    SDL_Window *window;
    SDL_Renderer *renderer;
#else

#endif
    DE_Texture *target;
    int gl_major;
    int gl_minor;
    bool is_running;

#ifdef DECCAN_REPORTS_ENABLED
    FILE *logfile;
#endif

    /* Settings */
    DE_Vector2i win_mode;
    bool is_fullscreen;
    bool vsync_enabled;
    int32_t frame_count;
    float fps_req;
    float fps_avg;
    float delta_time;

    /* Input system */
    SDL_Event event;
    uint8_t curr_keys [SDL_NUM_SCANCODES];
    uint8_t prev_keys [SDL_NUM_SCANCODES];

    /* Scene manager */
    DE_GameScene **scenes;
    int scene_count;

    /* Asset manager */
    struct {
        char *key;
        SDL_Texture *value;
    } *textures;

    /* Messaging */
    DE_msgbuf msg;

    /* Renderer */
    DE_Vector2f camera;
    DE_PosRect  camera_bounds;
    struct {
        int type; 
        union {
            DE_Texture *texture;
            DE_Color color;
        };
    } background;
} DE_GameInfo;

void DE_Core_SetGlobalInfo(DE_GameInfo *engine);
DE_GameInfo *DE_Core_GetGlobalInfo();

int  DE_Core_Init(const char *title, DE_Vector2i mode);
void DE_Core_Quit();
void DE_Core_Run(float fps);

void DE_Core_SetTitle(const char *name);
void DE_Core_SetMode(DE_Vector2i mode);
void DE_Core_SetFullscreen();
void DE_Core_SetVsyncStatus(bool vsync);
void DE_Core_SetFramerateLimit(float fps);

const char *DE_Core_GetTitle();
DE_Vector2i DE_Core_GetMode();
bool DE_Core_GetFullscreenStatus();
bool DE_Core_GetVsyncStatus();
float DE_Core_GetFramerateLimit();
float DE_Core_GetAverageFramerate();
int32_t DE_Core_GetTotalFrameCount();
float DE_Core_GetDeltaTime();

void DE_Core_SendMessage(const char *msg);
bool DE_Core_ReceiveMessage(const char *msg);