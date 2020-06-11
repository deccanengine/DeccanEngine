/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Camera.h"

static struct {
    Vector2 position;
    Rect  bounds;
} Camera_Info = {
    .position = (Vector2){0,  0},
    .bounds   = (Rect){-1, -1, -1, -1}
};

/////////////////////////////////////////////////
// Camera
////////////////////////////////////////////////

void Clamp(Vector2 *pos, Rect *rect, float *final_x, float *final_y) {
    /* Bounds are not set */
    if(rect->x == -1) { 
        *final_x = pos->x;
        *final_y = pos->y;
        return; 
    }

    /* Clamp the abscissa */
    if(pos->x < rect->x) { *final_x = rect->x; }
    else if(pos->x > rect->x + rect->w) { *final_x = rect->x + rect->w; }
    else { *final_y = pos->x; }

    /* Clamp the ordinate */
    if(pos->y < rect->y) { *final_y = rect->y; }
    else if(pos->y > rect->y + rect->h) { *final_y = rect->y + rect->h; }
    else { *final_y = pos->y; }
}

void Camera_Move(Vector2 pos) {
    float x, y; 
    Clamp(&pos, &Camera_Info.bounds, &x, &y);

    Camera_Info.position.x += x;
    Camera_Info.position.y += y;
}

/* New function needed */
/*
void Camera_CenterOn(GameObject *obj) {
    if(obj == NULL) {
        DE_REPORT("Invalid object used with camera"); return;
    }

    Vector2i mode = Core_GetMode();
    Vector2f pixel = Renderer_GetPixelSize();

    float x = (obj->position.x) + (obj->size.x)/2 - (mode.x/pixel.x)/2; 
    float y = (obj->position.y) + (obj->size.y)/2 - (mode.y/pixel.y)/2;

    Vector2f pos = {x, y};
    _clamp(&pos, &Camera_Info.bounds, &x, &y);
    Camera_SetPosition((Vector2f){x, y});
}
*/

void Camera_SetPosition(Vector2 pos) {
    Camera_Info.position = pos;
}

void Camera_SetBounds(Rect rect) {
    Camera_Info.bounds = rect;
}

Vector2 Camera_GetPosition() {
    return Camera_Info.position;
}

Rect Camera_GetBounds() {
    return Camera_Info.bounds;
}