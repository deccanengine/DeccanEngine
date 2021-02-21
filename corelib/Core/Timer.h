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

DE_API void DE_TimerStart(DeccanTimer *timer);
DE_API void DE_TimerStop(DeccanTimer *timer);
DE_API void DE_TimerPause(DeccanTimer *timer);
DE_API void DE_TimerReset(DeccanTimer *timer);
DE_API DeccanTime DE_TimerGetTime(DeccanTimer *timer);
