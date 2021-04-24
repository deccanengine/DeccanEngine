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

    manager->pool = DE_HandlePoolCreate(POOL_INITIAL_CAP);
}

DE_IMPL void DE_AssetDestroyManager(DeccanAssetManager *manager) {
    for (int i = 0; i < stbds_shlen(manager->system); i++) {
        DeccanAssetDescriptor desc = stbds_shgets(manager->desc, manager->system[i].key);
        Asset *asset_class = manager->system[i].value;

        for (int j = 0; j < stbds_shlen(asset_class); j++) {
            Asset asset_entry = asset_class[j];

            uint32_t handle = asset_entry.value;
            uint32_t index = DE_HandleIndex(Asset_Info.manager->pool, handle);

            void *asset = manager->asset_buffer.data[index];
            desc.calls.Destroy(asset);
        }
    }

    DE_HandlePoolDestroy(manager->pool);

    if (manager->system != NULL) {
        stbds_shfree(manager->system);
    }

    DE_ArrayDestroy(&manager->asset_buffer);
}

DE_API void DE_AssetSetManagerInst(DeccanAssetManager *manager) {
    Asset_Info.manager = manager;
}

DE_IMPL uint32_t DE_AssetLoad(const char *type, const char *name, SDL_RWops *file) {
    if (file == NULL) {
        return -1;
    }

    const char *data = DE_FSGetFileContent(file);
    if (data == NULL) {
        return -1;
    }

    DeccanAssetDescriptor desc = stbds_shgets(Asset_Info.manager->desc, type);

    void *asset = desc.calls.Create(data, SDL_RWsize(file));
    if (asset == NULL) {
        DE_ERROR("Could not create asset: %s", name);
        return -1;
    }

    Asset *asset_class = stbds_shget(Asset_Info.manager->system, type);
    
    uint32_t handle = DE_HandleNew(Asset_Info.manager->pool);

    Asset asset_entry = {
        .key = name,
        .value = handle,
    };

    stbds_shputs(asset_class, asset_entry);
    stbds_shput(Asset_Info.manager->system, type, asset_class);

    DE_ArrayAddItem(&Asset_Info.manager->asset_buffer, (void *)asset);

    return handle;
}

DE_IMPL uint32_t DE_AssetLoadFromFile(const char *type, const char *name, const char *file_name, bool is_binary) {
    SDL_RWops *file = SDL_RWFromFile(file_name, (is_binary ? "rb" : "r"));
    if (file == NULL) {
        DE_ERROR("Cannot load file: %s: %s", file_name, SDL_GetError());
        return -1;
    }
    return DE_AssetLoad(type, name, file);
}

DE_IMPL uint32_t DE_AssetLoadFromMem(const char *type, const char *name, size_t size, void *memory) {
    SDL_RWops *file = SDL_RWFromMem(memory, size);
    if (file == NULL) {
        DE_ERROR("Cannot read memory block: %s", SDL_GetError());
        return -1;
    }
    return DE_AssetLoad(type, name, file);
}

DE_IMPL uint32_t DE_AssetGet(const char *type, const char *name) {
    Asset *asset_class = stbds_shget(Asset_Info.manager->system, type);

    uint32_t handle = stbds_shget(asset_class, name);
    if (DE_HandleValid(Asset_Info.manager->pool, handle) == false) { 
        DE_ERROR("Cannot find asset: %s", name);
        return -1;
    }

    return handle;
}

DE_IMPL void *DE_AssetGetRaw(uint32_t handle) {
    uint32_t index = DE_HandleIndex(Asset_Info.manager->pool, handle);
    if (index == -1)
        return NULL;
    return Asset_Info.manager->asset_buffer.data[index];
}

DE_IMPL bool DE_AssetRemove(const char *type, const char *name) {
    DeccanAssetDescriptor desc = stbds_shgets(Asset_Info.manager->desc, type);
    Asset *asset_class = stbds_shget(Asset_Info.manager->system, type);

    uint32_t handle = stbds_shget(asset_class, name);
    if (DE_HandleValid(Asset_Info.manager->pool, handle) == false) {
        DE_ERROR("Asset '%s' cannot be removed because it is not found", name);
        return false;
    }

    uint32_t index = DE_HandleIndex(Asset_Info.manager->pool, handle);

    DE_HandleDelete(Asset_Info.manager->pool, handle);

    void *asset = Asset_Info.manager->asset_buffer.data[index];
    desc.calls.Destroy(asset);

    DE_ArrayRemoveItem(&Asset_Info.manager->asset_buffer, index);

    return true;
}
