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
    deccan_asset_manager_t *manager;
    deccan_asset_handle_t invalid_asset;
} asset_info = {
    .manager = NULL,
    .invalid_asset = { -1 },
};

////////////////////////////////////////////////////////////////////////////////

ZPL_TABLE_DEFINE(asset_list_t, asset_list_, deccan_asset_handle_t);
ZPL_TABLE_DEFINE(asset_table_t, asset_table_, asset_entry_t);

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_asset_init_manager(deccan_asset_manager_t *manager, size_t count, deccan_asset_descriptor_t *desc) {
    zpl_array_init(manager->asset_buffer, deccan_zpl_allocator());
    asset_table_init(&manager->assets, deccan_zpl_allocator());
    manager->pool = deccan_handle_pool_create(POOL_INITIAL_CAP);

    for (int i = 0; i < count; i++) {
        asset_entry_t entry;
        entry.desc = desc[i];
        asset_list_init(&entry.entries, deccan_zpl_allocator());
        asset_table_set(&manager->assets, deccan_string_hash(desc[i].key, strlen(desc[i].key)), entry);
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_PRIV void asset_destroy_func(uint64_t index, asset_entry_t value) {
    asset_list_destroy(&value.entries);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_asset_destroy_manager(deccan_asset_manager_t *manager) {
    asset_table_map(&manager->assets, asset_destroy_func);
    asset_table_destroy(&manager->assets);
    deccan_handle_pool_destroy(manager->pool);
    zpl_array_free(manager->asset_buffer);
}

////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_asset_set_manager_inst(deccan_asset_manager_t *manager) {
    asset_info.manager = manager;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_asset_handle_t deccan_asset_load(const char *type, const char *name, SDL_RWops *file) {
    if (file == NULL) {
        return asset_info.invalid_asset;
    }

    const char *data = deccan_fs_get_file_content(file);
    if (data == NULL) {
        return asset_info.invalid_asset;
    }
    
    asset_entry_t *entry = asset_table_get(&asset_info.manager->assets, deccan_string_hash(type, strlen(type)));
    
    void *asset = entry->desc.calls.create(data, SDL_RWsize(file));
    if (asset == NULL) {
        DE_ERROR("Could not create asset: %s", name);
        return asset_info.invalid_asset;
    }

    deccan_asset_handle_t handle;
    handle.id = deccan_handle_new(asset_info.manager->pool);

    asset_list_set(&entry->entries, deccan_string_hash(name, strlen(name)), handle);
    zpl_array_append(asset_info.manager->asset_buffer, asset);

    return handle;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_asset_handle_t deccan_asset_load_from_file(const char *type, const char *name, const char *file_name, bool is_binary) {
    SDL_RWops *file = SDL_RWFromFile(file_name, (is_binary ? "rb" : "r"));
    if (file == NULL) {
        DE_ERROR("Cannot load file: %s: %s", file_name, SDL_GetError());
        return asset_info.invalid_asset;
    }
    return deccan_asset_load(type, name, file);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_asset_handle_t deccan_asset_load_from_mem(const char *type, const char *name, size_t size, void *memory) {
    SDL_RWops *file = SDL_RWFromMem(memory, size);
    if (file == NULL) {
        DE_ERROR("Cannot read memory block: %s", SDL_GetError());
        return asset_info.invalid_asset;
    }
    return deccan_asset_load(type, name, file);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_asset_handle_t deccan_asset_get(const char *type, const char *name) {
    asset_entry_t *entry = asset_table_get(&asset_info.manager->assets, deccan_string_hash(type, strlen(type)));
    deccan_asset_handle_t *handle = asset_list_get(&entry->entries, deccan_string_hash(name, strlen(name)));
    if ((handle == NULL) || deccan_handle_valid(asset_info.manager->pool, handle->id) == false) { 
        DE_WARN("Cannot find asset: %s", name);
        return asset_info.invalid_asset;
    }

    return *handle;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void *deccan_asset_get_raw(deccan_asset_handle_t handle) {
    uint32_t index = deccan_handle_index(asset_info.manager->pool, handle.id);
    if (index == -1)
        return NULL;
    return asset_info.manager->asset_buffer[index];
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_asset_remove(const char *type, const char *name) {
    asset_entry_t *entry = asset_table_get(&asset_info.manager->assets, deccan_string_hash(type, strlen(type)));
    
    deccan_asset_handle_t *handle = asset_list_get(&entry->entries, deccan_string_hash(name, strlen(name)));
    if ((handle == NULL) || deccan_handle_valid(asset_info.manager->pool, handle->id) == false) { 
        DE_ERROR("Asset '%s' cannot be removed because it is not found", name);
        return false;
    }

    uint32_t index = deccan_handle_index(asset_info.manager->pool, handle->id);
    if (index == -1)
        return false;

    deccan_handle_delete(asset_info.manager->pool, handle->id);

    void *asset = asset_info.manager->asset_buffer[index];
    entry->desc.calls.destroy(asset);

    zpl_array_remove_at(asset_info.manager->asset_buffer, index);

    asset_list_remove(&entry->entries, deccan_string_hash(name, strlen(name)));

    return true;
}
