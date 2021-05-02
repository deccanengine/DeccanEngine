/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Components.h"

////////////////////////////////////////////////////////////////////////////////
// Registrar
////////////////////////////////////////////////////////////////////////////////

DE_IMPL void DE_ComponentsRegisterAll(void) {
    DE_FlecsRegisterComponent("Transform", sizeof(DeccanCompTransform), ECS_ALIGNOF(DeccanCompTransform));

    DE_FlecsRegisterComponent("Collider", sizeof(DeccanCompCollider), ECS_ALIGNOF(DeccanCompCollider));

    DE_FlecsRegisterComponent("DrawableGeometry", sizeof(DeccanCompDrawableGeometry), 
        ECS_ALIGNOF(DeccanCompDrawableGeometry));

    DE_FlecsRegisterComponent("DrawableSprite", sizeof(DeccanCompDrawableSprite), 
        ECS_ALIGNOF(DeccanCompDrawableSprite));
}
