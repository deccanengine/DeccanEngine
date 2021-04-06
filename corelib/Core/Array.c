/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Array.h"

/////////////////////////////////////////////////
// Constructor/Destructor
////////////////////////////////////////////////

DE_IMPL void DE_ArrayCreate(DeccanArray *array) {
    array->length = 0;
    array->capacity = 5;
    array->data = malloc(sizeof(void *) * array->capacity);
}

DE_IMPL void DE_ArrayDestroy(DeccanArray *array) {
    free(array->data);
}

/////////////////////////////////////////////////
// Insertion
////////////////////////////////////////////////

DE_IMPL void CheckGrowArray(DeccanArray *array) {
    if (array->length <= array->capacity) {
        array->capacity += 5;
        array->data = realloc(array->data, sizeof(void *) * array->capacity);
    }
}

DE_IMPL void DE_ArrayAddItem(DeccanArray *array, void *item) {
    CheckGrowArray(array);
    array->data[array->length++] = item;
}

DE_IMPL bool IndexBound(DeccanArray *array, uint32_t index) {
    if (index > array->length || index < 0) {
        printf("Index out of bounds\n");
        return false;
    }
    return true;
}

DE_IMPL void DE_ArraySetItem(DeccanArray *array, uint32_t index, void *item) {
    if (!IndexBound(array, index))
        return;
    array->data[index] = item;
}

DE_IMPL void DE_ArrayInsertItem(DeccanArray *array, uint32_t index, void *item) {
    if (!IndexBound(array, index))
        return;
    CheckGrowArray(array);
    array->length++;

    memmove(&array->data[index + 1], &array->data[index], sizeof(void *) * ((array->length - 1) - index));
    array->data[index] = item;
}

/////////////////////////////////////////////////
// Access
////////////////////////////////////////////////

DE_IMPL void *DE_ArrayGetItem(DeccanArray *array, uint32_t index) {
    if (!IndexBound(array, index))
        return NULL;
    return array->data[index];
}

DE_IMPL void *DE_ArrayGetLastItem(DeccanArray *array) {
    return array->data[array->length - 1];
}

/////////////////////////////////////////////////
// Deletion
////////////////////////////////////////////////

DE_IMPL void DE_ArrayRemoveItem(DeccanArray *array, int32_t index) {
    if (!IndexBound(array, index))
        return;
    memmove(&array->data[index], &array->data[index + 1], sizeof(void *) * ((array->length - 1) - index));
    array->length--;
}

DE_IMPL void DE_ArrayRemoveLastItem(DeccanArray *array) {
    /* Yes, that's it! */
    array->length--;
}
