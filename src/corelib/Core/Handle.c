#include "Handle.h"

/////////////////////////////////////////////////////////////////////////////////
// Handle Pool
////////////////////////////////////////////////////////////////////////////////

deccan_handle_pool_t *deccan_handle_pool_create(int capacity) {
    if (capacity <= 0) 
        return NULL;

    deccan_handle_pool_t *pool = deccan_alloc(sizeof(deccan_handle_pool_t), 1);
    pool->dense  = deccan_alloc(sizeof(deccan_handle_t), capacity);
    pool->sparse = deccan_alloc(sizeof(uint32_t), capacity);
    pool->length = 0;
    pool->capacity = capacity;
    for (int i = 0; i < pool->capacity; i += 1) {
        pool->dense[i] = i;
    }

    return pool;
}

////////////////////////////////////////////////////////////////////////////////

void deccan_handle_pool_destroy(deccan_handle_pool_t *pool) {
    deccan_free(pool->sparse);
    deccan_free(pool->dense);
    deccan_free(pool);
}

/////////////////////////////////////////////////////////////////////////////////
// Handle
////////////////////////////////////////////////////////////////////////////////

deccan_handle_t deccan_handle_new(deccan_handle_pool_t *pool) {
    if (pool->length < pool->capacity) {
        int index = pool->length;
        pool->length += 1;

        deccan_handle_t handle = pool->dense[index];
        pool->sparse[handle] = index;
        return handle;
    }
    else {
        pool->capacity *= 2;
        pool->dense = deccan_realloc(pool->dense, pool->capacity);
        pool->sparse = deccan_realloc(pool->sparse, pool->capacity);
        return deccan_handle_new(pool);
    }

    return -1;
}

////////////////////////////////////////////////////////////////////////////////

void deccan_handle_delete(deccan_handle_pool_t *pool, deccan_handle_t handle) {
    uint32_t index = pool->sparse[handle];
    pool->length -= 1;

    deccan_handle_t last_handle = pool->dense[pool->length];

    pool->dense[pool->length] = handle;
    pool->sparse[last_handle] = index;
    pool->dense[index] = last_handle;
}

////////////////////////////////////////////////////////////////////////////////

uint32_t deccan_handle_index(deccan_handle_pool_t *pool, deccan_handle_t handle) {
    return (handle == DE_INVALID_HANDLE) ? DE_INVALID_HANDLE : pool->sparse[handle];
}

////////////////////////////////////////////////////////////////////////////////

bool deccan_handle_valid(deccan_handle_pool_t *pool, deccan_handle_t handle) {
    uint32_t index = pool->sparse[handle];
    return index < pool->length && pool->dense[index] == handle; 
}
