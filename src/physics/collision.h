/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "shape.h"
#include "collider.h"
#include "../core/object.h"
#include "../utils/vector.h"

Deccan_Collider _priv_Collision_new_rect_collider(Deccan_PosRect rect);
Deccan_Collider _priv_Collision_new_circle_collider(Deccan_Circle circle);

bool _priv_Collision_test_vec_from(Deccan_GameObject *obj, Deccan_Vector2i vec);
bool _priv_Collision_test_object_from(Deccan_GameObject *obj1, Deccan_GameObject *obj2);
bool _priv_Collision_test_object(const char *name1, const char *name2);

#ifdef __STDC__
    typedef struct _priv_Collision {
        Deccan_Collider (*new_rect_collider)(Deccan_PosRect rect);
        Deccan_Collider (*new_circle_collider)(Deccan_Circle circle);
        
        bool (*test_vec_from)(Deccan_GameObject *obj, Deccan_Vector2i vec);
        bool (*test_object_from)(Deccan_GameObject *obj1, Deccan_GameObject *obj2);
        bool (*test_object)(const char *name1, const char *name2);
    } _priv_Collision;

    static _priv_Collision Deccan_Collision = { 
        _priv_Collision_new_rect_collider,
        _priv_Collision_new_circle_collider,

        _priv_Collision_test_vec_from,
        _priv_Collision_test_object_from,
        _priv_Collision_test_object
    };
#elif __cplusplus

#endif