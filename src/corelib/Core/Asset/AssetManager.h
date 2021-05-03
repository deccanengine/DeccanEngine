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

////////////////////////////////////////////////////////////////////////////////
// Generation
////////////////////////////////////////////////////////////////////////////////

typedef struct deccan_asset_handle_t {
    uint32_t id;
} deccan_asset_handle_t;

ZPL_TABLE_DECLARE(, asset_list_t, asset_list_, deccan_asset_handle_t);

typedef struct asset_entry_t {
    deccan_asset_descriptor_t desc;
    asset_list_t entries;
} asset_entry_t;

ZPL_TABLE_DECLARE(, asset_table_t, asset_table_, asset_entry_t);

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct deccan_asset_manager_t {
    asset_table_t assets;
    zpl_array(void *) asset_buffer;
    deccan_handle_pool_t *pool;
} deccan_asset_manager_t;

////////////////////////////////////////////////////////////////////////////////
// Asset Manager
////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_asset_init_manager(deccan_asset_manager_t *manager, size_t count, deccan_asset_descriptor_t *desc);
DE_API void deccan_asset_destroy_manager(deccan_asset_manager_t *manager);

DE_API void deccan_asset_set_manager_inst(deccan_asset_manager_t *manager);

DE_API deccan_asset_handle_t deccan_asset_load(const char *type, const char *name, SDL_RWops *file);
DE_API deccan_asset_handle_t deccan_asset_load_from_file(const char *type, const char *name, const char *file_name, bool is_binary);
DE_API deccan_asset_handle_t deccan_asset_load_from_mem(const char *type, const char *name, size_t size, void *memory);

DE_API deccan_asset_handle_t deccan_asset_get(const char *type, const char *file_name);
DE_API void *deccan_asset_get_raw(deccan_asset_handle_t handle);

DE_API bool deccan_asset_remove(const char *type, const char *name);
