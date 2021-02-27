#include "AssetManager.h"
#include "../FileSys.h"

#define POOL_INITIAL_CAP 100

DE_PRIV struct {
    DeccanAssetManager *manager;
} Asset_Info = {
    .manager = NULL,
};

DE_IMPL void DE_AssetInitManager(DeccanAssetManager *manager, size_t count, DeccanAssetDescriptor *desc) {
    manager->system = NULL;
    manager->asset_buffer = NULL;
    
    manager->desc = NULL;

    for (int i = 0; i < count; i++) {
        stbds_shputs(manager->desc, desc[i]);
    }

    manager->pool = sx_handle_create_pool(sx_alloc_malloc(), POOL_INITIAL_CAP);
}

DE_API void DE_AssetSetManagerInst(DeccanAssetManager *manager) {
    Asset_Info.manager = manager;
}

DE_IMPL void *DE_AssetLoad(const char *type, const char *name, SDL_RWops *file) {
    if (file == NULL) {
        return NULL;
    }
    char *data = DE_FSGetFileContent(file);

    DeccanAssetDescriptor desc = stbds_shgets(Asset_Info.manager->desc, type);

    /* TODO: Actually send size */
    void *asset = desc.calls.Create(data, 1);
    if (asset == NULL) {
        DE_ERROR("Could not create asset: %s", name);
        return NULL;
    }

    Asset *asset_class = stbds_shget(Asset_Info.manager->system, type);

    Asset asset_entry = {
        .key = name,
        .value = sx_handle_new(Asset_Info.manager->pool),
    };

    stbds_shputs(asset_class, asset_entry);
    stbds_shput(Asset_Info.manager->system, type, asset_class); 

    RawAsset raw_asset = {
        .internal_data = asset,
    };
    stbds_arrput(Asset_Info.manager->asset_buffer, raw_asset);

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

DE_IMPL void *DE_AssetGet(const char *type, const char *file_name) {
    Asset *asset_class = stbds_shget(Asset_Info.manager->system, type);
    uint32_t handle = stbds_shget(asset_class, file_name);

    uint32_t index = sx_handle_index(handle);

    RawAsset asset = Asset_Info.manager->asset_buffer[index];
    return asset.internal_data;
}
