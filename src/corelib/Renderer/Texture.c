/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Texture.h"

DE_PRIV void CreateTexture(DeccanTexture *texture, int32_t width, int32_t height, int format, 
    sg_image_data *image_content) {
    texture->width = width;
    texture->height = height;
    texture->pixel_format = format;

    sg_image_desc desc = {
        .width = texture->width,
        .height = texture->height,
        .pixel_format = texture->pixel_format,
        .min_filter = SG_FILTER_NEAREST,
        .mag_filter = SG_FILTER_NEAREST,
        .data = *image_content,
    };

    texture->image = sg_make_image(&desc);
}

DE_IMPL void DE_TextureCreateFromMem(
    DeccanTexture *texture, int32_t width, int32_t height, size_t count, DeccanSurface *surfaces) {
    assert(&surfaces[0] != NULL);

    sg_image_data image_content;
    for (int i = 0; i < count; i += 1) {
        image_content.subimage[0][i] = (sg_range){ surfaces[i].data, surfaces[i].size };
    }

    CreateTexture(texture, width, height, surfaces[0].format, &image_content);
}

DE_IMPL void DE_TextureCreateBlankRGBA(DeccanTexture *texture, int32_t width, int32_t height, uint32_t color) {
    int size_bytes = sizeof(uint32_t) * width * height;
    uint32_t *pixels = DE_Alloc(size_bytes, 1);

    for (int w = 0; w < width; w++) {
        for (int h = 0; h < height; h++) {
            pixels[h * width + w] = color;
        }
    }

    sg_image_data image_content = {
        .subimage[0][0] = SG_RANGE(pixels),
    };

    CreateTexture(texture, width, height, SG_PIXELFORMAT_RGBA8, &image_content);

    DE_Free(pixels);
}

DE_IMPL void DE_TextureDestroy(DeccanTexture *texture) {
    sg_destroy_image(texture->image);
}
