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

/////////////////////////////////////////////////
/* Common macros */
/////////////////////////////////////////////////

#define DE_STRINGIFY(x) #x
#define DE_CONCAT(x,y) x##y
#define DE_UNUSED(x) (void)(x)

/////////////////////////////////////////////////
/* Detect C Version */
/////////////////////////////////////////////////
// See: https://sourceforge.net/p/predef/wiki/Standards/
#if __STDC_VERSION__ < 201112L
    #error Use a modern C compiler(C11 or greater)
#endif

/////////////////////////////////////////////////
/* Detect C Compiler */
/////////////////////////////////////////////////
// See: https://sourceforge.net/p/predef/wiki/Compilers/
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
// See: https://sourceforge.net/p/predef/wiki/OperatingSystems/
#if defined(__ANDROID__)
    /* Android must be checked first because
     * android defined both __ANDROID__ and __linux__
     */
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

/////////////////////////////////////////////////
/* Disable warnings */
/////////////////////////////////////////////////
// See: https://www.fluentcpp.com/2019/08/30/how-to-disable-a-warning-in-cpp/
#if defined(DE_COMPILER_MSVC)
    #define DE_DISABLE_WARNING        __pragma(warning(push))
    #define DE_ENABLE_WARNING         __pragma(warning(pop))
    #define DE_WARNING(warningNumber) __pragma(warning(disable: warningNumber))

    // TODO
    #define DE_DISABLE_WARNING_NO_UNUSED_VALUE
    #define DE_DISABLE_WARNING_NO_UNUSED_PARAM
    #define DE_DISABLE_WARNING_IMPLICIT_FALLTHROUGH

#elif defined(DE_COMPILER_GCC) || defined(DE_COMPILER_MINGW) || defined(DE_COMPILER_CLANG)
    #define DE_DISABLE_WARNING      _Pragma("GCC diagnostic push")
    #define DE_ENABLE_WARNING       _Pragma("GCC diagnostic pop")
    #define DE_WARNING(warningName) _Pragma("GCC diagnostic ignored \"warningName\"")

    #define DE_DISABLE_WARNING_NO_UNUSED_VALUE      DE_WARNING(-Wno-unused-value)
    #define DE_DISABLE_WARNING_NO_UNUSED_PARAM      DE_WARNING(-Wno-unused-parameter)
    #define DE_DISABLE_WARNING_IMPLICIT_FALLTHROUGH DE_WARNING(-Wno-implicit-fallthrough)

#else
    #define DE_DISABLE_WARNING
    #define DE_ENABLE_WARNING
    #define DE_WARNING

    #define DE_DISABLE_WARNING_NO_UNUSED_VALUE
    #define DE_DISABLE_WARNING_NO_UNUSED_PARAM
    #define DE_DISABLE_WARNING_IMPLICIT_FALLTHROUGH
 #endif

/////////////////////////////////////////////////
/* Define basic constants */
/////////////////////////////////////////////////

#define PI 3.14159265358979323846
#define DEG2RAD (PI/180.0000)
#define RAD2DEG (180.0000/PI)

/////////////////////////////////////////////////
/* External library includes */
/////////////////////////////////////////////////

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <depends/log.c/src/log.h>

#include <depends/cglm/include/cglm/cglm.h>

#include <depends/flecs/flecs.h>

#include <depends/stb/stb_image.h>
#include <depends/stb/stb_ds.h>

/////////////////////////////////////////////////
/* Error handling/logging */
/////////////////////////////////////////////////

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
