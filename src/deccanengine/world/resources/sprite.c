/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "sprite.h"

////////////////////////////////////////////////////////////////////////////////
// Sprite asset
////////////////////////////////////////////////////////////////////////////////

void *sprite_asset_create(const unsigned char *mem, size_t size) {
    int32_t width, height;

    /* We dont need to collect the number of channels
     * Just ask for 4 channels here. If alpha is absent
     * stb_image will handle it. */
    stbi_uc *data = stbi_load_from_memory(mem, size, &width, &height, NULL, STBI_rgb_alpha);
    if (data == NULL) {
        // TODO: pass in asset name for error handling
        DE_WARN("Cannot load image");
    }

    deccan_surface_t surfaces[] = {
        { data, size, SG_PIXELFORMAT_RGBA8 },
    };

    deccan_texture_t *texture = deccan_alloc(sizeof(deccan_texture_t), 1);
    deccan_texture_create_from_mem(texture, width, height, 1, surfaces);

    stbi_image_free(data);
    return texture;
}

////////////////////////////////////////////////////////////////////////////////

bool sprite_asset_destroy(void *asset) {
    deccan_texture_destroy((deccan_texture_t *)asset);
    deccan_free((deccan_texture_t *)asset);
    return true;
}
