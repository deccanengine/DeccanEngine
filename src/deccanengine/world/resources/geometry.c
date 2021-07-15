/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "geometry.h"

DE_IMPL void *geometry_create(const unsigned char *mem, size_t size) {
    DE_UNUSED(size);

    unsigned char *data = (unsigned char *)mem;
    struct geometry_header_t {
        int32_t index_count;
        int32_t vertex_count;
    } header;

    memcpy(&header, data, sizeof(struct geometry_header_t));

    data += sizeof(struct geometry_header_t);

    deccan_geometry_t *geometry = deccan_alloc(sizeof(deccan_geometry_t), 1);
    *geometry = (deccan_geometry_t){
        .index_count = header.index_count,
        .ibuf = sg_make_buffer(&(sg_buffer_desc){
            .type = SG_BUFFERTYPE_INDEXBUFFER,
            .data = (sg_range){
                .size = header.index_count,
                .ptr = data,
            }
        }),
        .vbuf = sg_make_buffer(&(sg_buffer_desc){
            .data = (sg_range){
                .size = header.vertex_count,
                .ptr = data + (sizeof(int16_t) * header.index_count),
            }
        }),
    };

    return geometry;
}

DE_IMPL bool geometry_destroy(void *asset) {
    deccan_geometry_t *geometry = (deccan_geometry_t *)asset;
    deccan_free(geometry);
    return true;
}
