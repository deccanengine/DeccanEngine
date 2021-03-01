#include "PrimitiveGeometry.h"

DeccanGeometry DE_PrimitiveCreateQuad() {
    static const float vertices[] = {
         /*   Position   */   /* Tex coord */
        -0.5f,  0.5f,  0.0f,   0.0f, 0.0f,
         0.5f,  0.5f,  0.0f,   1.0f, 0.0f,
         0.5f, -0.5f,  0.0f,   1.0f, 1.0f,
        -0.5f, -0.5f,  0.0f,   0.0f, 1.0f,
    };

    static const int16_t indices[] = {
        0, 1, 2,
        0, 2, 3,
    };

    DeccanGeometry quad;
    quad.index_count = 6;

    quad.vbuf = sg_make_buffer(&(sg_buffer_desc) {
        .size = sizeof(vertices),
        .content = vertices,
    });

    quad.ibuf = sg_make_buffer(&(sg_buffer_desc) {
        .type = SG_BUFFERTYPE_INDEXBUFFER,
        .size = sizeof(indices),
        .content = indices
    });

    return quad;
}

DeccanGeometry DE_PrimitiveCreateTriangle() {
    static const float vertices[] = {
         /*   Position   */   /* Tex coord */
         0.0f,  0.5f,  0.0f,   0.5f, 0.0f,
         0.5f, -0.5f,  0.0f,   1.0f, 1.0f,
        -0.5f, -0.5f,  0.0f,   0.0f, 1.0f, 
    };

    static const int16_t indices[] = {
        0, 1, 2,
    };

    DeccanGeometry tri;
    tri.index_count = 3;

    tri.vbuf = sg_make_buffer(&(sg_buffer_desc) {
        .size = sizeof(vertices),
        .content = vertices,
    });

    tri.ibuf = sg_make_buffer(&(sg_buffer_desc) {
        .type = SG_BUFFERTYPE_INDEXBUFFER,
        .size = sizeof(indices),
        .content = indices
    });

    return tri;
}

DeccanGeometry DE_PrimitiveCreateCube() {
    static const float vertices[] = { 
         /*   Position   */   /* Tex coord */
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
         0,  1,  2,   0,  2,  3,
         6,  5,  4,   7,  6,  4,
         8,  9, 10,   8, 10, 11,
        14, 13, 12,  15, 14, 12,
        16, 17, 18,  16, 18, 19,
        22, 21, 20,  23, 22, 20
    };

    DeccanGeometry cube;
    cube.index_count = 36;

    cube.vbuf = sg_make_buffer(&(sg_buffer_desc) {
        .size = sizeof(vertices),
        .content = vertices,
    });

    cube.ibuf = sg_make_buffer(&(sg_buffer_desc) {
        .type = SG_BUFFERTYPE_INDEXBUFFER,
        .size = sizeof(indices),
        .content = indices
    });

    return cube;

}
