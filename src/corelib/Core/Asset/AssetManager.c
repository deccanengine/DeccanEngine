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

////////////////////////////////////////////////////////////////////////////////

DE_PRIV struct {
    DeccanAssetManager *manager;
    DeccanAssetHandle invalid_asset;
} Asset_Info = {
    .manager = NULL,
    .invalid_asset = { -1 },
};

////////////////////////////////////////////////////////////////////////////////

ZPL_TABLE_DEFINE(asset_list_t, asset_list_, DeccanAssetHandle);
ZPL_TABLE_DEFINE(asset_table_t, asset_table_, asset_entry_t);

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void DE_AssetInitManager(DeccanAssetManager *manager, size_t count, DeccanAssetDescriptor *desc) {
    zpl_array_init(manager->asset_buffer, DE_ZPLAllocator());
    asset_table_init(&manager->assets, DE_ZPLAllocator());
    manager->pool = DE_HandlePoolCreate(POOL_INITIAL_CAP);

    for (int i = 0; i < count; i++) {
        asset_entry_t entry;
        entry.desc = desc[i];
        asset_list_init(&entry.entries, DE_ZPLAllocator());
        asset_table_set(&manager->assets, DE_StringHash(desc[i].key, strlen(desc[i].key)), entry);
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_PRIV void AssetDestroyFunc(uint64_t index, asset_entry_t value) {
    asset_list_destroy(&value.entries);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void DE_AssetDestroyManager(DeccanAssetManager *manager) {
    asset_table_map(&manager->assets, AssetDestroyFunc);
    asset_table_destroy(&manager->assets);
    DE_HandlePoolDestroy(manager->pool);
    zpl_array_free(manager->asset_buffer);
}

////////////////////////////////////////////////////////////////////////////////

DE_API void DE_AssetSetManagerInst(DeccanAssetManager *manager) {
    Asset_Info.manager = manager;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL DeccanAssetHandle DE_AssetLoad(const char *type, const char *name, SDL_RWops *file) {
    if (file == NULL) {
        return Asset_Info.invalid_asset;
    }

    const char *data = DE_FSGetFileContent(file);
    if (data == NULL) {
        return Asset_Info.invalid_asset;
    }
    
    asset_entry_t *entry = asset_table_get(&Asset_Info.manager->assets, DE_StringHash(type, strlen(type)));
    
    void *asset = entry->desc.calls.Create(data, SDL_RWsize(file));
    if (asset == NULL) {
        DE_ERROR("Could not create asset: %s", name);
        return Asset_Info.invalid_asset;
    }

    DeccanAssetHandle handle;
    handle.id = DE_HandleNew(Asset_Info.manager->pool);

    asset_list_set(&entry->entries, DE_StringHash(name, strlen(name)), handle);
    zpl_array_append(Asset_Info.manager->asset_buffer, asset);

    return handle;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL DeccanAssetHandle DE_AssetLoadFromFile(const char *type, const char *name, const char *file_name, bool is_binary) {
    SDL_RWops *file = SDL_RWFromFile(file_name, (is_binary ? "rb" : "r"));
    if (file == NULL) {
        DE_ERROR("Cannot load file: %s: %s", file_name, SDL_GetError());
        return Asset_Info.invalid_asset;
    }
    return DE_AssetLoad(type, name, file);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL DeccanAssetHandle DE_AssetLoadFromMem(const char *type, const char *name, size_t size, void *memory) {
    SDL_RWops *file = SDL_RWFromMem(memory, size);
    if (file == NULL) {
        DE_ERROR("Cannot read memory block: %s", SDL_GetError());
        return Asset_Info.invalid_asset;
    }
    return DE_AssetLoad(type, name, file);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL DeccanAssetHandle DE_AssetGet(const char *type, const char *name) {
    asset_entry_t *entry = asset_table_get(&Asset_Info.manager->assets, DE_StringHash(type, strlen(type)));
    DeccanAssetHandle *handle = asset_list_get(&entry->entries, DE_StringHash(name, strlen(name)));
    if ((handle == NULL) || DE_HandleValid(Asset_Info.manager->pool, handle->id) == false) { 
        DE_WARN("Cannot find asset: %s", name);
        return Asset_Info.invalid_asset;
    }

    return *handle;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void *DE_AssetGetRaw(DeccanAssetHandle handle) {
    uint32_t index = DE_HandleIndex(Asset_Info.manager->pool, handle.id);
    if (index == -1)
        return NULL;
    return Asset_Info.manager->asset_buffer[index];
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool DE_AssetRemove(const char *type, const char *name) {
    asset_entry_t *entry = asset_table_get(&Asset_Info.manager->assets, DE_StringHash(type, strlen(type)));
    
    DeccanAssetHandle *handle = asset_list_get(&entry->entries, DE_StringHash(name, strlen(name)));
    if ((handle == NULL) || DE_HandleValid(Asset_Info.manager->pool, handle->id) == false) { 
        DE_ERROR("Asset '%s' cannot be removed because it is not found", name);
        return false;
    }

    uint32_t index = DE_HandleIndex(Asset_Info.manager->pool, handle->id);
    if (index == -1)
        return false;

    DE_HandleDelete(Asset_Info.manager->pool, handle);

    void *asset = Asset_Info.manager->asset_buffer[index];
    entry->desc.calls.Destroy(asset);

    zpl_array_remove_at(Asset_Info.manager->asset_buffer, index);

    asset_list_remove(&entry->entries, DE_StringHash(name, strlen(name)));

    return true;
}
