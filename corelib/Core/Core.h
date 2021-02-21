/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once

#include "../Config.h"
#include "Utils.h"
#include "String.h"
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

int  DE_CoreInit(DeccanSettings *settings);
void DE_CoreQuit(void);
void DE_CoreUpdate(float fpsAverage, float deltaTime);
void DE_CoreSetTitle(const char *name);
void DE_CoreSetResolution(vec2 mode);
void DE_CoreToogleFullscreen(void);
void DE_CoreToogleVsync(bool vsync);
void DE_CoreSetFramerateLimit(float fps);
const char *DE_CoreGetTitle(void);
void DE_CoreGetResolution(vec2 res);
bool DE_CoreIsFullscreened(void);
bool DE_CoreIsVsyncEnabled(void);
bool DE_CoreIsResizable(void);
bool DE_CoreIsRunning(void);
float DE_CoreGetFramerateLimit(void);
float DE_CoreGetAverageFramerate(void);
float DE_CoreGetDeltaTime(void);
SDL_Window *DE_CoreGetWindowHandle(void);
DeccanVarManager *DE_CoreGetVarManager(void);
DeccanSettings *DE_CoreGetSettings(void);

