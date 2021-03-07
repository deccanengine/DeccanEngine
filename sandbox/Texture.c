#include "Texture.h"

void *CreateSprite(char *mem, size_t size) {
    int32_t width, height;

    /* We dont need to collect the number of channels
     * Just ask for 4 channels here. If alpha is absent
     * stb_image will handle it. */
    stbi_uc *data = stbi_load_from_memory(mem, size, &width, &height, NULL, STBI_rgb_alpha);
    if (data == NULL) {
        DE_WARN("Cannot load image: %s", path);
    }

    sg_image img = sg_make_image(&(sg_image_desc){.width = width,
        .height = height,
        .pixel_format = SG_PIXELFORMAT_RGBA8,
        .min_filter = SG_FILTER_NEAREST,
        .mag_filter = SG_FILTER_NEAREST,
        .content.subimage[0][0] = {
            .ptr = data,
            .size = size, // sizeof(data),
        }});
    stbi_image_free(data);

    return NULL; // TODO!
}

bool DestroySprite(void *asset) {
    // TODO
}
