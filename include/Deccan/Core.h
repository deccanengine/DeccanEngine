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

/////////////////////////////////////////////////
// Asset Manager
////////////////////////////////////////////////

int32_t Asset_GetSpriteIndex(const char *name);
SpriteAsset *Asset_NewSpriteAsset(const char *name);
SpriteAsset *Asset_LoadSprite(const char *name, const char *path);
SpriteAsset *Asset_LoadAnimatedSprite(const char *name, const char *path, ...);
SpriteAsset *Asset_GetSprite(const char *name);

int32_t Asset_GetFontIndex(const char *name);
FontAsset *Asset_NewFontAsset(const char *name);
FontAsset *Asset_LoadFont(const char *name, const char *path);
FontAsset *Asset_GetFont(const char *name);

/////////////////////////////////////////////////
// Camera
////////////////////////////////////////////////

void Camera_Move(Vector2f pos);
void Camera_CenterOn(GameObject *obj);
void Camera_SetPosition(Vector2f pos);
void Camera_SetBounds(PosRect rect);
Vector2f Camera_GetPosition();
PosRect  Camera_GetBounds();