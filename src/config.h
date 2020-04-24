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

#include "../depends/stb_ds.h"

typedef SDL_Texture Deccan_Texture;

#define DE_new(type,size) (type*)malloc(sizeof(type)*size);
static inline char *DE_newstring(const char *source) {
    char *string = DE_new(char, strlen(source));
    strcpy(string, source);
    return string;
}

static void DE_error(const char *str, ...) {
    printf("Fatal Error: ");
    
    va_list args;
    va_start(args, str);
    vprintf(str, args);
    va_end(args);
    
    printf("\n");
    exit(-1);
}

#define DECCAN_REPORTS_ENABLED

#ifdef DECCAN_REPORTS_ENABLED
extern FILE *DE_logfile;
#endif

static void DE_report(const char *str, ...) {
#ifdef DECCAN_REPORTS_ENABLED
    va_list args;
    
    va_start(args, str);
    vfprintf(DE_logfile, str, args);
    va_end(args);
    
    fprintf(DE_logfile, "\n");
#endif
}