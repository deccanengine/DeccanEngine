/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "scene.h"

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef ecs_entity_t deccan_flecs_type_t;
typedef ecs_iter_t deccan_flecs_iter_t;
typedef ecs_iter_action_t deccan_flecs_action_func_t;

////////////////////////////////////////////////////////////////////////////////
// Registrars
////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_flecs_register_system(deccan_flecs_action_func_t iter, const char *name, const char *sign, deccan_flecs_type_t type);
DE_API void deccan_flecs_register_component(const char *name, size_t size, size_t alignment);
DE_API uint64_t deccan_flecs_register_tag(const char *name);

////////////////////////////////////////////////////////////////////////////////
// Iterator
////////////////////////////////////////////////////////////////////////////////

DE_API void *deccan_flecs_iter_column(deccan_flecs_iter_t *it, const char *name, int index);
