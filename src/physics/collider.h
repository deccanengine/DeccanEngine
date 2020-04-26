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

typedef struct DE_Collider {
    int type;
    union {
        struct { DE_Vector2i vec;  };
        struct { DE_PosRect rect;  };
        struct { DE_Circle circle; };
    };
} DE_Collider;