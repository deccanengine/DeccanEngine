/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "Scene.h"

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

void DE_Flecs_RegisterComponent(const char *name, size_t size, size_t alignment);
DeccanComponent DE_Flecs_LookupComponent(const char *name);

uint64_t DE_Flecs_RegisterTag(const char *name);
void DE_Flecs_SetTag(ecs_entity_t entity, const char *name);
bool DE_Flecs_HasTag(ecs_entity_t entity, const char *name);
