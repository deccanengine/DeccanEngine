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

typedef SDL_Texture DE_Texture;

#define DE_new(type,size) (type*)malloc(sizeof(type)*size);
static inline char *DE_newstring(const char *source) {
    char *string = DE_new(char, strlen(source));
    strcpy(string, source);
    return string;
}

extern void DE_error (const char *str, ...);
extern void DE_report(const char *str, ...);