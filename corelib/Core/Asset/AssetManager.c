#include "AssetManager.h"
#include "../FileSys.h"

#define POOL_INITIAL_CAP 100

DE_PRIV struct {
    DeccanAssetManager *manager;
} Asset_Info = {
    .manager = NULL,
};

DE_API void DE_AssetSetManagerInst(DeccanAssetManager *manager) {
    Asset_Info.manager = manager;
}

DE_IMPL void DE_AssetInitManager(size_t count, DeccanAssetDescriptor *desc) {
    Asset_Info.manager->system = NULL;
    Asset_Info.manager->asset_buffer = NULL;
    
    Asset_Info.manager->desc = NULL;

    for (int i = 0; i < count; i++) {
        stbds_shputs(Asset_Info.manager->desc, desc[i]);
    }

    Asset_Info.manager->pool = sx_handle_create_pool(sx_alloc_malloc(), POOL_INITIAL_CAP);
}

DE_IMPL void *DE_AssetLoadFromFile(const char *type, const char *file_name) {
    /* TODO: Binary formats */
    SDL_RWops *file = DE_FSLocateFile(file_name, false); 
    char *data = DE_FSGetFileContent(file);

    DeccanAssetDescriptor desc = stbds_shgets(Asset_Info.manager->desc, type);
    /* if (desc == NULL) {
        DE_ERROR("Invalid type of asset: %s", type);
        return NULL;
    }
    */

    /* TODO: Actually send size */
    void *asset = desc.calls.Create(data, 1);
    if (asset == NULL) {
        DE_ERROR("Could not create asset: %s", file_name);
        return NULL;
    }

    Asset *asset_class = stbds_shget(Asset_Info.manager->system, type);

    Asset asset_entry = {
        .key = file_name,
        .value = sx_handle_new(Asset_Info.manager->pool), /* 1; handle */
    };

    stbds_shputs(asset_class, asset_entry);
    stbds_shput(Asset_Info.manager->system, type, asset_class); 

    RawAsset raw_asset = {
        .internal_data = asset,
    };
    stbds_arrput(Asset_Info.manager->asset_buffer, raw_asset);

    return asset;
}

DE_IMPL void *DE_AssetGet(const char *type, const char *file_name) {
    Asset *asset_class = stbds_shget(Asset_Info.manager->system, type);
    uint32_t handle = stbds_shget(asset_class, file_name);

    uint32_t index = sx_handle_index(handle); /* handle */;

    RawAsset asset = Asset_Info.manager->asset_buffer[index];
    return asset.internal_data;
}
