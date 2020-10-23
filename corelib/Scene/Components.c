/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Components.h"

void DE_Components_RegisterAll() {
    DE_CompColliderRegister();
    DE_CompState2DRegister();
}
