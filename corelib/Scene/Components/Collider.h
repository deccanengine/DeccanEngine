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
} COLLIDER;

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct Collider {
    COLLIDER type;
    union {
        struct { vec2 vec; };
        struct { vec4 rect; };
        struct { vec3 circle; };
    };
} Collider;

/////////////////////////////////////////////////
// Registers/Constructors/Destructors
////////////////////////////////////////////////

void Collider_Register();

/////////////////////////////////////////////////
// Collision checking
////////////////////////////////////////////////

bool Collider_CheckObject(GameObject *obj1, GameObject *obj2);
bool Collider_CheckObjectWithVector(GameObject *obj, vec2 vec);
bool Collider_CheckObjectWithRect(GameObject *obj, vec4 vec);
bool Collider_CheckObjectWithCircle(GameObject *obj, vec3 vec);
bool Collider_Check(const char *name1, const char *name2);
