#include "timer.h"

void _priv_timer_start(Deccan_Timer *timer) {
    timer->start_ticks = SDL_GetTicks();
    timer->paused_ticks = 0;
    timer->is_running = true;
    timer->is_paused = false;
}

void _priv_timer_stop(Deccan_Timer *timer) {
    timer->start_ticks = 0;
    timer->paused_ticks = 0;
    timer->is_running = false;
    timer->is_paused = false;
}

void _priv_timer_pause(Deccan_Timer *timer) {
    if(timer->is_running && timer->is_paused) {
        timer->is_paused = true;
        
        /* Calculate the paused ticks */
        timer->paused_ticks = SDL_GetTicks() - timer->start_ticks;
        timer->start_ticks = 0;
    }
}

float _priv_timer_get_time_ms(Deccan_Timer *timer) {
    float time = 0.0f;

    if(timer->is_running) {
        if(timer->is_paused) { time = timer->paused_ticks; }
        else { time = SDL_GetTicks() - timer->start_ticks; }
    }
    
    return time;
}

float _priv_timer_get_time(Deccan_Timer *timer) {
    return _priv_timer_get_time_ms(timer)/1000.0f;
}