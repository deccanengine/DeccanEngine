/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */
 
#pragma once
#include "../config.h"
#include "../core/core.h"
#include "../utils/vector.h"

void _priv_Camera_move(Deccan_Vector2i pos);
void _priv_Camera_set_position(Deccan_Vector2i pos);

typedef struct _priv_Camera {
    void (*move)(Deccan_Vector2i pos);
    void (*set_position)(Deccan_Vector2i pos);
} _priv_Camera;

static _priv_Camera Deccan_Camera = {
    _priv_Camera_move,
    _priv_Camera_set_position
};