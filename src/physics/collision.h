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

DE_Collider DE_Collision_NewRectCollider(DE_PosRect rect);
DE_Collider DE_Collision_NewCircleCollider(DE_Circle circle);

bool DE_Collision_VecVec(DE_Vector2f *v1, DE_Vector2f *v2);
bool DE_Collision_RectRect(DE_PosRect *r1, DE_PosRect *r2);
bool DE_Collision_CircleCircle(DE_Circle *c1, DE_Circle *c2);
bool DE_Collision_VecRect(DE_Vector2f *vec, DE_PosRect *rect);
bool DE_Collision_CircleVec(DE_Circle *circle, DE_Vector2f *vec);
bool DE_Collision_RectCircle(DE_PosRect *rect, DE_Circle *circle);
bool DE_Collision_ObjectObject(DE_GameObject *obj1, DE_GameObject *obj2);
bool DE_Collision_ObjectVec(DE_GameObject *obj, DE_Vector2f *vec);
bool DE_Collision_Test(const char *name1, const char *name2);