#pragma once
#include "../../Config.h"

typedef struct AssetCallbacks {
    void *(*Create)(void *mem, size_t size);
    void  (*Destroy)(void *asset);
} AssetCallbacks;

typedef struct DeccanAssetDescriptor {
    const char *key;
    const char **ext; /* Unused for now! */
    bool is_binary;   /* Unused for now! */
    AssetCallbacks calls;
} DeccanAssetDescriptor;
