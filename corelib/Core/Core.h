/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once

#include "../Config.h"
#include "Memory.h"
#include "Timer.h"
#include "Variable.h"

#ifndef DECCAN_MSG_LENGTH
    #define DECCAN_MSG_LENGTH 50
#endif

#ifndef DECCAN_MSG_COUNT
    #define DECCAN_MSG_COUNT 100
#endif
/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct DeccanSettings {
    char *title;
    vec2 resolution;
    bool fullscreen;
    bool vsync;
    bool resizable;
    bool closeOnEscape;
    float fps;
} DeccanSettings;

/////////////////////////////////////////////////
// Core functions
////////////////////////////////////////////////

int  Core_Init(DeccanSettings *settings);
void Core_Quit();
void DE_Core_Update(float fpsAverage, float deltaTime);
void Core_SetTitle(const char *name);
void Core_SetResolution(vec2 mode);
void Core_ToogleFullscreen();
void Core_ToogleVsync(bool vsync);
void Core_SetFramerateLimit(float fps);
const char *Core_GetTitle();
void Core_GetResolution(vec2 res);
bool Core_IsFullscreened();
bool Core_IsVsyncEnabled();
bool Core_IsResizable();
bool Core_IsRunning();
float Core_GetFramerateLimit();
float Core_GetAverageFramerate();
float Core_GetDeltaTime();
SDL_Window *DE_Core_GetWindowHandle();
DeccanVarManager *DE_Core_GetVarManager();
DeccanSettings *DE_Core_GetSettings();

