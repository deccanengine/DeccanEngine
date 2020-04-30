/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "camera.h"

void DE_clamp_vec_rect(DE_Vector2i *pos, DE_PosRect *rect, int32_t *final_x, int32_t *final_y) {
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

void DE_Camera_move(DE_Vector2i pos) {
    DE_Info *engine = DE_Core_get_global_engine();

    int32_t x, y;
    DE_clamp_vec_rect(&pos, &engine->camera_bounds, &x, &y);

    engine->camera.x += x;
    engine->camera.y += y;
}

void DE_Camera_center_on(DE_GameObject *obj) {
    if(obj == NULL) {
        DE_report("Invalid object used with camera"); return;
    }

    DE_Vector2i mode = DE_Core_get_mode();
    DE_Vector2f pixel = DE_Renderer_get_pixel_size();

    int32_t x = (obj->position.x) + (obj->size.x)/2 - (mode.x/pixel.x)/2; 
    int32_t y = (obj->position.y) + (obj->size.y)/2 - (mode.y/pixel.y)/2;

    DE_Vector2i pos = {x, y};
    DE_clamp_vec_rect(&pos, &DE_Core_get_global_engine()->camera_bounds, &x, &y);
    DE_Camera_set_position((DE_Vector2i){x, y});
}

void DE_Camera_set_position(DE_Vector2i pos) {
    DE_Core_get_global_engine()->camera = pos;
}

void DE_Camera_set_bounds(DE_PosRect rect) {
    DE_Core_get_global_engine()->camera_bounds = rect;
}

DE_Vector2i DE_Camera_get_position() {
    return DE_Core_get_global_engine()->camera;
}

DE_PosRect DE_Camera_get_bounds() {
    return DE_Core_get_global_engine()->camera_bounds;
}