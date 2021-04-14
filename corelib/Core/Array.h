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

typedef struct DeccanArray {
    void **data;
    uint32_t length;
    uint32_t capacity;
} DeccanArray;

/////////////////////////////////////////////////
// Constructor/Destructor
////////////////////////////////////////////////

DE_API void DE_ArrayCreate(DeccanArray *array);
DE_API void DE_ArrayDestroy(DeccanArray *array);

/////////////////////////////////////////////////
// Insertion
////////////////////////////////////////////////

DE_API void DE_ArrayAddItem(DeccanArray *array, void *item);
DE_API void DE_ArraySetItem(DeccanArray *array, uint32_t index, void *item);
DE_API void DE_ArrayInsertItem(DeccanArray *array, uint32_t index, void *item);

/////////////////////////////////////////////////
// Access
////////////////////////////////////////////////

DE_API void *DE_ArrayGetItem(DeccanArray *array, uint32_t index);
DE_API void *DE_ArrayGetLastItem(DeccanArray *array);

/////////////////////////////////////////////////
// Deletion
////////////////////////////////////////////////

DE_API void DE_ArrayRemoveItem(DeccanArray *array, int32_t index);
DE_API void DE_ArrayRemoveLastItem(DeccanArray *array);
