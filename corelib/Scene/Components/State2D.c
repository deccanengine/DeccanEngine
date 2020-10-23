/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "State2D.h"

/////////////////////////////////////////////////
// Registers/Constructors/Destructors
////////////////////////////////////////////////

void DE_CompState2DRegister() {
    DE_Flecs_RegisterComponent("State2D", sizeof(DeccanCompState2D), ECS_ALIGNOF(DeccanCompState2D));
}
