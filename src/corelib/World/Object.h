/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "../Core/Utils.h"

////////////////////////////////////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct DeccanGameObject DeccanGameObject;

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
} DeccanObjectInfo;

typedef struct DeccanGameObject {
    ecs_entity_t entity;
} DeccanGameObject;

////////////////////////////////////////////////////////////////////////////////
// Initialization and instantiator functions
////////////////////////////////////////////////////////////////////////////////

DE_API DeccanGameObject DE_ObjectNewObject(const char *name);
DE_API void DE_ObjectDeleteObject(DeccanGameObject obj);
DE_API void DE_ObjectFreeObject(DeccanGameObject obj);
DE_API bool DE_ObjectIsValid(DeccanGameObject obj);

////////////////////////////////////////////////////////////////////////////////
// Prefab and hierarchy functions
////////////////////////////////////////////////////////////////////////////////

DE_API DeccanGameObject DE_ObjectMakeCopy(DeccanGameObject object);
DE_API void DE_ObjectMakePrefab(DeccanGameObject object);
DE_API void DE_ObjectSetParent(DeccanGameObject object, DeccanGameObject parent);
DE_API void DE_ObjectAddChild(DeccanGameObject object, DeccanGameObject child);

////////////////////////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////////////////////////

DE_API void DE_ObjectUpdate(DeccanGameObject obj);
DE_API void DE_ObjectRender(DeccanGameObject obj);
DE_API void DE_ObjectEnd(DeccanGameObject obj);

////////////////////////////////////////////////////////////////////////////////
// Messaging
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Component
////////////////////////////////////////////////////////////////////////////////

DE_API void DE_ObjectSetComponent(DeccanGameObject obj, const char *name, void *component);
DE_API void *DE_ObjectGetComponent(DeccanGameObject obj, const char *name);
DE_API void DE_ObjectRemoveComponent(DeccanGameObject obj, const char *name);

DE_API void DE_ObjectSetName(DeccanGameObject obj, const char *name);
DE_API const char *DE_ObjectGetName(DeccanGameObject obj);

DE_API void DE_ObjectSetTag(DeccanGameObject obj, const char *name);
DE_API bool DE_ObjectHasTag(DeccanGameObject obj, const char *name);

////////////////////////////////////////////////////////////////////////////////
// Getters and Setters
////////////////////////////////////////////////////////////////////////////////
DE_API bool DE_ObjectIsHidden(DeccanGameObject obj);
DE_API void DE_ObjectHide(DeccanGameObject obj, bool hide);

DE_API bool DE_ObjectIsActive(DeccanGameObject obj);
DE_API void DE_ObjectActivate(DeccanGameObject obj, bool act);
