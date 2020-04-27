/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "timer.h"

void DE_Timer_start(DE_Timer *timer) {
    timer->start_ticks = SDL_GetTicks();
    timer->paused_ticks = 0;
    timer->is_running = true;
    timer->is_paused = false;
}

void DE_Timer_stop(DE_Timer *timer) {
    timer->start_ticks = 0;
    timer->paused_ticks = 0;
    timer->is_running = false;
    timer->is_paused = false;
}

void DE_Timer_pause(DE_Timer *timer) {
    if(timer->is_running && timer->is_paused) {
        timer->is_paused = true;
        
        /* Calculate the paused ticks */
        timer->paused_ticks = SDL_GetTicks() - timer->start_ticks;
        timer->start_ticks = 0;
    }
}

float DE_Timer_get_time_ms(DE_Timer *timer) {
    float time = 0.0f;

    if(timer->is_running) {
        if(timer->is_paused) { time = timer->paused_ticks; }
        else { time = SDL_GetTicks() - timer->start_ticks; }
    }
    
    return time;
}

float DE_Timer_get_time(DE_Timer *timer) {
    return DE_Timer_get_time_ms(timer)/1000.0f;
}

DE_Timer DE_Clock_new_timer() {
    DE_Timer timer;
    timer.Start = DE_Timer_start;
    timer.Stop  = DE_Timer_stop;
    timer.Pause = DE_Timer_pause;
    timer.Reset = DE_Timer_start; /* reset and start are same */
    timer.GetTime = DE_Timer_get_time;
    timer.GetTimeMS = DE_Timer_get_time_ms;
    return timer;
}