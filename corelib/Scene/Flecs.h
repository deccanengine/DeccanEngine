/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "Scene.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

typedef enum DeccanEcsType {
    DECCAN_ECS_TYPE_PRE_FRAME   = EcsPreFrame,
    DECCAN_ECS_TYPE_POST_LOAD   = EcsPostLoad,
    DECCAN_ECS_TYPE_PRE_UPDATE  = EcsPreUpdate,
    DECCAN_ECS_TYPE_ON_UPDATE   = EcsOnUpdate,
    DECCAN_ECS_TYPE_ON_VALIDATE = EcsOnValidate,
    DECCAN_ECS_TYPE_POST_UPDATE = EcsPostUpdate,
    DECCAN_ECS_TYPE_PRE_STORE   = EcsPreStore,
    DECCAN_ECS_TYPE_ON_STORE    = EcsOnStore,
    DECCAN_ECS_TYPE_POST_FRAME  = EcsPostFrame
} DeccanFlecsType;

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef ecs_iter_t DeccanFlecsIter;
typedef ecs_iter_action_t DeccanFlecsActionFunc;

/////////////////////////////////////////////////
// System
////////////////////////////////////////////////

DE_API void DE_FlecsSystem(DeccanFlecsActionFunc iter, const char *name, const char *sign, DeccanFlecsType type);

/////////////////////////////////////////////////
// Component 
////////////////////////////////////////////////

DE_API void DE_FlecsRegisterComponent(const char *name, size_t size, size_t alignment);
DE_API void DE_FlecsSetComponent(ecs_entity_t entity, const char *name, void *component);
DE_API void *DE_FlecsGetComponent(ecs_entity_t entity, const char *name);
DE_API void DE_FlecsRemoveComponent(ecs_entity_t entity, const char *name);

/////////////////////////////////////////////////
// Tag
////////////////////////////////////////////////

DE_API uint64_t DE_FlecsRegisterTag(const char *name);
DE_API void DE_FlecsSetTag(ecs_entity_t entity, const char *name);
DE_API bool DE_FlecsHasTag(ecs_entity_t entity, const char *name);

/////////////////////////////////////////////////
// Iterator
////////////////////////////////////////////////

DE_API void *DE_FlecsIterColumn(DeccanFlecsIter *it, const char *name, int index);
