/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "camera.h"

void DE_Camera_move(DE_Vector2i pos) {
    DE_Core_get_global_engine()->camera.x += pos.x;
    DE_Core_get_global_engine()->camera.y += pos.y;
}

void DE_Camera_set_position(DE_Vector2i pos) {
    DE_Core_get_global_engine()->camera = pos;
}

void DE_Camera_center_on(DE_GameObject *obj) {
    if(obj == NULL) {
        DE_report("Invalid object used with camera"); return;
    }

    DE_Vector2i mode = DE_Core_get_mode();
    int32_t x = obj->position.x + obj->size.x/2 - mode.x/2; 
    int32_t y = obj->position.y + obj->size.y/2 - mode.y/2;
    DE_Camera_set_position((DE_Vector2i){x, y});
}