/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"

////////////////////////////////////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////////////////////////////////////

typedef enum deccan_camera_type_t { 
    DECCAN_CAMERA_ORTHOGRAPHIC = 0, 
    DECCAN_CAMERA_PERSPECTIVE 
} deccan_camera_type_t;

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct deccan_view_t {
    mat4s view;
    vec3s position;
    float yaw;
    float pitch;
    float roll;
} deccan_view_t;

typedef struct deccan_camera_t {
    deccan_view_t cam;
    deccan_camera_type_t type;
    mat4s proj;
    float near;
    float far;
    float aspect_ratio;
} deccan_camera_t;

////////////////////////////////////////////////////////////////////////////////
// View
////////////////////////////////////////////////////////////////////////////////

void deccan_view_init(deccan_view_t *camera, vec3s position);
void deccan_view_update(deccan_view_t *camera);

////////////////////////////////////////////////////////////////////////////////
// Camera
////////////////////////////////////////////////////////////////////////////////

void deccan_camera_init(deccan_camera_t *camera, float near, float far);
void deccan_camera_set_viewport(deccan_camera_t *camera, vec2s viewport);
void deccan_camera_set_ortho(deccan_camera_t *camera, float size);
void deccan_camera_set_persp(deccan_camera_t *camera, float vfov);
