/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Timer.h"

DE_IMPL void deccan_timer_start(deccan_timer_t *timer) {
    timer->start_ticks = SDL_GetTicks();
    timer->paused_ticks = 0;
    timer->is_running = true;
    timer->is_paused = false;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_timer_stop(deccan_timer_t *timer) {
    timer->start_ticks = 0;
    timer->paused_ticks = 0;
    timer->is_running = false;
    timer->is_paused = false;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_timer_reset(deccan_timer_t *timer) {
    deccan_timer_start(timer);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_timer_pause(deccan_timer_t *timer) {
    if (timer->is_running && !timer->is_paused) {
        timer->is_paused = true;

        /* Calculate the paused ticks */
        timer->paused_ticks = SDL_GetTicks() - timer->start_ticks;
        timer->start_ticks = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_time_t deccan_timer_get_time(deccan_timer_t *timer) {
    float time_ms = 0.0f;

    if (timer->is_running) {
        if (timer->is_paused) {
            time_ms = timer->paused_ticks;
        }
        else {
            time_ms = SDL_GetTicks() - timer->start_ticks;
        }
    }

    deccan_time_t time;
    time.milliseconds = time_ms;
    time.seconds = time_ms / 1000.0f;

    return time;
}
