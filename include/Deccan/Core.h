/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once

#include <Deccan/Config.h>
#include <Deccan/Scene.h>
#include <Deccan/Object.h>

typedef Color Color;

#ifndef DECCAN_MSG_LENGTH
    #define DECCAN_MSG_LENGTH 50
#endif

#ifndef DECCAN_MSG_COUNT
    #define DECCAN_MSG_COUNT 100
#endif

typedef struct GameInfo {
    /* Core engine */
#ifdef DECCAN_RENDERER_SDL
    SDL_Window *window;
    SDL_Renderer *renderer;
#else

#endif
    RawTexture *target;
    int gl_major;
    int gl_minor;
    bool is_running;

#ifdef DECCAN_REPORTS_ENABLED
    FILE *logfile;
#endif

    /* Settings */
    Vector2i win_mode;
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
    GameScene **scenes;
    int scene_count;

    /* Asset manager */
    struct {
        char *key;
        SDL_Texture *value;
    } *textures;

    struct {
        char *key;
        TTF_Font *value;
    } *fonts;

    /* Messaging */
    msgbuf msg;

    /* Renderer */
    Vector2f camera;
    PosRect  camera_bounds;
    struct {
        int type; 
        union {
            RawTexture *texture;
            Color color;
        };
    } background;
} GameInfo;

/* Core functions */
void Core_SetGlobalInfo(GameInfo *engine);
GameInfo *Core_GetGlobalInfo();
int  Core_Init(const char *title, Vector2i mode);
void Core_Quit();
void Core_Run(float fps);
void Core_SetTitle(const char *name);
void Core_SetMode(Vector2i mode);
void Core_SetFullscreen();
void Core_SetVsyncStatus(bool vsync);
void Core_SetFramerateLimit(float fps);
const char *Core_GetTitle();
Vector2i Core_GetMode();
bool Core_GetFullscreenStatus();
bool Core_GetVsyncStatus();
float Core_GetFramerateLimit();
float Core_GetAverageFramerate();
int32_t Core_GetTotalFrameCount();
float Core_GetDeltaTime();
void Core_SendMessage(const char *msg);
bool Core_ReceiveMessage(const char *msg);

/* Asset Manager */
void Asset_LoadTexture(const char *name, const char *path);
SDL_Texture *Asset_GetTexture(const char *name);
void Asset_LoadFont(const char *name, const char *path);
TTF_Font *Asset_GetFont(const char *name);

/* Camera */
void Camera_Move(Vector2f pos);
void Camera_CenterOn(GameObject *obj);
void Camera_SetPosition(Vector2f pos);
void Camera_SetBounds(PosRect rect);
Vector2f Camera_GetPosition();
PosRect  Camera_GetBounds();