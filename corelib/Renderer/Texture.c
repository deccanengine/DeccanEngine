#include "Texture.h"
#include <assert.h>

void CreateTexture(DeccanTexture *texture, int32_t width, int32_t height, int format, sg_image_content *image_content) {
    texture->width = width;
    texture->height = height;
    texture->pixel_format = format;

    sg_image_desc desc = {
        .width = texture->width,
        .height = texture->height,
        .pixel_format = texture->pixel_format,
        .min_filter = SG_FILTER_NEAREST,
        .mag_filter = SG_FILTER_NEAREST,
        .content = *image_content,
    };

    texture->image = sg_make_image(&desc);
}

void DE_TextureCreateFromMem(
    DeccanTexture *texture, int32_t width, int32_t height, size_t count, DeccanSurface *surfaces) {
    assert(&surfaces[0] != NULL);

    sg_image_content image_content;
    memcpy(&image_content, surfaces, sizeof(sg_subimage_content) * count);

    CreateTexture(texture, width, height, surfaces[0].format, &image_content);
}

void DE_TextureCreateBlankRGBA(DeccanTexture *texture, int32_t width, int32_t height, uint32_t color) {
    int size_bytes = sizeof(uint32_t) * width * height;
    uint32_t *pixels = malloc(size_bytes);

    for (int w = 0; w < width; w++) {
        for (int h = 0; h < height; h++) {
            pixels[h * width + w] = color;
        }
    }

    sg_image_content image_content = {
        .subimage[0][0] =
            {
                .ptr = pixels,
                .size = size_bytes,
            },
    };

    CreateTexture(texture, width, height, SG_PIXELFORMAT_RGBA8, &image_content);

    free(pixels);
}

void DE_TextureDestroy(DeccanTexture *texture) {
    sg_destroy_image(texture->image);
}
