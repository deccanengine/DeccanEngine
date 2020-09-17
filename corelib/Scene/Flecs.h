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

typedef ecs_iter_t DeccanSysIter;
typedef ecs_iter_action_t DeccanSysFunc;

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
} DeccanEcsType;

void DE_Flecs_RegisterComponent(const char *name, size_t size, size_t alignment);
DeccanComponent DE_Flecs_LookupComponent(const char *name);

void DE_Flecs_System(DeccanSysFunc iter, const char *name, const char *sign, DeccanEcsType type);

uint64_t DE_Flecs_RegisterTag(const char *name);
void DE_Flecs_SetTag(ecs_entity_t entity, const char *name);
bool DE_Flecs_HasTag(ecs_entity_t entity, const char *name);

void *DE_Flecs_IterColumn(DeccanSysIter *it, const char *name, int index);
