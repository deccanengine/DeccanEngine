/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "ECSystem.h"

typedef struct ECSComp {
    char *key;
    int32_t value;
} ECSComp;

typedef struct ECSystem {
    int32_t *components;
    int32_t  when;
    void (*func)(GameObject *object);
} ECSystem;

static struct {
    ECSComp   *componentTable;
    ECSystem **systemTable;
    int32_t globalCompCount;
} ECS_Info = {
    .componentTable = NULL,
    .systemTable = NULL,
    .globalCompCount = 0
};

/////////////////////////////////////////////////
// ECS Destructor
////////////////////////////////////////////////

void ECSystem_FreeAllComponents() {
    for(int i=0; i<stbds_shlen(ECS_Info.componentTable); i++) {
        ECSComp comp = ECS_Info.componentTable[i];
        
        if(comp.key != NULL) {
            free(comp.key);
            comp.key = NULL;
        }
    }

    stbds_shfree(ECS_Info.componentTable);
}

void ECSystem_FreeAllSystems() {
    for(int i=0; i<stbds_arrlen(ECS_Info.systemTable); i++) {
        ECSystem *sys = ECS_Info.systemTable[i];
        
        if(sys != NULL) {
            stbds_arrfree(sys->components);

            free(sys);
            sys = NULL;       
        }
    }

    stbds_arrfree(ECS_Info.systemTable);
}

/////////////////////////////////////////////////
// Entity Component System
////////////////////////////////////////////////

int32_t ECSystem_RegisterComponent(const char *name) {
    /* Push the component into the global table */
    stbds_shput(ECS_Info.componentTable, DE_NEWSTRING(name), ECS_Info.globalCompCount++);

    /* Return the ID of the component           */
    /* STB_DS will automatically increment it   */
    /* So return the previous index             */
    return ECS_Info.globalCompCount - 1;
}

void ECSystem_RegisterSystem(int count, const char *participants[], int32_t when, void (*func)(GameObject *object)) {
    if(!count) { 
        return;
    }
    
    ECSystem *system = DE_NEW(ECSystem, 1);
    system->components = NULL;
    system->when = when;
    system->func = func;

    for(int i=0; i<count; i++) {
        /* Add each participating component */
        int id = ECSystem_GetComponentID(participants[i]);
        stbds_arrput(system->components, id);
    }

    stbds_arrput(ECS_Info.systemTable, system);
}

int32_t ECSystem_GetComponentID(const char *name) {
    int32_t index = stbds_shgeti(ECS_Info.componentTable, name);
    if(index != -1) {
        return ECS_Info.componentTable[index].value;
    }
    else {
        DE_ERROR("Not a valid registered component: %s", name);
    }
}

void ECSystem_UpdateSystems(GameObject *obj, int32_t when) {
    bool loopStatus = true;
    int systemCount = stbds_arrlen(ECS_Info.systemTable);

    for(int i=0; i<systemCount; i++) {
        if(ECS_Info.systemTable[i]->when == when) {
            int systemComponentCount = stbds_arrlen(ECS_Info.systemTable[i]->components);
            
            for(int j=0; j<systemComponentCount; j++) {
                int32_t component = ECS_Info.systemTable[i]->components[j];    
                if(stbds_hmgeti(obj->components, component) == -1) {
                    loopStatus = false;
                    break;
                }
            }

            if(loopStatus) {
                ECS_Info.systemTable[i]->func(obj);
            }
        }
    }
    
}