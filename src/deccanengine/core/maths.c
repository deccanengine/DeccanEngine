/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <deccanengine/core/maths.h>

////////////////////////////////////////////////////////////////////////////////
// Matrix 4x4
////////////////////////////////////////////////////////////////////////////////

DE_IMPL mat4s deccan_mat4_compose(vec3s position, vec3s scale, vec3s rotation) {
    mat4s transmat = glms_mat4_identity();
    transmat = glms_translate(transmat, position);
    transmat = glms_rotate_x(transmat, rotation.x);
    transmat = glms_rotate_y(transmat, rotation.y);
    transmat = glms_rotate_z(transmat, rotation.z);
    transmat = glms_scale(transmat, scale);
    return transmat;
}
