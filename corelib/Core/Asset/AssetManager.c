/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "AssetManager.h"
#include "../Utils.h"
#include "../FileSys.h"

#define POOL_INITIAL_CAP 100

DE_PRIV struct {
    DeccanAssetManager *manager;
} Asset_Info = {
    .manager = NULL,
};

DE_IMPL void DE_AssetInitManager(DeccanAssetManager *manager, size_t count, DeccanAssetDescriptor *desc) {
    manager->system = NULL;
    manager->desc = NULL;

    DE_ArrayCreate(&manager->asset_buffer);

    for (int i = 0; i < count; i++) {
        stbds_shputs(manager->desc, desc[i]);
    }

    manager->pool = sx_handle_create_pool(DE_GetSXAlloc(), POOL_INITIAL_CAP);
}

DE_IMPL void DE_AssetDestroyManager(DeccanAssetManager *manager) {
    for (int i = 0; i < stbds_shlen(manager->system); i++) {
        DeccanAssetDescriptor desc = stbds_shgets(manager->desc, manager->system[i].key);
        Asset *asset_class = manager->system[i].value;

        for (int j = 0; j < stbds_shlen(asset_class); j++) {
            Asset asset_entry = asset_class[j];

            uint32_t handle = asset_entry.value;
            uint32_t index = sx_handle_index(handle);

            RawAsset *asset = manager->asset_buffer.data[index];
            desc.calls.Destroy(asset->internal_data);
        }
    }

    sx_handle_destroy_pool(manager->pool, DE_GetSXAlloc());

    if (manager->system != NULL) {
        stbds_shfree(manager->system);
    }

    DE_ArrayDestroy(&manager->asset_buffer);
}

DE_API void DE_AssetSetManagerInst(DeccanAssetManager *manager) {
    Asset_Info.manager = manager;
}

DE_IMPL void *DE_AssetLoad(const char *type, const char *name, SDL_RWops *file) {
    if (file == NULL) {
        return NULL;
    }

    char *data = DE_FSGetFileContent(file);
    if (data == NULL) {
        return NULL;
    }

    DeccanAssetDescriptor desc = stbds_shgets(Asset_Info.manager->desc, type);

    void *asset = desc.calls.Create(data, SDL_RWsize(file));
    if (asset == NULL) {
        DE_ERROR("Could not create asset: %s", name);
        return NULL;
    }

    Asset *asset_class = stbds_shget(Asset_Info.manager->system, type);

    if (sx_handle_full(Asset_Info.manager->pool)) {
        sx_handle_grow_pool(Asset_Info.manager->pool, DE_GetSXAlloc());
    }

    Asset asset_entry = {
        .key = name,
        .value = sx_handle_new(Asset_Info.manager->pool),
    };

    stbds_shputs(asset_class, asset_entry);
    stbds_shput(Asset_Info.manager->system, type, asset_class);

    RawAsset raw_asset = {
        .internal_data = asset,
    };
    DE_ArrayAddItem(&Asset_Info.manager->asset_buffer, (void *)&raw_asset);

    return asset;
}

DE_IMPL void *DE_AssetLoadFromFile(const char *type, const char *name, const char *file_name, bool is_binary) {
    SDL_RWops *file = SDL_RWFromFile(file_name, (is_binary ? "rb" : "r"));
    if (file == NULL) {
        DE_ERROR("Cannot load file: %s: %s", file_name, SDL_GetError());
        return NULL;
    }
    return DE_AssetLoad(type, name, file);
}

DE_IMPL void *DE_AssetLoadFromMem(const char *type, const char *name, size_t size, void *memory) {
    SDL_RWops *file = SDL_RWFromMem(memory, size);
    if (file == NULL) {
        DE_ERROR("Cannot read memory block: %s", SDL_GetError());
        return NULL;
    }
    return DE_AssetLoad(type, name, file);
}

DE_IMPL void *DE_AssetGet(const char *type, const char *name) {
    Asset *asset_class = stbds_shget(Asset_Info.manager->system, type);

    uint32_t handle = stbds_shget(asset_class, name);
    if (handle == 0 || sx_handle_valid(Asset_Info.manager->pool, handle) == false) {
        DE_ERROR("Cannot find asset: %s", name);
        return NULL;
    }

    uint32_t index = sx_handle_index(handle);

    RawAsset *asset = Asset_Info.manager->asset_buffer.data[index];
    return asset->internal_data;
}

DE_IMPL bool DE_AssetRemove(const char *type, const char *name) {
    DeccanAssetDescriptor desc = stbds_shgets(Asset_Info.manager->desc, type);
    Asset *asset_class = stbds_shget(Asset_Info.manager->system, type);

    uint32_t handle = stbds_shget(asset_class, name);
    if (handle == 0 || sx_handle_valid(Asset_Info.manager->pool, handle) == false) {
        DE_ERROR("Asset '%s' cannot be removed because it is not found", name);
        return false;
    }

    uint32_t index = sx_handle_index(handle);

    sx_handle_del(Asset_Info.manager->pool, handle);

    RawAsset *asset = Asset_Info.manager->asset_buffer.data[index];
    desc.calls.Destroy(asset->internal_data);

    DE_ArrayRemoveItem(&Asset_Info.manager->asset_buffer, index);

    return true;
}
