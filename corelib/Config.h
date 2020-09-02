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
#include <SDL2/SDL_ttf.h>

#include "../depends/cglm/include/cglm/cglm.h"

#include "../depends/stb/stb_image.h"
#include "../depends/stb/stb_ds.h"

/////////////////////////////////////////////////
/* Detect C Version */
/////////////////////////////////////////////////
#if __STDC_VERSION__ < 201112L
    #error Use a modern C compiler(C11 or greater)
#endif

/////////////////////////////////////////////////
/* Detect C Compiler */
/////////////////////////////////////////////////
#if defined(__clang__)
    #define DE_COMPILER_CLANG
#elif defined(_MSC_VER_)
    #define DE_COMPILER_MSVC
#elif defined(__GNUC__)
    #define DE_COMPILER_GCC
#elif defined(__MINGW32__)
    #define DE_COMPILER_MINGW
#else
    // TODO: Pelles C and others?
    #error This C compiler is not supported
#endif

/////////////////////////////////////////////////
/* Detect OS-family */
/////////////////////////////////////////////////
#if defined(unix) || defined(__unix__) || defined(__unix)
    #define DE_PLATFORM_UNIX
#endif

/////////////////////////////////////////////////
/* Detect OS */
/////////////////////////////////////////////////
#if defined(__ANDROID__)
    #define DE_OS_ANDROID
#elif defined(__linux__)
    #define DE_OS_LINUX
#elif defined(__FreeBSD__) && defined(__NetBSD__) && \
    defined(__OpenBSD__) && defined(__DragonFly__)
    #define DE_OS_BSD
#elif defined(__APPLE__) && defined(__MACH__)
    #include <TargetConditionals.h>
    #if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
        #define DE_OS_IOS
    #elif TARGET_OS_MAC
        #define DE_OS_MAC
    #else
        #error "This Apple operating system is not supported"
    #endif
#elif defined(_WIN32)
    #if defined(DE_COMPILER_MSVC) && defined(_WINRT_DLL)
        #define DE_OS_UWP
    #else
        #define DE_OS_WIN
    #endif
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
#elif defined(__EMSCRIPTEN__)
    #define DE_OS_WEB
#else
    #error This Operating System is not supported
#endif


/////////////////////////////////////////////////
/* Define basic constants */
/////////////////////////////////////////////////

#define PI 3.14159265358979323846
#define DEG2RAD (PI/180.0000)
#define RAD2DEG (180.0000/PI)

#define DE_UNUSED(x) (void)(x)

/* Texture structure depends on backend */
#ifdef DECCAN_RENDERER_SDL
    typedef SDL_Texture RawTexture;
#endif

/* Error handling/logging */
extern void DE_ERROR (const char *str, ...);
extern void DE_REPORT(const char *str, ...);
