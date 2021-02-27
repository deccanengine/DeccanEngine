#pragma once
#include "../../Config.h"
#include "AssetDescriptor.h"

typedef struct Asset {
    const char *key;
    uint32_t value;
} Asset;

typedef struct AssetSystem {
    const char *key;
    Asset *value;
} AssetSystem;

typedef struct RawAsset {
    void *internal_data;
} RawAsset;

typedef struct DeccanAssetManager {
    DeccanAssetDescriptor *desc;
    AssetSystem *system;
    RawAsset *asset_buffer;
    sx_handle_pool *pool;
} DeccanAssetManager;

DE_API void DE_AssetInitManager(DeccanAssetManager *manager, size_t count, DeccanAssetDescriptor *desc);
DE_API void DE_AssetDestroyManager(DeccanAssetManager *manager);

DE_API void DE_AssetSetManagerInst(DeccanAssetManager *manager);

DE_API void *DE_AssetLoad(const char *type, const char *name, SDL_RWops *file);
DE_API void *DE_AssetLoadFromFile(const char *type, const char *name, const char *file_name, bool is_binary);
DE_API void *DE_AssetLoadFromMem(const char *type, const char *name, size_t size, void *memory);

DE_API void *DE_AssetGet(const char *type, const char *file_name);
