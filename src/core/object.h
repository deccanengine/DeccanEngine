/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "scene.h"
#include "../physics/collider.h"
#include "../utils/vector.h"

#define obj_func(x) void (*x)(Deccan_GameObject *object)

typedef struct Deccan_GameObject Deccan_GameObject;
typedef struct Deccan_GameObject {
    struct { char *name, *type; } info;     /* Basic information about the object */ 
    Deccan_Vector2i position;               /* Positional info of the object */
    Deccan_Vector2f transform;              /* Transformation info */
    struct { bool dead, hidden; } status;   /* Status */
    Deccan_Collider collider;

    obj_func(at_beginning);
    obj_func(at_step);
    obj_func(at_render);
    obj_func(at_end);
} Deccan_GameObject;

Deccan_GameObject *_priv_Object_new_object(const char *name, const char *type, obj_func(ab), obj_func(as), obj_func(ar), obj_func(ae));
void _priv_Object_instantiate_object(Deccan_GameObject *object);
Deccan_GameObject *_priv_Object_get_object(const char *name);

#ifdef __STDC__

    typedef struct _priv_Object {
        Deccan_GameObject *(*new_object)(const char *name, const char *type, obj_func(ab), obj_func(as), obj_func(ar), obj_func(ae));
        void (*instantiate_object)(Deccan_GameObject *object);
        Deccan_GameObject *(*get_object)(const char *name);
    } _priv_Object;

    static _priv_Object Deccan_Object = { 
        _priv_Object_new_object,
        _priv_Object_instantiate_object,
        _priv_Object_get_object
    };

#elif __cplusplus

#endif

#undef obj_func