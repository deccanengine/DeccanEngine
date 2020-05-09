/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Config.h>

void _timer_start(Timer *timer) {
    timer->start_ticks = SDL_GetTicks();
    timer->paused_ticks = 0;
    timer->is_running = true;
    timer->is_paused = false;
}

void _timer_stop(Timer *timer) {
    timer->start_ticks = 0;
    timer->paused_ticks = 0;
    timer->is_running = false;
    timer->is_paused = false;
}

void _timer_pause(Timer *timer) {
    if(timer->is_running && timer->is_paused) {
        timer->is_paused = true;
        
        /* Calculate the paused ticks */
        timer->paused_ticks = SDL_GetTicks() - timer->start_ticks;
        timer->start_ticks = 0;
    }
}

float _timer_get_time_ms(Timer *timer) {
    float time = 0.0f;

    if(timer->is_running) {
        if(timer->is_paused) { time = timer->paused_ticks; }
        else { time = SDL_GetTicks() - timer->start_ticks; }
    }
    
    return time;
}

float _timer_get_time(Timer *timer) {
    return _timer_get_time_ms(timer)/1000.0f;
}

Timer Clock_NewTimer() {
    Timer timer;
    timer.Start = _timer_start;
    timer.Stop  = _timer_stop;
    timer.Pause = _timer_pause;
    timer.Reset = _timer_start; /* reset and start are same */
    timer.GetTime = _timer_get_time;
    timer.GetTimeMS = _timer_get_time_ms;
    return timer;
}