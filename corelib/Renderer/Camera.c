/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Camera.h"

static struct {
    vec2 position;
    vec4  bounds;
} Camera_Info = {
    .position = {0,  0},
    .bounds   = {-1, -1, -1, -1}
};

/////////////////////////////////////////////////
// Camera
////////////////////////////////////////////////

void Clamp(vec2 pos, vec4 rect, float *final_x, float *final_y) {
    /* Bounds are not set */
    if(rect[0] == -1) {
        *final_x = pos[0];
        *final_y = pos[1];
        return;
    }

    /* Clamp the abscissa */
    if(pos[0] < rect[0]) { *final_x = rect[0]; }
    else if(pos[0] > rect[0] + rect[2]) { *final_x = rect[0] + rect[2]; }
    else { *final_y = pos[0]; }

    /* Clamp the ordinate */
    if(pos[1] < rect[1]) { *final_y = rect[1]; }
    else if(pos[1] > rect[1] + rect[3]) { *final_y = rect[1] + rect[3]; }
    else { *final_y = pos[1]; }
}

void DE_CameraMove(vec2 pos) {
    float x, y;
    Clamp(pos, Camera_Info.bounds, &x, &y);

    Camera_Info.position[0] += x;
    Camera_Info.position[1] += y;
}

/* New function needed */
/*
void Camera_CenterOn(GameObject *obj) {
    if(obj == NULL) {
        DE_REPORT("Invalid object used with camera"); return;
    }

    vec2i mode = Core_GetMode();
    vec2f pixel = Renderer_GetPixelSize();

    float x = (obj->position.x) + (obj->size.x)/2 - (mode.x/pixel.x)/2;
    float y = (obj->position.y) + (obj->size.y)/2 - (mode.y/pixel.y)/2;

    vec2f pos = {x, y};
    _clamp(&pos, &Camera_Info.bounds, &x, &y);
    Camera_SetPosition((vec2f){x, y});
}
*/

void DE_CameraSetPosition(vec2 pos) {
    glm_vec2_copy(pos, Camera_Info.position);
}

void DE_CameraSetBounds(vec4 rect) {
    glm_vec2_copy(rect, Camera_Info.bounds);
}

void DE_CameraGetPosition(vec2 pos) {
    glm_vec2_copy(Camera_Info.position, pos);
}

void DE_CameraGetBounds(vec4 bounds) {
    glm_vec4_copy(Camera_Info.bounds, bounds);
}
