/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"

typedef struct DeccanTime {
    float seconds;
    float milliseconds;
} DeccanTime;

typedef struct DeccanTimer {
    float startTicks;
    float pausedTicks;
    bool isRunning;
    bool isPaused;
} DeccanTimer;

static inline void DE_ClockDelay(int32_t ms) {
    SDL_Delay(ms);
}

void DE_TimerStart(DeccanTimer *timer);
void DE_TimerStop(DeccanTimer *timer);
void DE_TimerPause(DeccanTimer *timer);
void DE_TimerReset(DeccanTimer *timer);
DeccanTime DE_TimerGetTime(DeccanTimer *timer);
