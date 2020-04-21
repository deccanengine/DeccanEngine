/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"

typedef struct Deccan_Timer Deccan_Timer;
typedef struct Deccan_Timer {
    float start_ticks, paused_ticks;
    bool is_running, is_paused;

    void (*start)(Deccan_Timer *timer);
    void (*stop) (Deccan_Timer *timer);
    void (*pause)(Deccan_Timer *timer);
    void (*reset)(Deccan_Timer *timer);
    float (*get_time)(Deccan_Timer *timer);
    float (*get_time_ms)(Deccan_Timer *timer);
} Deccan_Timer;

void _priv_Timer_start(Deccan_Timer *timer);
void _priv_Timer_stop (Deccan_Timer *timer);
void _priv_Timer_pause(Deccan_Timer *timer);
float _priv_Timer_get_time(Deccan_Timer *timer);
float _priv_Timer_get_time_ms(Deccan_Timer *timer);

static inline void _priv_Clock_delay(int32_t ms) { SDL_Delay(ms); }
Deccan_Timer _priv_Clock_new_timer();

#ifdef __STDC__

typedef struct _priv_Clock {
    void (*delay)(int32_t ms);
    Deccan_Timer (*new_timer)();
} _priv_Clock;

static _priv_Clock Deccan_Clock = {
    _priv_Clock_delay,
    _priv_Clock_new_timer
};

#elif __cplusplus

#endif