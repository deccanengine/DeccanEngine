#pragma once
#include "../Config.h"

typedef struct DeccanGeometry {
    sg_buffer vbuf, ibuf;
    sg_image image;
    mat4s transform;
    float color[4];
    uint16_t index_count;
} DeccanGeometry;
