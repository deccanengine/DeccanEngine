/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../Config.h"
#include "../Object.h"
#include "../../Renderer/Primitives.h"
#include "../../Core/Utils.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

typedef enum { COLLIDER_Vec, COLLIDER_Rect, COLLIDER_Circle } DeccanCompColliderType;

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct DeccanCompCollider {
    DeccanCompColliderType type;
    union {
        struct {
            vec2 vec;
        };
        struct {
            vec4 rect;
        };
        struct {
            vec3 circle;
        };
    };
} DeccanCompCollider;

/////////////////////////////////////////////////
// Registers/Constructors/Destructors
////////////////////////////////////////////////

DE_API void DE_CompColliderRegister(void);

/////////////////////////////////////////////////
// Collision checking
////////////////////////////////////////////////

DE_API bool DE_CompColliderCheckObject(DeccanGameObject obj1, DeccanGameObject obj2);
DE_API bool DE_CompColliderCheckObjectWithVector(DeccanGameObject obj, vec2 vec);
DE_API bool DE_CompColliderCheckObjectWithRect(DeccanGameObject obj, vec4 vec);
DE_API bool DE_CompColliderCheckObjectWithCircle(DeccanGameObject obj, vec3 vec);
DE_API bool DE_CompColliderCheck(const char *name1, const char *name2);
