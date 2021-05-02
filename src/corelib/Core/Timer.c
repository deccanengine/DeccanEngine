/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Timer.h"

DE_IMPL void deccan_timer_start(deccan_timer_t *timer) {
    timer->startTicks = SDL_GetTicks();
    timer->pausedTicks = 0;
    timer->isRunning = true;
    timer->isPaused = false;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_timer_stop(deccan_timer_t *timer) {
    timer->startTicks = 0;
    timer->pausedTicks = 0;
    timer->isRunning = false;
    timer->isPaused = false;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_timer_reset(deccan_timer_t *timer) {
    deccan_timer_start(timer);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_timer_pause(deccan_timer_t *timer) {
    if (timer->isRunning && !timer->isPaused) {
        timer->isPaused = true;

        /* Calculate the paused ticks */
        timer->pausedTicks = SDL_GetTicks() - timer->startTicks;
        timer->startTicks = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_time_t deccan_timer_get_time(deccan_timer_t *timer) {
    float timeMS = 0.0f;

    if (timer->isRunning) {
        if (timer->isPaused) {
            timeMS = timer->pausedTicks;
        }
        else {
            timeMS = SDL_GetTicks() - timer->startTicks;
        }
    }

    deccan_time_t time;
    time.milliseconds = timeMS;
    time.seconds = timeMS / 1000.0f;

    return time;
}
