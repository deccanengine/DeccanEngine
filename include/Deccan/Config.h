/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../../depends/stb_ds.h"

/* Define basic constants */
#ifndef PI 
    #define PI 3.14159265358979323846
#endif

#define DEG2RAD (PI/180.0000)
#define RAD2DEG (180.0000/PI)

/* Texture structure depends on backend */
#ifdef DECCAN_RENDERER_SDL
    typedef SDL_Texture RawTexture;
#endif

/* Memory management functions */
#ifndef DE_NEW
    #define DE_NEW(type,size) (type*)malloc(sizeof(type)*size);
#endif

static inline char *DE_newstring(const char *source) {
    char *string = DE_NEW(char, strlen(source));
    strcpy(string, source);
    return string;
}

/* Error handling/logging */
extern void DE_error (const char *str, ...);
extern void DE_report(const char *str, ...);

typedef struct Rect {
    float x;
    float y;
    float w;
    float h;
} Rect;

typedef struct PosRect {
    float x1;
    float y1;
    float x2;
    float y2;
} PosRect;

typedef struct Circle {
    float x;
    float y;
    float radius;
} Circle;

typedef struct Vector2i {
    int32_t x;
    int32_t y;
} Vector2i;

typedef struct Vector2u {
    uint32_t x;
    uint32_t y;
} Vector2u;

typedef struct Vector2f {
    float x;
    float y;
} Vector2f;

typedef struct Vector3i {
    int32_t x;
    int32_t y;
    int32_t z;
} Vector3i;

typedef struct MsgBuf {
    int count;
    int length;
    int num;
    char **messages;
} MsgBuf;

void Msg_Init(MsgBuf *buf, int count, int length);
void Msg_Send(MsgBuf *buf, const char *msg);
bool Msg_Receive(MsgBuf *buf, const char *msg);
void Msg_Free(MsgBuf *buf);

typedef struct Timer Timer;
typedef struct Timer {
    float startTicks;
    float pausedTicks;
    bool isRunning;
    bool isPaused;
} Timer;

typedef struct Time {
    float seconds;
    float milliseconds;
} Time;

static inline void Clock_Delay(int32_t ms) { 
    SDL_Delay(ms); 
}

void Clock_StartTimer(Timer *timer);
void Clock_StopTimer (Timer *timer);
void Clock_PauseTimer(Timer *timer);
void Clock_ResetTimer(Timer *timer);
Time Clock_GetTime(Timer *timer);