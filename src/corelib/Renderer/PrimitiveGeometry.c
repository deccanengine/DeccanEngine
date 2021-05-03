/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "PrimitiveGeometry.h"

DE_IMPL deccan_geometry_t deccan_primitive_create_quad() {
    /* clang-format off */
    static const float vertices[] = {
        /*    Position    */ /* Tex coord */
        -0.5f,  0.5f,  0.0f,   0.0f, 0.0f,
         0.5f,  0.5f,  0.0f,   1.0f, 0.0f,
         0.5f, -0.5f,  0.0f,   1.0f, 1.0f,
        -0.5f, -0.5f,  0.0f,   0.0f, 1.0f,
    };

    static const int16_t indices[] = {
        0, 1, 2,
        0, 2, 3,
    };

    static deccan_geometry_t quad;
    if (quad.index_count == 0) {
        quad.index_count = 6;

        quad.vbuf = sg_make_buffer(&(sg_buffer_desc){
            .data = SG_RANGE(vertices),
        });

        quad.ibuf = sg_make_buffer(&(sg_buffer_desc){
            .type = SG_BUFFERTYPE_INDEXBUFFER, 
            .data = SG_RANGE(indices),
        });
    }

    return quad;
    /* clang-format on */
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_geometry_t deccan_primitive_create_triangle() {
    /* clang-format off */
    static const float vertices[] = {
        /*    Position    */ /* Tex coord */
         0.0f,  0.5f,  0.0f,   0.5f, 0.0f,
         0.5f, -0.5f,  0.0f,   1.0f, 1.0f,
        -0.5f, -0.5f,  0.0f,   0.0f, 1.0f,
    };

    static const int16_t indices[] = {
        0, 1, 2,
    };

    static deccan_geometry_t tri;
    if (tri.index_count == 0) {
        tri.index_count = 3;

        tri.vbuf = sg_make_buffer(&(sg_buffer_desc){
            .data = SG_RANGE(vertices),
        });

        tri.ibuf = sg_make_buffer(&(sg_buffer_desc){
            .type = SG_BUFFERTYPE_INDEXBUFFER, 
            .data = SG_RANGE(indices),
        });
    }

    return tri;
    /* clang-format on */
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_geometry_t deccan_primitive_create_cube() {
    /* clang-format off */
    static const float vertices[] = {
        /*    Position    */ /* Tex coord */
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 1.0f,

         0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
    };

    static const int16_t indices[] = {
         0,  1,  2,  0,  2,  3, 
         6,  5,  4,  7,  6,  4, 
         8,  9, 10,  8, 10, 11, 
        14, 13, 12, 15, 14, 12,
        16, 17, 18, 16, 18, 19, 
        22, 21, 20, 23, 22, 20
    };

    static deccan_geometry_t cube;
    if (cube.index_count == 0) {
        cube.index_count = 36;

        cube.vbuf = sg_make_buffer(&(sg_buffer_desc){
            .data = SG_RANGE(vertices),
        });

        cube.ibuf = sg_make_buffer(&(sg_buffer_desc){
            .type = SG_BUFFERTYPE_INDEXBUFFER, 
            .data = SG_RANGE(indices),
        });
    }

    return cube;
    /* clang-format on */
}
