/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_TGA
#define STBI_NO_GIF
#define STBI_NO_HDR
#define STBI_NO_PIC
#define STBI_NO_PNM

#define STB_DS_IMPLEMENTATION

#define SOKOL_IMPL
#define SOKOL_GLCORE33

#include "../Config.h"

#include <depends/flecs/flecs.c>
#include <depends/log.c/src/log.c>

#include <depends/glad/src/glad.c>

#include <depends/sx/src/handle.c>
#include <depends/sx/src/sx.c>
#include <depends/sx/src/allocator.c>
#include <depends/sx/src/threads.c>
#include <depends/sx/src/string.c>
#include <depends/sx/src/os.c>
