/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

/* clang-format off */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////////
/* Common macros */
/////////////////////////////////////////////////////////////////////////////////

#define DE_STRINGIFY(x) #x
#define DE_CONCAT(x,y) x##y
#define DE_UNUSED(x) (void)(x)

/////////////////////////////////////////////////////////////////////////////////
/* Detect C Compiler */
/////////////////////////////////////////////////////////////////////////////////
// See: https://sourceforge.net/p/predef/wiki/Compilers/
#if defined(__clang__)
    #define DE_COMPILER_CLANG
#elif defined(_MSC_VER)
    #define DE_COMPILER_MSVC
#elif defined(__GNUC__)
    #define DE_COMPILER_GCC
#elif defined(__MINGW32__)
    #define DE_COMPILER_MINGW
#else
    /* No other compilers are planned! */
    #error This C compiler is not supported
#endif

/////////////////////////////////////////////////////////////////////////////////
/* Detect C Version */
/////////////////////////////////////////////////////////////////////////////////
// See: https://sourceforge.net/p/predef/wiki/Standards/
#ifndef DE_COMPILER_MSVC
    // MSVC doesn't defines it?
    #if __STDC_VERSION__ < 201112L
        #error Use a modern C compiler(C11 or greater)
    #endif
#endif

/////////////////////////////////////////////////////////////////////////////////
/* Detect OS-family */
/////////////////////////////////////////////////////////////////////////////////
#if defined(unix) || defined(__unix__) || defined(__unix)
    #define DE_PLATFORM_UNIX
#endif

/////////////////////////////////////////////////////////////////////////////////
/* Detect OS */
/////////////////////////////////////////////////////////////////////////////////
// See: https://sourceforge.net/p/predef/wiki/OperatingSystems/
#if defined(__ANDROID__)
    /* Android must be checked first because
     * android defines both __ANDROID__ and __linux__ */
    #define DE_OS_ANDROID

#elif defined(__linux__)
    #define DE_OS_LINUX

#elif defined(__FreeBSD__) && defined(__NetBSD__) && \
    defined(__OpenBSD__) && defined(__DragonFly__)
    #define DE_OS_BSD

#elif defined(__APPLE__) && defined(__MACH__)
    /* Defines all Apple platform */
    #include <TargetConditionals.h>

    #if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
        #define DE_OS_IOS
    #elif TARGET_OS_MAC
        #define DE_OS_MAC
    #else
        #error "This Apple operating system is not supported"
    #endif

#elif defined(_WIN32)
    // See: https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros
    #if defined(DE_COMPILER_MSVC) && defined(_WINRT_DLL)
        /* UWP would only work with MSVC */
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

/////////////////////////////////////////////////////////////////////////////////
/* Define basic constants */
/////////////////////////////////////////////////////////////////////////////////

#define DE_PI 3.14159265358979323846
#define DE_DEG2RAD (PI/180.0000)
#define DE_RAD2DEG (180.0000/PI)

/////////////////////////////////////////////////////////////////////////////////
/* External library includes */
/////////////////////////////////////////////////////////////////////////////////

#include <SDL.h>
#include <SDL_ttf.h>

#define ZPL_NANO
#define ZPL_ENABLE_HASHING
#include <zpl.h>

#include <log.h>

#include <cglm/cglm.h>
#include <cglm/struct.h>

#include <flecs.h>

#include <stb/stb_image.h>

#include <glad/glad.h>

#include <sokol/sokol_gfx.h>

/////////////////////////////////////////////////////////////////////////////////
/* Library API */
/////////////////////////////////////////////////////////////////////////////////

/* Always shared library */
#define DE_SHARED_LIB

#ifdef DE_SHARED_LIB
    #ifdef DE_COMPILER_MSVC 
        #ifdef DE_LIBRARY_EXPORT
            #define DE_API __declspec(dllexport)
        #else
            #define DE_API __declspec(dllimport)
        #endif
    #else
        #define DE_API extern
    #endif
#else
    /* Just reserved for future */
    #error "Building as static library is unsupported."
#endif

#define DE_IMPL /* Unused! */
#define DE_PRIV static

/////////////////////////////////////////////////////////////////////////////////
/* Error handling/logging */
/////////////////////////////////////////////////////////////////////////////////

#if defined(DE_DEBUG)
    #define DE_FATAL(...) (log_fatal(__VA_ARGS__), exit(-1))
    #define DE_ERROR(...) (log_error(__VA_ARGS__))
    #define DE_WARN(...)  (log_warn (__VA_ARGS__))
    #define DE_INFO(...)  (log_info (__VA_ARGS__))
#else
    #define DE_FATAL(...) (exit(-1))
    #define DE_ERROR(...)
    #define DE_WARN(...)
    #define DE_INFO(...)
#endif

/* clang-format on */
