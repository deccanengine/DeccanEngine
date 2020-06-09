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

void State2D_Register() {
    ECSystem_RegisterComponent("State2D");
}

State2D *State2D_Init(State2D s) {
    State2D *state = DE_NEW(State2D, 1);
    *state = s;
    
    return state;
}