/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"

typedef struct deccan_time_t {
    float seconds;
    float milliseconds;
} deccan_time_t;

typedef struct deccan_timer_t {
    float start_ticks;
    float paused_ticks;
    bool is_running;
    bool is_paused;
} deccan_timer_t;

static inline void deccan_clock_delay(int32_t ms) {
    SDL_Delay(ms);
}

DE_API void deccan_timer_start(deccan_timer_t *timer);
DE_API void deccan_timer_stop(deccan_timer_t *timer);
DE_API void deccan_timer_pause(deccan_timer_t *timer);
DE_API void deccan_timer_reset(deccan_timer_t *timer);
DE_API deccan_time_t deccan_timer_get_time(deccan_timer_t *timer);
