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
