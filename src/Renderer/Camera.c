/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Renderer.h>
#include <Deccan/Core.h>
#include <Deccan/Object.h>

void _clamp(Vector2f *pos, PosRect *rect, float *final_x, float *final_y) {
    /* Bounds are not set */
    if(rect->x1 == -1) { 
        *final_x = pos->x;
        *final_y = pos->y;
        return; 
    }

    /* Clamp the abscissa */
    if(pos->x < rect->x1) { *final_x = rect->x1; }
    else if(pos->x > rect->x2) { *final_x = rect->x2; }
    else { *final_y = pos->x; }

    /* Clamp the ordinate */
    if(pos->y < rect->y1) { *final_y = rect->y1; }
    else if(pos->y > rect->y2) { *final_y = rect->y2; }
    else { *final_y = pos->y; }
}

void Camera_Move(Vector2f pos) {
    GameInfo *engine = Core_GetGlobalInfo();

    float x, y; 
    _clamp(&pos, &engine->camera_bounds, &x, &y);

    engine->camera.x += x;
    engine->camera.y += y;
}

void Camera_CenterOn(GameObject *obj) {
    if(obj == NULL) {
        DE_report("Invalid object used with camera"); return;
    }

    Vector2i mode = Core_GetMode();
    Vector2f pixel = Renderer_GetPixelSize();

    float x = (obj->position.x) + (obj->size.x)/2 - (mode.x/pixel.x)/2; 
    float y = (obj->position.y) + (obj->size.y)/2 - (mode.y/pixel.y)/2;

    Vector2f pos = {x, y};
    _clamp(&pos, &Core_GetGlobalInfo()->camera_bounds, &x, &y);
    Camera_SetPosition((Vector2f){x, y});
}

void Camera_SetPosition(Vector2f pos) {
    Core_GetGlobalInfo()->camera = pos;
}

void Camera_SetBounds(PosRect rect) {
    Core_GetGlobalInfo()->camera_bounds = rect;
}

Vector2f Camera_GetPosition() {
    return Core_GetGlobalInfo()->camera;
}

PosRect Camera_GetBounds() {
    return Core_GetGlobalInfo()->camera_bounds;
}