/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "Utils.h"

#define DE_INVALID_HANDLE (-1)

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef uint32_t deccan_handle_t;

typedef struct deccan_handle_pool_t {
    deccan_handle_t *dense;
    uint32_t *sparse;
    int length;
    int capacity;
} deccan_handle_pool_t;

////////////////////////////////////////////////////////////////////////////////
// Handle Pool
////////////////////////////////////////////////////////////////////////////////

deccan_handle_pool_t *deccan_handle_pool_create(int capacity);
void deccan_handle_pool_destroy(deccan_handle_pool_t *pool);

////////////////////////////////////////////////////////////////////////////////
// Handle
////////////////////////////////////////////////////////////////////////////////

deccan_handle_t deccan_handle_new(deccan_handle_pool_t *pool);
void deccan_handle_delete(deccan_handle_pool_t *pool, deccan_handle_t handle);
uint32_t deccan_handle_index(deccan_handle_pool_t *pool, deccan_handle_t handle);
bool deccan_handle_valid(deccan_handle_pool_t *pool, deccan_handle_t handle);
