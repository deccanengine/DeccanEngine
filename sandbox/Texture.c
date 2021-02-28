#include "Texture.h"

void *CreateSprite(char *mem, size_t size) {
    SDL_Surface *img;
    SDL_Texture *tex;

    int32_t width, height, fmt = STBI_rgb_alpha;
    unsigned char *data;

    /* We dont need to collect the number of channels
     * Just ask for 4 channels here. If alpha is absent
     * stb_image will handle it. */
    data = stbi_load_from_memory(mem, size, /*strlen(mem),*/ &width, &height, NULL, fmt);
    if (data == NULL) {
        DE_WARN("Cannot load image: %s", path);
    }

    /* 3-channel calculation is never used but,
     * let it be here for future */
    int32_t depth, pitch;
    uint32_t pixel_fmt;
    if (fmt == STBI_rgb) {
        depth = 24;
        pitch = 3 * width;
        pixel_fmt = SDL_PIXELFORMAT_RGB24;
    }
    else {
        depth = 32;
        pitch = 4 * width;
        pixel_fmt = SDL_PIXELFORMAT_RGBA32;
    }

    img = SDL_CreateRGBSurfaceWithFormatFrom((void *)data, width, height, depth, pitch, pixel_fmt);
    if (img == NULL) {
        DE_WARN("Cannot process image: %s", path);
        stbi_image_free(data);
    }

    tex = SDL_CreateTextureFromSurface(DE_RendererGetRenderer(), img);

    SDL_FreeSurface(img);
    stbi_image_free(data);

    return tex;
}

bool DestroySprite(void *asset) {
    SDL_Texture *tex = (SDL_Texture *)asset;
    SDL_DestroyTexture(tex);
}
