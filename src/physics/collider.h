/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "shape.h"
#include "../utils/vector.h"

enum {
    ColliderVec,
    ColliderRect,
    ColliderCircle
};

typedef struct Deccan_Collider {
    int type;
    union {
        struct { Deccan_Vector2i vec;  };
        struct { Deccan_PosRect rect;  };
        struct { Deccan_Circle circle; };
    };
} Deccan_Collider;