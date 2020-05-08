/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include <Deccan/Config.h>
#include <Deccan/Core.h>

void DE_Asset_LoadTexture(const char *name, const char *path);
SDL_Texture *DE_Asset_GetTexture(const char *name);

void DE_Asset_LoadFont(const char *name, const char *path);
TTF_Font *DE_Asset_GetFont(const char *name);