/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once

#include "Config.h"
#include "Timer.h"
#include "Structures.h"
#include "Scene/Scene.h"
#include "Scene/Object.h"

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

/////////////////////////////////////////////////
// Core functions
////////////////////////////////////////////////

int  Core_Init(CoreSettings *settings);
void Core_Quit();
void Core_Run();
void Core_SetTitle(const char *name);
void Core_SetResolution(Vector2 mode);
void Core_ToogleFullscreen();
void Core_ToogleVsync(bool vsync);
void Core_SetFramerateLimit(float fps);
const char *Core_GetTitle();
Vector2 Core_GetResolution();
bool Core_IsFullscreened();
bool Core_IsVsyncEnabled();
bool Core_IsResizable();
float Core_GetFramerateLimit();
float Core_GetAverageFramerate();
int32_t Core_GetTotalFrameCount();
float Core_GetDeltaTime();
//DeccanVarManager *DE_Core_GetVarManager();
