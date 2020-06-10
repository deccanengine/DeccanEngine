/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once

#include "Config.h"
#include "Timer.h"
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