/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Camera.h"

////////////////////////////////////////////////////////////////////////////////
// View
////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_view_init(deccan_view_t *camera, vec3s position) {
    camera->position = position;
    camera->yaw = 0.0f;
    camera->pitch = 0.0f;
    camera->roll = 0.0f;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_view_update(deccan_view_t *camera) {
    mat4s transform = glms_mat4_identity();

    transform = glms_rotate_x(transform, glm_rad(camera->roll));
    transform = glms_rotate_y(transform, glm_rad(camera->pitch));
    transform = glms_rotate_z(transform, glm_rad(camera->yaw));

    transform = glms_translate(transform, camera->position);

    camera->view = glms_mat4_inv(transform);
}

////////////////////////////////////////////////////////////////////////////////
// Camera
////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_camera_init(deccan_camera_t *camera, float near, float far) {
    deccan_view_init(&camera->cam, (vec3s){.x = 0.0f, .y = 0.0f, .z = 1.0f});

    camera->proj = glms_mat4_identity();
    camera->near = near;
    camera->far = far;
    camera->aspect_ratio = (float)(4.0f / 3.0f);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_camera_set_viewport(deccan_camera_t *camera, vec2s viewport) {
    if (viewport.y <= 0)
        return;
    camera->aspect_ratio = (float)(viewport.x / viewport.y);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_camera_set_ortho(deccan_camera_t *camera, float size) {
    camera->proj =
        glms_ortho(-camera->aspect_ratio * size, camera->aspect_ratio * size, -size, size, camera->near, camera->far);

    deccan_view_update(&camera->cam);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_camera_set_persp(deccan_camera_t *camera, float vfov) {
    camera->proj = glms_perspective(glm_rad(vfov), camera->aspect_ratio, camera->near, camera->far);

    deccan_view_update(&camera->cam);
}
