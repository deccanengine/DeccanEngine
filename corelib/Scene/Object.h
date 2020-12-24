/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "../Core/Variable.h"
#include "../Core/Utils.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct DeccanGameObject DeccanGameObject ;

typedef struct DeccanObjectInfo {
	bool visible;
	bool active;
	bool to_remove;

	bool is_beginning;

    void (*AtFirstFrame)(DeccanGameObject object);
    void (*AtBeginning)(DeccanGameObject object);
    void (*AtStep)(DeccanGameObject object);
    void (*AtRender)(DeccanGameObject object);
    void (*AtEnd)(DeccanGameObject object);

	DeccanVarManager vars;
} DeccanObjectInfo;

typedef struct DeccanGameObject {
    ecs_entity_t entity;
} DeccanGameObject ;

static inline void NULL_OBJFUNC(DeccanGameObject obj) { DE_UNUSED(obj); }

/////////////////////////////////////////////////
// Initialization and instantiator functions
////////////////////////////////////////////////

DeccanGameObject DE_ObjectNewObject(const char *name);
void DE_ObjectDeleteObject(DeccanGameObject obj);
void DE_ObjectFreeObject(DeccanGameObject obj);
bool DE_ObjectIsValid(DeccanGameObject obj);

/////////////////////////////////////////////////
// Prefab and hierarchy functions
////////////////////////////////////////////////

DeccanGameObject DE_ObjectMakeCopy(DeccanGameObject object);
void DE_ObjectMakePrefab(DeccanGameObject object);
void DE_ObjectSetParent(DeccanGameObject object, DeccanGameObject parent);
void DE_ObjectAddChild(DeccanGameObject object, DeccanGameObject child);

/////////////////////////////////////////////////
// Update
////////////////////////////////////////////////

void DE_ObjectUpdate(DeccanGameObject obj);
void DE_ObjectRender(DeccanGameObject obj);
void DE_ObjectEnd(DeccanGameObject obj);

/////////////////////////////////////////////////
// Messaging
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Component
////////////////////////////////////////////////

void DE_ObjectSetComponent(DeccanGameObject obj, const char *name, void *component);
void *DE_ObjectGetComponent(DeccanGameObject obj, const char *name);
void DE_ObjectRemoveComponent(DeccanGameObject obj, const char *name);

void DE_ObjectSetName(DeccanGameObject obj, const char *name);
const char *DE_ObjectGetName(DeccanGameObject obj);

void DE_ObjectSetTag(DeccanGameObject obj, const char *name);
bool DE_ObjectHasTag(DeccanGameObject obj, const char *name);

/////////////////////////////////////////////////
// Getters and Setters
////////////////////////////////////////////////
bool DE_ObjectIsHidden(DeccanGameObject obj);
void DE_ObjectHide(DeccanGameObject obj, bool hide);

bool DE_ObjectIsActive(DeccanGameObject obj);
void DE_ObjectActivate(DeccanGameObject obj, bool act);
