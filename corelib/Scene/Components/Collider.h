/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../Config.h"
#include "../Object.h"
#include "../ECSystem.h"

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
        struct { Vector2 vec;  };
        struct { Rect    rect;  };
        struct { Circle  circle; };
    };
} Collider;

/////////////////////////////////////////////////
// Registers/Constructors/Destructors
////////////////////////////////////////////////

void Collider_Register();

Collider *Collider_Init(Collider s);

/////////////////////////////////////////////////
// Collision checking
////////////////////////////////////////////////

bool Collider_CheckObject(GameObject *obj1, GameObject *obj2);
bool Collider_CheckObjectWithVector(GameObject *obj, Vector2 vec);
bool Collider_CheckObjectWithRect(GameObject *obj, Rect vec);
bool Collider_CheckObjectWithCircle(GameObject *obj, Circle vec);
bool Collider_Check(const char *name1, const char *name2);