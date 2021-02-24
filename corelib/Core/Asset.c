/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Asset.h"

struct AssetManager {
    const char *key;
    DeccanAsset *value;
};

DE_PRIV struct AssetManager *manager = NULL;

DE_IMPL void DE_AssetLoadAsset(const char *type, const char *name, void *asset) {
    int32_t index = stbds_shgeti(manager, type);
    struct AssetManager assets;

    if (index == -1) {
        assets.key = DE_StringNew(type);
        assets.value = NULL;
    }
    else {
        assets = manager[index];
    }

    stbds_shput(assets.value, name, asset);
    stbds_shputs(manager, assets);
}

DE_IMPL void *DE_AssetGetAsset(const char *type, const char *name) {
    struct AssetManager assets = stbds_shgets(manager, type);
    return stbds_shget(assets.value, name);
}
