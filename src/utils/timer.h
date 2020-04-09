#pragma once
#include "../config.h"

static inline void deccan_delay(int32_t ms) { SDL_Delay(ms); }

typedef struct {
    float start_ticks, paused_ticks;
    bool is_running, is_paused;
} deccan_timer;

void deccan_new_timer(deccan_timer *timer);
void deccan_start_timer(deccan_timer *timer);
void deccan_stop_timer(deccan_timer *timer);
void deccan_pause_timer(deccan_timer *timer);
float deccan_get_timer_time(deccan_timer *timer);
float deccan_get_timer_time_ms(deccan_timer *timer);
