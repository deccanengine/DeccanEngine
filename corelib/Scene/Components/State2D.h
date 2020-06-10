/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../Config.h"
#include "../ECSystem.h"

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct State2D {
    Vector3f position;
    Vector2f scale;
    double   rotation;

    bool is_z_dirty;
} State2D;

/////////////////////////////////////////////////
// Registers/Constructors/Destructors
////////////////////////////////////////////////

void State2D_Register();

State2D *State2D_Init(State2D s);