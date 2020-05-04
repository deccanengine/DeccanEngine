/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "core.h"

void DE_Asset_LoadTexture(const char *name, const char *path);
SDL_Texture *DE_Asset_GetTexture(const char *name);