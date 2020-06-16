/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "Object.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

typedef enum {
    SYSTEM_AT_BEGINING,
    SYSTEM_AT_STEP,
    SYSTEM_AT_RENDER,
    SYSTEM_AT_END
} SYSTEM_WHEN;

/////////////////////////////////////////////////
// ECS Destructor
////////////////////////////////////////////////

void ECSystem_FreeAllComponents();
void ECSystem_FreeAllSystems();

/////////////////////////////////////////////////
// Entity Component System
////////////////////////////////////////////////

int32_t ECSystem_RegisterComponent(const char *name);
void ECSystem_RegisterSystem(int count, const char *participants[], int32_t when, void (*func)(GameObject *object)); 

int32_t ECSystem_GetComponentID(const char *name);
const char *ECSystem_GetComponentName(int32_t id);

int32_t ECSystem_GetSystem(int32_t index);

void ECSystem_UpdateSystems(GameObject *obj, int32_t when);