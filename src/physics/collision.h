/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "rect.h"
#include "collider.h"
#include "../core/object.h"
#include "../utils/vector.h"

Deccan_Collider _priv_Collision_new_rect_collider(Deccan_PosRect rect);
bool _priv_Collision_test_vec(Deccan_GameObject *obj, Deccan_Vector2i vec);

#ifdef __STDC__
    typedef struct _priv_Collision {
        Deccan_Collider (*new_rect_collider)(Deccan_PosRect rect);
        bool (*test_vec)(Deccan_GameObject *obj, Deccan_Vector2i vec);
    } _priv_Collision;

    static _priv_Collision Deccan_Collision = { 
        _priv_Collision_new_rect_collider,
        _priv_Collision_test_vec
    };
#elif __cplusplus

#endif