/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../Config.h"
#include "../Object.h"
#include "../ECSystem.h"

typedef struct State2D {
    Vector3f position;
    Vector2f scale;
    double   rotation;

    bool is_z_dirty;
} State2D;

void State2D_Register();

State2D *State2D_Init();