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

#define obj_func(x) void (*x)(GameObject *object)

typedef struct GameObject GameObject;
typedef struct GameObject {
    struct { char *name, *type; } info;     /* Basic information about the object */ 
    Vector2f position;               /* Positional info of the object */
    Vector2f size;                   /* Size of the rect bounding the object */
    Vector2f transform;              /* Transformation info */
    double angle;
    struct { bool dead, hidden; } status;   /* Status */
    Collider collider;               /* Collider info */
    union {
        struct { Color color; };     /* Color value for shape rendering */
    };

    msgbuf msg;
    void (*SendMessage)(GameObject *obj, const char *msg);
    bool (*ReceiveMessage)(GameObject *obj, const char *msg);

    bool is_beginning;
    obj_func(AtFirstFrame);
    obj_func(AtBeginning);
    obj_func(AtStep);
    obj_func(AtRender);
    obj_func(AtEnd);
} GameObject;

GameObject *Object_NewObject(const char *name, const char *type, obj_func(af), obj_func(ab), obj_func(as), obj_func(ar), obj_func(ae));
void Object_InstantiateObject(GameObject *object);
GameObject *Object_GetObject(const char *name);
void Object_GetObjectOfType(const char *name, void(*func)(GameObject *obj));

void Object_SetAngle(GameObject *obj, double angle);

double Object_GetAngle(GameObject *obj);

void Object_Rotate(GameObject *obj, double angle, int speed);
void Object_RotateTowardsObject(GameObject *obj, GameObject *target, int speed);
void Object_RotateTowardsPosition(GameObject *obj, Vector2f pos, int speed);

static inline void NULL_OBJFUNC(GameObject *obj) { }

#undef obj_func