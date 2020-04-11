#pragma once

#define DECCAN_DEBUG

#include "src/config.h"

#include "src/core.h"
#include "src/renderer.h"
#include "src/input.h"
#include "src/asset.h"

#include "src/utils/log.h"
#include "src/utils/timer.h"

#ifdef using_namespace_deccan
    #define DECCAN_SHORT_NAMES
#endif

#ifdef DECCAN_SHORT_NAMES 
    #define Info deccan_Info
    #define Scene deccan_Scene
    #define KeyState deccan_KeyState
    #define MouseState deccan_MouseState
    #define MousePos deccan_MousePos
    #define Color deccan_Color
    #define Timer deccan_Timer 

    #define key deccan_key
    #define button deccan_button

    #define Core deccan_Core
    #define Scenes deccan_Scenes
    #define Renderer deccan_Renderer
    #define Input deccan_Input
    #define Asset deccan_Asset
#endif