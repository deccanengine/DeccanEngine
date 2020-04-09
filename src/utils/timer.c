#include "timer.h"

void deccan_timer_init(deccan_Timer *timer) {
    timer->start_ticks = 0;
    timer->paused_ticks = 0;
    timer->is_running = false;
    timer->is_paused = false;
}

void deccan_timer_start(deccan_Timer *timer) {
    timer->start_ticks = SDL_GetTicks();
    timer->paused_ticks = 0;
    timer->is_running = true;
    timer->is_paused = false;
}

void deccan_timer_stop(deccan_Timer *timer) {
    deccan_timer_init(timer);
}

void deccan_timer_pause(deccan_Timer *timer) {
    if(timer->is_running && timer->is_paused) {
        timer->is_paused = true;
        
        /* Calculate the paused ticks */
        timer->paused_ticks = SDL_GetTicks() - timer->start_ticks;
        timer->start_ticks = 0;
    }
}

float deccan_timer_get_time_ms(deccan_Timer *timer) {
    float time = 0.0f;

    if(timer->is_running) {
        if(timer->is_paused) { time = timer->paused_ticks; }
        else { time = SDL_GetTicks() - timer->start_ticks; }
    }
    
    return time;
}

float deccan_timer_get_time(deccan_Timer *timer) {
    return deccan_timer_get_time_ms(timer)/1000.0f;
}