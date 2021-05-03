/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "Scene.h"

////////////////////////////////////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////////////////////////////////////

typedef enum deccan_ecs_type_t {
    DECCAN_ECS_TYPE_PRE_FRAME = EcsPreFrame,
    DECCAN_ECS_TYPE_POST_LOAD = EcsPostLoad,
    DECCAN_ECS_TYPE_PRE_UPDATE = EcsPreUpdate,
    DECCAN_ECS_TYPE_ON_UPDATE = EcsOnUpdate,
    DECCAN_ECS_TYPE_ON_VALIDATE = EcsOnValidate,
    DECCAN_ECS_TYPE_POST_UPDATE = EcsPostUpdate,
    DECCAN_ECS_TYPE_PRE_STORE = EcsPreStore,
    DECCAN_ECS_TYPE_ON_STORE = EcsOnStore,
    DECCAN_ECS_TYPE_POST_FRAME = EcsPostFrame
} deccan_flecs_type_t;

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef ecs_iter_t deccan_flecs_iter_t;
typedef ecs_iter_action_t deccan_flecs_action_func_t;

////////////////////////////////////////////////////////////////////////////////
// System
////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_flecs_system(deccan_flecs_action_func_t iter, const char *name, const char *sign, deccan_flecs_type_t type);
DE_API void deccan_flecs_update_world(void);

////////////////////////////////////////////////////////////////////////////////
// Component
////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_flecs_register_component(const char *name, size_t size, size_t alignment);
DE_API void deccan_flecs_set_component(ecs_entity_t entity, const char *name, void *component);
DE_API void *deccan_flecs_get_component(ecs_entity_t entity, const char *name);
DE_API void deccan_flecs_remove_component(ecs_entity_t entity, const char *name);

////////////////////////////////////////////////////////////////////////////////
// Tag
////////////////////////////////////////////////////////////////////////////////

DE_API uint64_t deccan_flecs_register_tag(const char *name);
DE_API void deccan_flecs_set_tag(ecs_entity_t entity, const char *name);
DE_API bool deccan_flecs_has_tag(ecs_entity_t entity, const char *name);

////////////////////////////////////////////////////////////////////////////////
// Iterator
////////////////////////////////////////////////////////////////////////////////

DE_API void *deccan_flecs_iter_column(deccan_flecs_iter_t *it, const char *name, int index);
