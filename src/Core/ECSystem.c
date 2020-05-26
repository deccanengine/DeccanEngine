/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Object.h>

typedef struct ECSystemInfo {
    int32_t *components;
    int32_t  count;
} ECSystemInfo;

static struct {
    const char **componentTable;
    int32_t componentTableCount;
    
    ECSystemInfo **systemTable;
    int32_t systemTableCount;
} ECS_Info = {
    .componentTable = NULL,
    .componentTableCount = 0,
    .systemTable = NULL,
    .systemTableCount = 0
};

/////////////////////////////////////////////////
// Entity Component System
////////////////////////////////////////////////

int32_t ValidComponent(int32_t id) {
    if(id >= 0 && id < ECS_Info.componentTableCount) {
        return id;
    }
    else {
        return -1;
    }
}

int32_t ECSystem_RegisterComponent(const char *name) {
    stbds_arrput(ECS_Info.componentTable, name);
    return ECS_Info.componentTableCount++;
}

void ECSystem_RegisterSystem(int count, const char *participants[]) {
    if(!count) { 
        return;
    }
    
    ECSystemInfo *system = DE_NEW(ECSystemInfo, 1);
    system->components = DE_NEW(int32_t, count);
    system->count = count;
    
    /* Check if all components are valid */
    for(int i=0; i<count; i++) {
        int id = ECSystem_GetComponentID(participants[i]);
        if(ValidComponent(id)) {
            system->components[i] = id;
            printf("Component: %s\n", ECSystem_GetComponentName(id));
        }
        else {
            free(system);
            DE_ERROR("Invalid component used in system: %d\n", participants[i]);
        }
    }

    stbds_arrput(ECS_Info.systemTable, system);
    ECS_Info.systemTableCount++;
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

// For debugging only 
int32_t ECSystem_GetSystem(int32_t index) {
    for(int i=0; i < ECS_Info.systemTable[index]->count; i++) {
        printf("system component: %s\n", ECSystem_GetComponentName(ECS_Info.systemTable[index]->components[i]));
    }
}