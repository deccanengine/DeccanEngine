/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Collider.h"

void Collider_Register() {
    ECSystem_RegisterComponent("Collider");
}

Collider *Collider_Init(Collider c) {
    Collider *collider = DE_NEW(Collider, 1);
    *collider = c;
    
    return collider;
}