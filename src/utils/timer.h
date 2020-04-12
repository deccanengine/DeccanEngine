/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"

typedef struct {
    float start_ticks, paused_ticks;
    bool is_running, is_paused;
} Deccan_Timer;


static inline void _priv_delay(int32_t ms) { SDL_Delay(ms); }

void _priv_timer_start(Deccan_Timer *timer);
void _priv_timer_stop(Deccan_Timer *timer);
void _priv_timer_pause(Deccan_Timer *timer);
float _priv_timer_get_time(Deccan_Timer *timer);
float _priv_timer_get_time_ms(Deccan_Timer *timer);

typedef struct _priv_Clock {
    void (*delay)(int32_t ms);
    void (*timer_start)(Deccan_Timer *timer);
    void (*timer_stop)(Deccan_Timer *timer);
    void (*timer_pause)(Deccan_Timer *timer);
    float (*timer_get_time)(Deccan_Timer *timer);
    float (*timer_get_time_ms)(Deccan_Timer *timer);
} _priv_Clock;

static _priv_Clock Deccan_Clock = {
    _priv_delay,
    _priv_timer_start,
    _priv_timer_stop,
    _priv_timer_pause,
    _priv_timer_get_time,
    _priv_timer_get_time_ms
};