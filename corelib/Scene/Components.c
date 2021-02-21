/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Components.h"

DE_IMPL void DE_ComponentsRegisterAll(void) {
    DE_CompColliderRegister();
    DE_CompState2DRegister();
}
