/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"

DE_API void *DE_Alloc(size_t size, int count);
DE_API void *DE_Realloc(void *mem, size_t size);
DE_API void DE_Free(void *mem);
