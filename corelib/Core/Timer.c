/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Timer.h"

void DE_TimerStart(DeccanTimer *timer) {
    timer->startTicks = SDL_GetTicks();
    timer->pausedTicks = 0;
    timer->isRunning = true;
    timer->isPaused = false;
}

void DE_TimerStop(DeccanTimer *timer) {
    timer->startTicks = 0;
    timer->pausedTicks = 0;
    timer->isRunning = false;
    timer->isPaused = false;
}

void DE_TimerReset(DeccanTimer *timer) {
    DE_TimerStart(timer);
}

void DE_TimerPause(DeccanTimer *timer) {
    if(timer->isRunning && !timer->isPaused) {
        timer->isPaused = true;

        /* Calculate the paused ticks */
        timer->pausedTicks = SDL_GetTicks() - timer->startTicks;
        timer->startTicks = 0;
    }
}

DeccanTime DE_TimerGetTime(DeccanTimer *timer) {
    float timeMS = 0.0f;

    if(timer->isRunning) {
        if(timer->isPaused) {
            timeMS = timer->pausedTicks;
        }
        else {
            timeMS = SDL_GetTicks() - timer->startTicks;
        }
    }

    DeccanTime time;
    time.milliseconds = timeMS;
    time.seconds = timeMS / 1000.0f;

    return time;
}
