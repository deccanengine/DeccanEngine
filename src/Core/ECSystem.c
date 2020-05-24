/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Object.h>

static struct {
    const char **componentTable;
    int32_t componentTableCount;
} ECS_Info = {
    .componentTable = NULL,
    .componentTableCount = 0
};

/////////////////////////////////////////////////
// Entity Component System
////////////////////////////////////////////////

int32_t ECSystem_RegisterComponent(const char *name) {
    stbds_arrput(ECS_Info.componentTable, name);
    return ECS_Info.componentTableCount++;
}

int32_t ECSystem_GetComponentID(const char *name) {
    for(int i=0; i<ECS_Info.componentTableCount; i++) {
        if(!strcmp(ECS_Info.componentTable[i], name)) {
            return i;
        }
    }

    DE_ERROR("Not a valid registered component: %s", name);
}

const char *ECSystem_GetComponentName(int32_t id) {
    if(id >= 0 && id < ECS_Info.componentTableCount) {
        return ECS_Info.componentTable[id];
    }

    DE_ERROR("Not a valid registered component ID: %d", id);
}