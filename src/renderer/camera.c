/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "camera.h"

void _clamp(DE_Vector2f *pos, DE_PosRect *rect, float *final_x, float *final_y) {
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

void DE_Camera_Move(DE_Vector2f pos) {
    DE_GameInfo *engine = DE_Core_GetGlobalInfo();

    float x, y; 
    _clamp(&pos, &engine->camera_bounds, &x, &y);

    engine->camera.x += x;
    engine->camera.y += y;
}

void DE_Camera_CenterOn(DE_GameObject *obj) {
    if(obj == NULL) {
        DE_report("Invalid object used with camera"); return;
    }

    DE_Vector2i mode = DE_Core_GetMode();
    DE_Vector2f pixel = DE_Renderer_GetPixelSize();

    float x = (obj->position.x) + (obj->size.x)/2 - (mode.x/pixel.x)/2; 
    float y = (obj->position.y) + (obj->size.y)/2 - (mode.y/pixel.y)/2;

    DE_Vector2f pos = {x, y};
    _clamp(&pos, &DE_Core_GetGlobalInfo()->camera_bounds, &x, &y);
    DE_Camera_SetPosition((DE_Vector2f){x, y});
}

void DE_Camera_SetPosition(DE_Vector2f pos) {
    DE_Core_GetGlobalInfo()->camera = pos;
}

void DE_Camera_SetBounds(DE_PosRect rect) {
    DE_Core_GetGlobalInfo()->camera_bounds = rect;
}

DE_Vector2f DE_Camera_GetPosition() {
    return DE_Core_GetGlobalInfo()->camera;
}

DE_PosRect DE_Camera_GetBounds() {
    return DE_Core_GetGlobalInfo()->camera_bounds;
}