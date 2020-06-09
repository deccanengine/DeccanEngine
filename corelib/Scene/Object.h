/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "../Message.h"
#include "../Renderer/Renderer.h"
#include "../Behaviour/Physics/Physics.h"

#ifndef DECCAN_OBJ_MSG_LENGTH
    #define DECCAN_OBJ_MSG_LENGTH 50
#endif

#ifndef DECCAN_OBJ_MSG_COUNT
    #define DECCAN_OBJ_MSG_COUNT 100
#endif

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

typedef enum {
    SYSTEM_AT_BEGINING,
    SYSTEM_AT_STEP,
    SYSTEM_AT_RENDER,
    SYSTEM_AT_END
} SYSTEM_WHEN;

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct Component {
    int32_t  key;
    void    *value;
} ObjectComponent;

/* Common components */
typedef Vector3f Position;
typedef Vector2f Scale;
typedef double   Rotation;
typedef Collider Collider;

typedef struct GameObject GameObject;
typedef struct GameObject {
    char *name;
    char *type;
    int32_t layer;   // To do

    // To do: use these
    bool active;
    bool visible;

    // Temporary
    struct { int32_t z; } order;

    // To do: mark and remove system
    bool toRemove;

    ObjectComponent *components;

    MsgBuf msg;

    bool is_beginning;
    void (*AtFirstFrame)(GameObject *object);
    void (*AtBeginning)(GameObject *object);
    void (*AtStep)(GameObject *object);
    void (*AtRender)(GameObject *object);
    void (*AtEnd)(GameObject *object);
} GameObject;

/////////////////////////////////////////////////
// Initialization and instantiator functions
////////////////////////////////////////////////

GameObject *Object_NewObject(const char *name, const char *type);
void Object_DeleteObject(GameObject *obj);
void Object_InstantiateObject(GameObject *object);
GameObject *Object_GetObject(const char *name);
void Object_GetObjectOfType(const char *name, void(*func)(GameObject *obj));

/////////////////////////////////////////////////
// Messaging
////////////////////////////////////////////////

void Object_SendMessage(GameObject *obj, const char *msg);
bool Object_ReceiveMessage(GameObject *obj, const char *msg);

/////////////////////////////////////////////////
// Component
////////////////////////////////////////////////

void  Object_SetComponent(GameObject *obj, const char *name, void *component);
void *Object_GetComponent(GameObject *obj, const char *name);

#define OBJECT_AddComponent(obj, component) \
    component *_##obj##_component_##component = DE_NEW(component, 1);   \
    Object_SetComponent(obj, #component, (void*)(_##obj##_component_##component))

#define OBJECT_AddComponentEx(obj, component) \
    component *_##obj##_component_##component = component##_Init();     \
    Object_SetComponent(obj, #component, (void*)(_##obj##_component_##component))

#define OBJECT_GetComponent(obj, component) \
    (component*)Object_GetComponent(obj, #component)

/////////////////////////////////////////////////
// Getters and Setters
////////////////////////////////////////////////

/***********
 * Position
 ***********/

void Object_SetPosition(GameObject *obj, Vector2f pos);
Vector2f Object_GetPosition(GameObject *obj);

/***********
 * Angle
 ***********/

void Object_SetAngle(GameObject *obj, double angle);
double Object_GetAngle(GameObject *obj);

/***********
 * Z-Order
 ***********/

void Object_SetZOrder(GameObject *obj, int32_t z);
int32_t Object_GetZOrder(GameObject *obj);

/***********
 * Status
 ***********/

bool Object_IsDead(GameObject *obj);
bool Object_IsHidden(GameObject *obj);
void Object_Hide(GameObject *obj, bool hide);

/***********
 * Collider
 ***********/

Collider Object_GetCollider(GameObject *obj);
void Object_SetCollider(GameObject *obj, Collider collider);

/////////////////////////////////////////////////
// Rotation Functions 
////////////////////////////////////////////////

void Object_Rotate(GameObject *obj, double angle, int speed);
void Object_RotateTowardsObject(GameObject *obj, GameObject *target, int speed);
void Object_RotateTowardsPosition(GameObject *obj, Vector2f pos, int speed);

static inline void NULL_OBJFUNC(GameObject *obj) { }