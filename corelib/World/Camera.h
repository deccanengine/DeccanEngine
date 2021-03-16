/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

typedef enum DeccanCameraType { DECCAN_CAMERA_ORTHOGRAPHIC = 0, DECCAN_CAMERA_PERSPECTIVE } DeccanCameraType;

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct DeccanView {
    mat4s view;
    vec3s position;
    float yaw;
    float pitch;
    float roll;
} DeccanView;

typedef struct DeccanCamera {
    DeccanView cam;
    DeccanCameraType type;
    mat4s proj;
    float near;
    float far;
    float aspect_ratio;
} DeccanCamera;

/////////////////////////////////////////////////
// View
////////////////////////////////////////////////

void DE_ViewInit(DeccanView *camera, vec3s position);
void DE_ViewUpdate(DeccanView *camera);

/////////////////////////////////////////////////
// Camera
////////////////////////////////////////////////

void DE_CameraInit(DeccanCamera *camera, float near, float far);
void DE_CameraSetViewport(DeccanCamera *camera, vec2s viewport);
void DE_CameraSetOrtho(DeccanCamera *camera, float size);
void DE_CameraSetPersp(DeccanCamera *camera, float vfov);
