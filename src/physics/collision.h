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

DE_Collider DE_Collision_new_rect_collider(DE_PosRect rect);
DE_Collider DE_Collision_new_circle_collider(DE_Circle circle);

bool DE_Collision_test_vec_vec_from(DE_Vector2i *v1, DE_Vector2i *v2);
bool DE_Collision_test_rect_rect_from(DE_PosRect *r1, DE_PosRect *r2);
bool DE_Collision_test_circle_circle_from(DE_Circle *c1, DE_Circle *c2);
bool DE_Collision_test_vec_rect_from(DE_Vector2i *vec, DE_PosRect *rect);
bool DE_Collision_test_circle_vec_from(DE_Circle *circle, DE_Vector2i *vec);
bool DE_Collision_test_rect_circle_from(DE_PosRect *rect, DE_Circle *circle);
bool DE_Collision_test_from(DE_GameObject *obj1, DE_GameObject *obj2);
bool DE_Collision_test_vec_from(DE_GameObject *obj, DE_Vector2i *vec);
bool DE_Collision_test(const char *name1, const char *name2);