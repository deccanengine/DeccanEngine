/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../Config.h"
#include "../Object.h"
#include "../../Renderer/Primitives.h"
#include "../../Core/Memory.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

typedef enum {
    COLLIDER_Vec,
    COLLIDER_Rect,
    COLLIDER_Circle
} DeccanCompColliderType;

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct DeccanCompCollider {
    DeccanCompColliderType type;
    union {
        struct { vec2 vec; };
        struct { vec4 rect; };
        struct { vec3 circle; };
    };
} DeccanCompCollider;

/////////////////////////////////////////////////
// Registers/Constructors/Destructors
////////////////////////////////////////////////

void DE_CompColliderRegister();

/////////////////////////////////////////////////
// Collision checking
////////////////////////////////////////////////

bool DE_CompColliderCheckObject(GameObject *obj1, GameObject *obj2);
bool DE_CompColliderCheckObjectWithVector(GameObject *obj, vec2 vec);
bool DE_CompColliderCheckObjectWithRect(GameObject *obj, vec4 vec);
bool DE_CompColliderCheckObjectWithCircle(GameObject *obj, vec3 vec);
bool DE_CompColliderCheck(const char *name1, const char *name2);
