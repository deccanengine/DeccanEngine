#include "Handle.h"

/////////////////////////////////////////////////
// Handle Pool
////////////////////////////////////////////////

DeccanHandlePool *DE_HandlePoolCreate(int capacity) {
    if (capacity <= 0) 
        return NULL;

    DeccanHandlePool *pool = DE_Alloc(sizeof(DeccanHandlePool), 1);
    pool->dense  = DE_Alloc(sizeof(DeccanHandle), capacity);
    pool->sparse = DE_Alloc(sizeof(uint32_t), capacity);
    pool->length = 0;
    pool->capacity = capacity;
    for (int i = 0; i < pool->capacity; i += 1) {
        pool->dense[i] = i;
    }

    return pool;
}

void DE_HandlePoolDestroy(DeccanHandlePool *pool) {
    DE_Free(pool->sparse);
    DE_Free(pool->dense);
    DE_Free(pool);
}

/////////////////////////////////////////////////
// Handle
////////////////////////////////////////////////

DeccanHandle DE_HandleNew(DeccanHandlePool *pool) {
    if (pool->length < pool->capacity) {
        int index = pool->length;
        pool->length += 1;

        DeccanHandle handle = pool->dense[index];
        pool->sparse[handle] = index;
        return handle;
    }
    else {
        pool->capacity *= 2;
        pool->dense = DE_Realloc(pool->dense, pool->capacity);
        pool->sparse = DE_Realloc(pool->sparse, pool->capacity);
        return DE_HandleNew(pool);
    }

    return -1;
}

void DE_HandleDelete(DeccanHandlePool *pool, DeccanHandle handle) {
    uint32_t index = pool->sparse[handle];
    pool->length -= 1;

    DeccanHandle last_handle = pool->dense[pool->length];

    pool->dense[pool->length] = handle;
    pool->sparse[last_handle] = index;
    pool->dense[index] = last_handle;
}

uint32_t DE_HandleIndex(DeccanHandlePool *pool, DeccanHandle handle) {
    return (handle == DE_INVALID_HANDLE) ? DE_INVALID_HANDLE : pool->sparse[handle];
}

bool DE_HandleValid(DeccanHandlePool *pool, DeccanHandle handle) {
    uint32_t index = pool->sparse[handle];
    return index < pool->length && pool->dense[index] == handle; 
}
