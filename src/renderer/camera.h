/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */
 
#pragma once
#include "../config.h"
#include "renderer.h"
#include "../core/core.h"
#include "../core/object.h"
#include "../utils/vector.h"

void DE_Camera_move(Deccan_Vector2i pos);
void DE_Camera_set_position(Deccan_Vector2i pos);
void DE_Camera_center_on(Deccan_GameObject *obj);

typedef struct DE_Camera {
    void (*move)(Deccan_Vector2i pos);
    void (*set_position)(Deccan_Vector2i pos);
    void (*center_on)(Deccan_GameObject *obj);
} DE_Camera;

static DE_Camera Deccan_Camera = {
    DE_Camera_move,
    DE_Camera_set_position,
    DE_Camera_center_on
};