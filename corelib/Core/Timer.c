/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Timer.h"

void Clock_StartTimer(Timer *timer) {
    timer->startTicks = SDL_GetTicks();
    timer->pausedTicks = 0;
    timer->isRunning = true;
    timer->isPaused = false;
}

void Clock_StopTimer(Timer *timer) {
    timer->startTicks = 0;
    timer->pausedTicks = 0;
    timer->isRunning = false;
    timer->isPaused = false;
}

void Clock_ResetTimer(Timer *timer) {
    Clock_StartTimer(timer);
}

void Clock_PauseTimer(Timer *timer) {
    if(timer->isRunning && !timer->isPaused) {
        timer->isPaused = true;

        /* Calculate the paused ticks */
        timer->pausedTicks = SDL_GetTicks() - timer->startTicks;
        timer->startTicks = 0;
    }
}

Time Clock_GetTime(Timer *timer) {
    float timeMS = 0.0f;

    if(timer->isRunning) {
        if(timer->isPaused) {
            timeMS = timer->pausedTicks;
        }
        else {
            timeMS = SDL_GetTicks() - timer->startTicks;
        }
    }

    Time time;
    time.milliseconds = timeMS;
    time.seconds = timeMS / 1000.0f;

    return time;
}
