#pragma once
#include "../Config.h"
#include "Object.h"

/////////////////////////////////////////////////
// Entity Component System
////////////////////////////////////////////////

int32_t ECSystem_RegisterComponent(const char *name);
void ECSystem_RegisterSystem(int count, const char *participants[], int32_t when, void (*func)(GameObject *object)); 

int32_t ECSystem_GetComponentID(const char *name);
const char *ECSystem_GetComponentName(int32_t id);

int32_t ECSystem_GetSystem(int32_t index);

void ECSystem_UpdateSystems(GameObject *obj, int32_t when);