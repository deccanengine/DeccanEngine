/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include <Deccan/Config.h>
#include <Deccan/Renderer.h>
#include <Deccan/Physics.h>

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
    int32_t  id;
    void    *address;
} Component;

typedef struct GameObject GameObject;
typedef struct GameObject {
    struct { char *name, *type; } info;     /* Basic information about the object */ 
    Vector2f position;                      /* Positional info of the object */
    Vector2f size;                          /* Size of the rect bounding the object */
    Vector2f transform;                     /* Transformation info */
    struct { int32_t z, layer; } order;     /* The Z order and layer */
    double angle;                           /* Present rotation(in degrees) */
    struct { bool dead, hidden; } status;   /* Status */
    Collider collider;                      /* Collider info */
    /* !! Unused !!*/
    union {
        struct { Color color; };     /* Color value for shape rendering */
    };

    Component **components;
    int32_t component_length;

    MsgBuf msg;
    void (*SendMessage)(GameObject *obj, const char *msg);
    bool (*ReceiveMessage)(GameObject *obj, const char *msg);

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
// Component
////////////////////////////////////////////////

void  Object_SetComponent(GameObject *obj, int32_t id, void *component);
void *Object_GetComponent(GameObject *obj, int32_t id);

#define OBJECT_AddComponent(obj, component) \
    component *_##obj##_component_##component = DE_NEW(component, 1);   \
    Object_SetComponent(obj, ECSystem_GetComponentID(#component), (void*)(_##obj##_component_##component))

#define OBJECT_GetComponent(obj, component) \
    (component*)Object_GetComponent(obj, ECSystem_GetComponentID(#component))

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

/////////////////////////////////////////////////
// Entity Component System
////////////////////////////////////////////////

int32_t ECSystem_RegisterComponent(const char *name);
int32_t ECSystem_GetComponentID(const char *name);
const char *ECSystem_GetComponentName(int32_t id);