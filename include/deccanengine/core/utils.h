/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"

DE_API void *deccan_alloc(size_t size, int count);
DE_API void *deccan_realloc(void *mem, size_t size);
DE_API void deccan_free(void *mem);
DE_API zpl_allocator deccan_zpl_allocator(void);
