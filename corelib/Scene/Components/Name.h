/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../Config.h"
#include "../../Core/Memory.h"
#include "../Flecs.h"

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct Name {
    char *name;
} Name;

/////////////////////////////////////////////////
// Registers/Constructors/Destructors
////////////////////////////////////////////////

void Name_Register();
