/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Sprite.h"

////////////////////////////////////////////////////////////////////////////////
// Sprite asset
////////////////////////////////////////////////////////////////////////////////

void *DE_SpriteAssetCreate(const char *mem, size_t size) {
    int32_t width, height;

    /* We dont need to collect the number of channels
     * Just ask for 4 channels here. If alpha is absent
     * stb_image will handle it. */
    stbi_uc *data = stbi_load_from_memory(mem, size, &width, &height, NULL, STBI_rgb_alpha);
    if (data == NULL) {
        // TODO: pass in asset name for error handling
        DE_WARN("Cannot load image");
    }

    DeccanSurface surfaces[] = {
        { data, size, SG_PIXELFORMAT_RGBA8 },
    };

    DeccanTexture *texture = DE_Alloc(sizeof(DeccanTexture), 1);
    DE_TextureCreateFromMem(texture, width, height, 1, surfaces);
    
    stbi_image_free(data);
    return texture;
}

////////////////////////////////////////////////////////////////////////////////

bool DE_SpriteAssetDestroy(void *asset) {
    DE_TextureDestroy((DeccanTexture *)asset);
    DE_Free((DeccanTexture *)asset);
    return true;
}
