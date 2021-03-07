#pragma once
#include "../Config.h"

typedef struct DeccanView {
    mat4s view;
    vec3s position;
    float yaw;
    float pitch;
    float roll;
} DeccanView;

typedef enum DeccanCameraType { DECCAN_CAMERA_ORTHOGRAPHIC = 0, DECCAN_CAMERA_PERSPECTIVE } DeccanCameraType;

typedef struct DeccanCamera {
    DeccanView cam;
    DeccanCameraType type;
    mat4s proj;
    float near;
    float far;
    float aspect_ratio;
} DeccanCamera;

void DE_ViewInit(DeccanView *camera, vec3s position);
void DE_ViewUpdate(DeccanView *camera);

void DE_CameraInit(DeccanCamera *camera, float near, float far);
void DE_CameraSetViewport(DeccanCamera *camera, vec2s viewport);
void DE_CameraSetOrtho(DeccanCamera *camera, float size);
void DE_CameraSetPersp(DeccanCamera *camera, float vfov);
