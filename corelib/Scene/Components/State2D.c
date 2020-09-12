/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "State2D.h"
#include "../Scene.h"

/////////////////////////////////////////////////
// Registers/Constructors/Destructors
////////////////////////////////////////////////

void State2D_Register() {
    GameScene *scene = Scene_CurrentScene();
    ecs_entity_t FLECS__EState2D = ecs_new_component(scene->world, 0, "State2D", sizeof(State2D), ECS_ALIGNOF(State2D));
}
