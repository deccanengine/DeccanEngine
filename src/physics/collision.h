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

Deccan_Collider DE_Collision_new_rect_collider(Deccan_PosRect rect);
Deccan_Collider DE_Collision_new_circle_collider(Deccan_Circle circle);

bool DE_Collision_test_vec_vec_from(Deccan_Vector2i *v1, Deccan_Vector2i *v2);
bool DE_Collision_test_rect_rect_from(Deccan_PosRect *r1, Deccan_PosRect *r2);
bool DE_Collision_test_circle_circle_from(Deccan_Circle *c1, Deccan_Circle *c2);
bool DE_Collision_test_vec_rect_from(Deccan_Vector2i *vec, Deccan_PosRect *rect);
bool DE_Collision_test_circle_vec_from(Deccan_Circle *circle, Deccan_Vector2i *vec);
bool DE_Collision_test_rect_circle_from(Deccan_PosRect *rect, Deccan_Circle *circle);
bool DE_Collision_test_from(Deccan_GameObject *obj1, Deccan_GameObject *obj2);
bool DE_Collision_test_vec_from(Deccan_GameObject *obj, Deccan_Vector2i *vec);
bool DE_Collision_test(const char *name1, const char *name2);

#ifdef __STDC__
    typedef struct DE_Collision {
        Deccan_Collider (*new_rect_collider)(Deccan_PosRect rect);
        Deccan_Collider (*new_circle_collider)(Deccan_Circle circle);
        
        bool (*test_vec_vec_from)(Deccan_Vector2i *v1, Deccan_Vector2i *v2);
        bool (*test_rect_rect_from)(Deccan_PosRect *r1, Deccan_PosRect *r2);
        bool (*test_circle_circle_from)(Deccan_Circle *c1, Deccan_Circle *c2);
        bool (*test_vec_rect_from)(Deccan_Vector2i *vec, Deccan_PosRect *rect);
        bool (*test_circle_vec_from)(Deccan_Circle *circle, Deccan_Vector2i *vec);
        bool (*test_rect_circle_from)(Deccan_PosRect *rect, Deccan_Circle *circle);
        bool (*test_from)(Deccan_GameObject *obj1, Deccan_GameObject *obj2);
        bool (*test_vec_from)(Deccan_GameObject *obj, Deccan_Vector2i *vec);
        bool (*test)(const char *name1, const char *name2);
    } DE_Collision;

    static DE_Collision Deccan_Collision = { 
        DE_Collision_new_rect_collider,
        DE_Collision_new_circle_collider,

        DE_Collision_test_vec_vec_from,
        DE_Collision_test_rect_rect_from,
        DE_Collision_test_circle_circle_from,
        DE_Collision_test_vec_rect_from,
        DE_Collision_test_circle_vec_from,
        DE_Collision_test_rect_circle_from,
        DE_Collision_test_from,
        DE_Collision_test_vec_from,
        DE_Collision_test
    };
#elif __cplusplus

#endif