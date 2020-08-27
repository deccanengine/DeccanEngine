/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Asset.h"

static DeccanAssetManager *mngr = NULL;

void DE_Asset_RegisterAssetType(const char *type) {
    DeccanAssetManager asset;
    asset.key = DE_NEWSTRING(type);
    asset.value = NULL;
    stbds_arrput(mngr, asset);
}

void DE_Asset_LoadAsset(const char *type, const char *name, void *asset) {
    for(int i = 0; i < stbds_arrlen(mngr); i++) {
        if(!strcmp(mngr[i].key, type)) {
            stbds_shput(mngr[i].value, name, asset);
        }
    }
}

void* DE_Asset_GetAsset(const char *type, const char *name) {
    for(int i = 0; i < stbds_arrlen(mngr); i++) {
        if(!strcmp(mngr[i].key, type)) {
            return stbds_shget(mngr[i].value, name);
        }
    }
    return NULL;
}
