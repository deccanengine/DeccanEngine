/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Object.h>

static struct {
    const char **componentTable;
    int32_t **systemTable;
} ECS_Info = {
    .componentTable = NULL,
    .systemTable = NULL,
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

void ECSystem_RegisterSystem(int count, const char *participants[]) {
    if(!count) { 
        return;
    }
    
    int32_t *system = NULL;

    /* Iterate through */
    for(int i=0; i<count; i++) {
        /* Get component ID from name */
        int id = ECSystem_GetComponentID(participants[i]);
        
        /* Check if all components are valid */
        if(ValidComponent(id)) {
            /* Push the ID into system                          */
            /* Allocation and relloacation is managed by STBDS  */
            stbds_arrput(system, id);
        }
        else {
            DE_ERROR("Invalid component used in system: %d\n", participants[i]);
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
    int length = stbds_arrlen(ECS_Info.systemTable[index]);

    for(int i=0; i<length; i++) {
        printf("system component: %s\n", ECSystem_GetComponentName(ECS_Info.systemTable[index][i]));
    }
}