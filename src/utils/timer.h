#pragma once
#include "../config.h"

static inline void deccan_delay(int32_t ms) { SDL_Delay(ms); }

typedef struct {
    float start_ticks, paused_ticks;
    bool is_running, is_paused;
} deccan_Timer;

void deccan_timer_start(deccan_Timer *timer);
void deccan_timer_stop(deccan_Timer *timer);
void deccan_timer_pause(deccan_Timer *timer);
float deccan_timer_get_time(deccan_Timer *timer);
float deccan_timer_get_time_ms(deccan_Timer *timer);
