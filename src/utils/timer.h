#pragma once
#include "../config.h"

static inline void Deccan_delay(int32_t ms) { SDL_Delay(ms); }

typedef struct {
    float start_ticks, paused_ticks;
    bool is_running, is_paused;
} Deccan_Timer;

void Deccan_timer_start(Deccan_Timer *timer);
void Deccan_timer_stop(Deccan_Timer *timer);
void Deccan_timer_pause(Deccan_Timer *timer);
float Deccan_timer_get_time(Deccan_Timer *timer);
float Deccan_timer_get_time_ms(Deccan_Timer *timer);
