/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Drawable.h"
#include "../Flecs.h"

/////////////////////////////////////////////////
// Registers/Constructors/Destructors
////////////////////////////////////////////////

void DE_CompDrawableRegister(void) {
    DE_FlecsRegisterComponent("Drawable", sizeof(DeccanCompDrawable), ECS_ALIGNOF(DeccanCompDrawable));
}
