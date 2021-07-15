/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once

#include "../config.h"
#include "utils.h"
#include "string.h"
#include "timer.h"

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct deccan_core_desc_t {
    char *title;
    vec2s resolution;
    bool fullscreen;
    bool vsync;
    bool resizable;
    bool close_on_escape; // TODO: Need set-get but a bit differently
    float fps;
} deccan_core_desc_t;

////////////////////////////////////////////////////////////////////////////////
// Core functions
////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_core_set_title(const char *name);
DE_API void deccan_core_set_resolution(vec2s mode);
DE_API void deccan_core_toogle_fullscreen(void);
DE_API void deccan_core_toogle_vsync(bool vsync);
DE_API void deccan_core_set_framerate_limit(float fps);
DE_API const char *deccan_core_get_title(void);
DE_API vec2s deccan_core_get_resolution(void);
DE_API bool deccan_core_is_fullscreened(void);
DE_API bool deccan_core_is_vsync_enabled(void);
DE_API bool deccan_core_is_resizable(void);
DE_API bool deccan_core_is_running(void);
DE_API float deccan_core_get_framerate_limit(void);
DE_API float deccan_core_get_average_framerate(void);
DE_API float deccan_core_get_delta_time(void);
DE_API uint32_t deccan_core_process_start_time(void);
