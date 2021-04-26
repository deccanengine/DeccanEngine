/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../Config.h"
#include "../Array.h"
#include "../Handle.h"
#include "../String.h"
#include "AssetDescriptor.h"

/////////////////////////////////////////////////
// Generation
////////////////////////////////////////////////

ZPL_TABLE_DECLARE(, AssetList, AssetList_, uint32_t);

typedef struct AssetEntry {
    DeccanAssetDescriptor desc;
    AssetList entries;
} AssetEntry;

ZPL_TABLE_DECLARE(, AssetTable, AssetTable_, AssetEntry);


/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct DeccanAssetManager {
    AssetTable assets;
    DeccanArray asset_buffer; /* Array of RawAsset */
    DeccanHandlePool *pool;
} DeccanAssetManager;

/////////////////////////////////////////////////
// Asset Manager
////////////////////////////////////////////////

DE_API void DE_AssetInitManager(DeccanAssetManager *manager, size_t count, DeccanAssetDescriptor *desc);
DE_API void DE_AssetDestroyManager(DeccanAssetManager *manager);

DE_API void DE_AssetSetManagerInst(DeccanAssetManager *manager);

DE_API uint32_t DE_AssetLoad(const char *type, const char *name, SDL_RWops *file);
DE_API uint32_t DE_AssetLoadFromFile(const char *type, const char *name, const char *file_name, bool is_binary);
DE_API uint32_t DE_AssetLoadFromMem(const char *type, const char *name, size_t size, void *memory);

DE_API uint32_t DE_AssetGet(const char *type, const char *file_name);
DE_API void *DE_AssetGetRaw(uint32_t handle);

DE_API bool DE_AssetRemove(const char *type, const char *name);
