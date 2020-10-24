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

typedef struct DeccanGameObject DeccanGameObject;
typedef struct DeccanGameObject {
    bool visible;
    bool active;
    bool toRemove;

    ecs_entity_t entity;
    DeccanVarManager vars;

    bool is_beginning;
    void (*AtFirstFrame)(DeccanGameObject *object);
    void (*AtBeginning)(DeccanGameObject *object);
    void (*AtStep)(DeccanGameObject *object);
    void (*AtRender)(DeccanGameObject *object);
    void (*AtEnd)(DeccanGameObject *object);
} DeccanGameObject;

static inline void NULL_OBJFUNC(DeccanGameObject *obj) { DE_UNUSED(obj); }

/////////////////////////////////////////////////
// Initialization and instantiator functions
////////////////////////////////////////////////

DeccanGameObject *DE_ObjectNewObject(const char *name);
DeccanGameObject *DE_ObjectMakeCopy(DeccanGameObject *object);
void DE_ObjectDeleteObject(DeccanGameObject *obj);
void DE_ObjectFreeObject(DeccanGameObject *obj);

/////////////////////////////////////////////////
// Update
////////////////////////////////////////////////

void DE_ObjectUpdate(DeccanGameObject *obj);
void DE_ObjectRender(DeccanGameObject *obj);
void DE_ObjectEnd(DeccanGameObject *obj);

/////////////////////////////////////////////////
// Messaging
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Component
////////////////////////////////////////////////

void DE_ObjectSetComponent(DeccanGameObject *obj, const char *name, void *component);
void *DE_ObjectGetComponent(DeccanGameObject *obj, const char *name);

void DE_ObjectSetName(DeccanGameObject *obj, const char *name);
const char *DE_ObjectGetName(DeccanGameObject *obj);

void DE_ObjectSetTag(DeccanGameObject *obj, const char *name);
bool DE_ObjectHasTag(DeccanGameObject *obj, const char *name);

/////////////////////////////////////////////////
// Getters and Setters
////////////////////////////////////////////////

bool DE_ObjectIsHidden(DeccanGameObject *obj);
void DE_ObjectHide(DeccanGameObject *obj, bool hide);

bool DE_ObjectIsActive(DeccanGameObject *obj);
void DE_ObjectActivate(DeccanGameObject *obj, bool act);
