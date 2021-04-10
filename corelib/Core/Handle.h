/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "Utils.h"

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef uint32_t DeccanHandle;

typedef struct DeccanHandlePool {
    DeccanHandle *dense;
    uint32_t *sparse;
    int length;
    int capacity;
} DeccanHandlePool;

/////////////////////////////////////////////////
// Handle Pool
////////////////////////////////////////////////

DeccanHandlePool *DE_HandlePoolCreate(int capacity);
void DE_HandlePoolDestroy(DeccanHandlePool *pool);

/////////////////////////////////////////////////
// Handle
////////////////////////////////////////////////

DeccanHandle DE_HandleNew(DeccanHandlePool *pool);
void DE_HandleDelete(DeccanHandlePool *pool, DeccanHandle handle);
uint32_t DE_HandleIndex(DeccanHandlePool *pool, DeccanHandle handle);
bool DE_HandleValid(DeccanHandlePool *pool, DeccanHandle handle);
