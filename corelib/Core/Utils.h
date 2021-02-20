/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"

void *DE_Alloc(size_t size, int count);
void *DE_Realloc(void *mem, size_t size);
void DE_Free(void *mem);
