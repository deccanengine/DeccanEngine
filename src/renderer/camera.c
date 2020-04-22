/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "camera.h"

void _priv_Camera_move(Deccan_Vector2i pos) {
    Deccan_Core.get_global_engine()->camera.x += pos.x;
    Deccan_Core.get_global_engine()->camera.y += pos.y;
}

void _priv_Camera_set_position(Deccan_Vector2i pos) {
    Deccan_Core.get_global_engine()->camera = pos;
}

void _priv_Camera_center_on(Deccan_GameObject *obj) {
    Deccan_Vector2i mode = Deccan_Core.get_mode();
    int32_t x = obj->position.x + obj->size.x/2 - mode.x/2; 
    int32_t y = obj->position.y + obj->size.y/2 - mode.y/2;
    Deccan_Camera.set_position((Deccan_Vector2i){x, y});
}