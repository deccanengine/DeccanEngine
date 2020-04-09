#include "timer.h"

void deccan_new_timer(deccan_timer *timer) {
    timer->start_ticks = 0;
    timer->paused_ticks = 0;
    timer->is_running = false;
    timer->is_paused = false;
}

void deccan_start_timer(deccan_timer *timer) {
    timer->start_ticks = SDL_GetTicks();
    timer->paused_ticks = 0;
    timer->is_running = true;
    timer->is_paused = false;
}

void deccan_stop_timer(deccan_timer *timer) {
    deccan_new_timer(timer);
}

void deccan_pause_timer(deccan_timer *timer) {
    if(timer->is_running && timer->is_paused) {
        timer->is_paused = true;
        
        /* Calculate the paused ticks */
        timer->paused_ticks = SDL_GetTicks() - timer->start_ticks;
        timer->start_ticks = 0;
    }
}

float deccan_get_timer_time_ms(deccan_timer *timer) {
    float time = 0.0f;

    if(timer->is_running) {
        if(timer->is_paused) { time = timer->paused_ticks; }
        else { time = SDL_GetTicks() - timer->start_ticks; }
    }
    
    return time;
}

float deccan_get_timer_time(deccan_timer *timer) {
    return deccan_get_timer_time_ms(timer)/1000.0f;
}