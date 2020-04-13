/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "config.h"

#include "core/core.h"
#include "core/input.h"
#include "core/asset.h"

#include "renderer/renderer.h"

#include "utils/log.h"
#include "utils/timer.h"
#include "utils/vector.h"

#ifdef using_namespace_Deccan
    #define DECCAN_SHORT_NAMES
#endif

#ifdef DECCAN_SHORT_NAMES 
    #define Info Deccan_Info
    #define Scene Deccan_Scene
    #define KeyState Deccan_KeyState
    #define MouseState Deccan_MouseState
    #define MousePos Deccan_MousePos
    #define Color Deccan_Color
    #define Timer Deccan_Timer 
    #define Vector2i Deccan_Vector2i
    #define Vector2u Deccan_Vector2u
    #define Vector2f Deccan_Vector2f

    #define Core Deccan_Core
    #define Scenes Deccan_Scenes
    #define Renderer Deccan_Renderer
    #define ColorList Deccan_ColorList
    #define Key Deccan_Key
    #define Button Deccan_Button
    #define Input Deccan_Input
    #define Asset Deccan_Asset
#endif