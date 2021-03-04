/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Transform.h"

/////////////////////////////////////////////////
// Registers/Constructors/Destructors
////////////////////////////////////////////////

DE_IMPL void DE_CompTransformRegister(void) {
    DE_FlecsRegisterComponent("Transform", sizeof(DeccanCompTransform), ECS_ALIGNOF(DeccanCompTransform));
}
