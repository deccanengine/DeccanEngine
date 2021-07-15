/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "systems.h"

////////////////////////////////////////////////////////////////////////////////
// Registrar
////////////////////////////////////////////////////////////////////////////////

void systems_register_all(void) {
    system_init_rendering();
    system_init_physics_body();
    system_init_colliders();
}
