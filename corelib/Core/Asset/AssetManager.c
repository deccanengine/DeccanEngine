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


ZPL_TABLE_DEFINE(AssetList, AssetList_, uint32_t);
ZPL_TABLE_DEFINE(AssetTable, AssetTable_, AssetEntry);

DE_IMPL void DE_AssetInitManager(DeccanAssetManager *manager, size_t count, DeccanAssetDescriptor *desc) {
    DE_ArrayCreate(&manager->asset_buffer);
    AssetTable_init(&manager->assets, zpl_heap_allocator());
    manager->pool = DE_HandlePoolCreate(POOL_INITIAL_CAP);

    for (int i = 0; i < count; i++) {
        AssetEntry entry;
        entry.desc = desc[i];
        AssetList_init(&entry.entries, zpl_heap_allocator());
        AssetTable_set(&manager->assets, DE_StringHash(desc[i].key, strlen(desc[i].key)), entry);
    }
}

DE_PRIV void AssetDestroyFunc(uint64_t index, AssetEntry value) {
    AssetList_destroy(&value.entries);
}

DE_IMPL void DE_AssetDestroyManager(DeccanAssetManager *manager) {
    AssetTable_map(&manager->assets, AssetDestroyFunc);
    AssetTable_destroy(&manager->assets);
    DE_HandlePoolDestroy(manager->pool);
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
    
    AssetEntry *entry = AssetTable_get(&Asset_Info.manager->assets, DE_StringHash(type, strlen(type)));
    
    void *asset = entry->desc.calls.Create(data, SDL_RWsize(file));
    if (asset == NULL) {
        DE_ERROR("Could not create asset: %s", name);
        return -1;
    }

    uint32_t handle = DE_HandleNew(Asset_Info.manager->pool);

    AssetList_set(&entry->entries, DE_StringHash(name, strlen(name)), handle);
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
    AssetEntry *entry = AssetTable_get(&Asset_Info.manager->assets, DE_StringHash(type, strlen(type)));
    uint32_t handle = *AssetList_get(&entry->entries, DE_StringHash(name, strlen(name)));
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
    AssetEntry *entry = AssetTable_get(&Asset_Info.manager->assets, DE_StringHash(type, strlen(type)));
    uint32_t handle = *AssetList_get(&entry->entries, DE_StringHash(name, strlen(name)));
    if (DE_HandleValid(Asset_Info.manager->pool, handle) == false) {
        DE_ERROR("Asset '%s' cannot be removed because it is not found", name);
        return false;
    }

    uint32_t index = DE_HandleIndex(Asset_Info.manager->pool, handle);

    DE_HandleDelete(Asset_Info.manager->pool, handle);

    void *asset = Asset_Info.manager->asset_buffer.data[index];
    entry->desc.calls.Destroy(asset);

    DE_ArrayRemoveItem(&Asset_Info.manager->asset_buffer, index);
    
    AssetList_remove(&entry->entries, DE_StringHash(name, strlen(name)));

    return true;
}
