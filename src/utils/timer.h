/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"

typedef struct DE_Timer DE_Timer;
typedef struct DE_Timer {
    float start_ticks, paused_ticks;
    bool is_running, is_paused;

    void (*Start)(DE_Timer *timer);
    void (*Stop) (DE_Timer *timer);
    void (*Pause)(DE_Timer *timer);
    void (*Reset)(DE_Timer *timer);
    float (*GetTime)(DE_Timer *timer);
    float (*GetTimeMS)(DE_Timer *timer);
} DE_Timer;

void DE_Timer_start(DE_Timer *timer);
void DE_Timer_stop (DE_Timer *timer);
void DE_Timer_pause(DE_Timer *timer);
float DE_Timer_get_time(DE_Timer *timer);
float DE_Timer_get_time_ms(DE_Timer *timer);

static inline void DE_Clock_delay(int32_t ms) { SDL_Delay(ms); }
DE_Timer DE_Clock_new_timer();