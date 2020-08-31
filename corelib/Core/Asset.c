/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Asset.h"

struct AssetManager {
    const char *key;
    DeccanAsset *value;
};

static struct AssetManager *manager = NULL;

void DE_Asset_LoadAsset(const char *type, const char *name, void *asset) {
    int32_t index = stbds_shgeti(manager, type);
    struct AssetManager assets;

    if(index == -1) {
        assets.key = DE_NEWSTRING(type);
        assets.value = NULL;
    }
    else {
        assets = manager[index];
    }

    stbds_shput(assets.value, name, asset);
    stbds_shputs(manager, assets);
}

void* DE_Asset_GetAsset(const char *type, const char *name) {
    struct AssetManager assets = stbds_shgets(manager, type);
    return stbds_shget(assets.value, name);
}
