/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "../Core/Variable.h"
#include "../Core/Memory.h"

#ifndef DECCAN_OBJ_MSG_LENGTH
    #define DECCAN_OBJ_MSG_LENGTH 50
#endif

#ifndef DECCAN_OBJ_MSG_COUNT
    #define DECCAN_OBJ_MSG_COUNT 100
#endif

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct Component {
    int32_t  key;
    void    *value;
} ObjectComponent;

typedef struct GameObject GameObject;
typedef struct GameObject {
    int32_t layer;   // To do

    // To do: use these
    bool active;
    bool visible;

    // Temporary
    struct { int32_t z; } order;

    // To do: mark and remove system
    bool toRemove;

    ecs_entity_t entity;

    DeccanVarManager vars;

    bool is_beginning;
    void (*AtFirstFrame)(GameObject *object);
    void (*AtBeginning)(GameObject *object);
    void (*AtStep)(GameObject *object);
    void (*AtRender)(GameObject *object);
    void (*AtEnd)(GameObject *object);
} GameObject;

static inline void NULL_OBJFUNC(GameObject *obj) { DE_UNUSED(obj); }

/////////////////////////////////////////////////
// Initialization and instantiator functions
////////////////////////////////////////////////

GameObject *Object_NewObject(const char *name);
void Object_DeleteObject(GameObject *obj);
void Object_FreeObject(GameObject *obj);

/////////////////////////////////////////////////
// Update
////////////////////////////////////////////////

void Object_Update(GameObject *obj);
void Object_Render(GameObject *obj);
void Object_End(GameObject *obj);

/////////////////////////////////////////////////
// Messaging
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Component
////////////////////////////////////////////////

void Object_SetComponent(GameObject *obj, const char *name, void *component);
void *Object_GetComponent(GameObject *obj, const char *name);

void Object_SetTag(GameObject *obj, const char *name);
bool Object_HasTag(GameObject *obj, const char *name);

/////////////////////////////////////////////////
// Getters and Setters
////////////////////////////////////////////////

bool Object_IsHidden(GameObject *obj);
void Object_Hide(GameObject *obj, bool hide);

bool Object_IsActive(GameObject *obj);
void Object_Activate(GameObject *obj, bool act);
