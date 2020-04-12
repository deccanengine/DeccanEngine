#pragma once

#define DECCAN_DEBUG

#include "src/config.h"

#include "src/core.h"
#include "src/renderer.h"
#include "src/input.h"
#include "src/asset.h"

#include "src/utils/log.h"
#include "src/utils/timer.h"

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

    #define key Deccan_Key
    #define button Deccan_Button

    #define Core Deccan_Core
    #define Scenes Deccan_Scenes
    #define Renderer Deccan_Renderer
    #define Input Deccan_Input
    #define Asset Deccan_Asset
#endif