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