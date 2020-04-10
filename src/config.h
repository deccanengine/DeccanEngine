#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../depends/stb_ds.h"

#define sdlerr SDL_GetError()
#define imgerr IMG_GetError()
#define ttferr TTF_GetError()

#define state_func_ptr(x) void(*x)(void)