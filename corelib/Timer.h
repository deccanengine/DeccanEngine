#pragma once
#include "Config.h"

typedef struct Time {
    float seconds;
    float milliseconds;
} Time;

typedef struct Timer {
    float startTicks;
    float pausedTicks;
    bool isRunning;
    bool isPaused;
} Timer;

static inline void Clock_Delay(int32_t ms) { 
    SDL_Delay(ms); 
}

void Clock_StartTimer(Timer *timer);
void Clock_StopTimer (Timer *timer);
void Clock_PauseTimer(Timer *timer);
void Clock_ResetTimer(Timer *timer);
Time Clock_GetTime(Timer *timer);