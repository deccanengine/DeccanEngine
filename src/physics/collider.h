/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "rect.h"

enum {
    Deccan_ColliderType_Rect
};

typedef struct Deccan_Collider {
    int type;
    union {
        struct { Deccan_PosRect rect; };
    };
} Deccan_Collider;