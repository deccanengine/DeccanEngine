#pragma once
#include "../Config.h"

typedef struct DeccanTexture {
    int32_t width, height;
    int pixel_format;
    sg_image image;
} DeccanTexture;

typedef struct DeccanSurface {
    const void *data;
    size_t size;
    int format;
} DeccanSurface;

void DE_TextureCreateFromMem(
    DeccanTexture *texture, int32_t width, int32_t height, size_t count, DeccanSurface *surfaces);
void DE_TextureCreateBlankRGBA(DeccanTexture *texture, int32_t width, int32_t height, uint32_t color);
void DE_TextureDestroy(DeccanTexture *texture);
