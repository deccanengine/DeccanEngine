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

    #define set_global_engine deccan_set_global_engine
    #define get_global_engine deccan_get_global_engine
    #define init deccan_init
    #define quit deccan_quit
    #define run deccan_run
    #define new_scene deccan_new_scene
    #define add_scene deccan_add_scene
    #define remove_scene deccan_remove_scene
    #define current_scene deccan_current_scene
    #define pause_scene deccan_pause_scene
    #define is_scene_paused deccan_is_scene_paused
    #define input_get_key deccan_input_get_key
    #define input_get_mouse_button deccan_input_get_mouse_button
    #define input_get_mouse_pos deccan_input_get_mouse_pos
    #define renderer_clear deccan_renderer_clear
    #define renderer_set_color deccan_renderer_set_color
    #define asset_load_texture deccan_asset_load_texture
    #define asset_get_texture deccan_asset_get_texture
    #define timer_start deccan_timer_start
    #define timer_stop deccan_timer_stop
    #define timer_pause deccan_timer_pause
    #define timer_get_time deccan_timer_get_time
    #define timer_get_time_ms deccan_timer_get_time_ms
#endif