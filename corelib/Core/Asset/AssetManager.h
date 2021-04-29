/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../Config.h"
#include "../Handle.h"
#include "../String.h"
#include "AssetDescriptor.h"

/////////////////////////////////////////////////
// Generation
////////////////////////////////////////////////

typedef struct DeccanAssetHandle {
    uint32_t id;
} DeccanAssetHandle;

ZPL_TABLE_DECLARE(, asset_list_t, asset_list_, DeccanAssetHandle);

typedef struct asset_entry_t {
    DeccanAssetDescriptor desc;
    asset_list_t entries;
} asset_entry_t;

ZPL_TABLE_DECLARE(, asset_table_t, asset_table_, asset_entry_t);

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct DeccanAssetManager {
    asset_table_t assets;
    zpl_array(void *) asset_buffer;
    DeccanHandlePool *pool;
} DeccanAssetManager;

/////////////////////////////////////////////////
// Asset Manager
////////////////////////////////////////////////

DE_API void DE_AssetInitManager(DeccanAssetManager *manager, size_t count, DeccanAssetDescriptor *desc);
DE_API void DE_AssetDestroyManager(DeccanAssetManager *manager);

DE_API void DE_AssetSetManagerInst(DeccanAssetManager *manager);

DE_API DeccanAssetHandle DE_AssetLoad(const char *type, const char *name, SDL_RWops *file);
DE_API DeccanAssetHandle DE_AssetLoadFromFile(const char *type, const char *name, const char *file_name, bool is_binary);
DE_API DeccanAssetHandle DE_AssetLoadFromMem(const char *type, const char *name, size_t size, void *memory);

DE_API DeccanAssetHandle DE_AssetGet(const char *type, const char *file_name);
DE_API void *DE_AssetGetRaw(DeccanAssetHandle handle);

DE_API bool DE_AssetRemove(const char *type, const char *name);
