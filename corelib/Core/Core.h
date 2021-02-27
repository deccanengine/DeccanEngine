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

DE_API int DE_CoreInit(DeccanSettings *settings);
DE_API void DE_CoreQuit(void);
DE_API void DE_CoreUpdate(float fpsAverage, float deltaTime);
DE_API void DE_CoreSetTitle(const char *name);
DE_API void DE_CoreSetResolution(vec2 mode);
DE_API void DE_CoreToogleFullscreen(void);
DE_API void DE_CoreToogleVsync(bool vsync);
DE_API void DE_CoreSetFramerateLimit(float fps);
DE_API const char *DE_CoreGetTitle(void);
DE_API void DE_CoreGetResolution(vec2 res);
DE_API bool DE_CoreIsFullscreened(void);
DE_API bool DE_CoreIsVsyncEnabled(void);
DE_API bool DE_CoreIsResizable(void);
DE_API bool DE_CoreIsRunning(void);
DE_API float DE_CoreGetFramerateLimit(void);
DE_API float DE_CoreGetAverageFramerate(void);
DE_API float DE_CoreGetDeltaTime(void);
DE_API uint32_t DE_CoreProcessStartTime(void);
DE_API SDL_Window *DE_CoreGetWindowHandle(void);
DE_API DeccanVarManager *DE_CoreGetVarManager(void);
DE_API DeccanSettings *DE_CoreGetSettings(void);
