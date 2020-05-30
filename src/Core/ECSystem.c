/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Object.h>

typedef struct ECSystem {
    int32_t *components;
    int32_t  when;
    void (*func)(GameObject *object);
} ECSystem;

static struct {
    const char **componentTable;
    ECSystem **systemTable;
} ECS_Info = {
    .componentTable = NULL,
    .systemTable = NULL
};

/////////////////////////////////////////////////
// Entity Component System
////////////////////////////////////////////////

/* Check if the requested component ID is valid or not */
int32_t ValidComponent(int32_t id) {
    if(id >= 0 && id < stbds_arrlen(ECS_Info.componentTable)) {
        return id;
    }
    else {
        return -1;
    }
}

int32_t ECSystem_RegisterComponent(const char *name) {
    /* Push the component into the global table */
    stbds_arrput(ECS_Info.componentTable, name);

    /* Return the ID of the component           */
    /* STBDS will automatically increment it    */
    /* So return the previous index             */
    return stbds_arrlen(ECS_Info.componentTable) - 1;
}

void ECSystem_RegisterSystem(int count, const char *participants[], int32_t when, void (*func)(GameObject *object)) {
    if(!count) { 
        return;
    }
    
    //int32_t *system = NULL;
    ECSystem *system = DE_NEW(ECSystem, 1);
    system->components = NULL;
    system->when = when;
    system->func = func;

    /* Iterate through */
    for(int i=0; i<count; i++) {
        /* Get component ID from name */
        int id = ECSystem_GetComponentID(participants[i]);
        
        /* Check if all components are valid */
        if(ValidComponent(id)) {
            /* Push the ID into system                          */
            /* Allocation and relloacation is managed by STBDS  */
            stbds_arrput(system->components, id);
        }
        else {
            DE_ERROR("Invalid component used in system: %s\n", participants[i]);
        }
    }

    stbds_arrput(ECS_Info.systemTable, system);
}

int32_t ECSystem_GetComponentID(const char *name) {
    int length = stbds_arrlen(ECS_Info.componentTable);

    for(int i=0; i<length; i++) {
        if(!strcmp(ECS_Info.componentTable[i], name)) {
            /* Name matched */
            return i;
        }
    }

    DE_ERROR("Not a valid registered component: %s", name);
}

const char *ECSystem_GetComponentName(int32_t id) {
    if(ValidComponent(id)) {
        return ECS_Info.componentTable[id];
    }

    DE_ERROR("Not a valid registered component ID: %d", id);
}

// For debugging only, to be removed soon
int32_t ECSystem_GetSystem(int32_t index) {
    int length = stbds_arrlen(ECS_Info.systemTable[index]->components);

    for(int i=0; i<length; i++) {
        printf("system component: %s\n", ECSystem_GetComponentName(ECS_Info.systemTable[index]->components[i]));
    }
}

int32_t ObjectHasComponent(GameObject *obj, int32_t id) {
    for(int i=0; i<obj->component_length; i++) {
        if(obj->components[i]->id == id) {
            return true;
        }
    }
    return false;
}

void ECSystem_UpdateSystems(GameObject *obj, int32_t when) {
    int loopStatus;
    int systemCount = stbds_arrlen(ECS_Info.systemTable);

    for(int i=0; i<systemCount; i++) {
        if(ECS_Info.systemTable[i]->when == when) {
            int systemComponentCount = stbds_arrlen(ECS_Info.systemTable[i]->components);
            
            for(int j=0; j<systemComponentCount; j++) {
                int32_t component = ECS_Info.systemTable[i]->components[j];    
                if(!ObjectHasComponent(obj, component)) {
                    loopStatus = 0;
                    break;
                }
                else {
                    loopStatus = 1;
                }
            }

            if(loopStatus == 1) {
                ECS_Info.systemTable[i]->func(obj);
            }
        }
    }
}