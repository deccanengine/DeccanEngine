/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once

#define MAKE_VECTOR2(p,type)         \
typedef struct DE_Vector2 ## p { \
    type x, y;                       \
} DE_Vector2 ## p;

MAKE_VECTOR2(i, int32_t);
MAKE_VECTOR2(u, uint32_t);
MAKE_VECTOR2(f, float);

#define MAKE_VECTOR3(p,type)         \
typedef struct DE_Vector3 ## p { \
    type x, y, z;                    \
} DE_Vector3 ## p;

MAKE_VECTOR3(i, int32_t);

#undef MAKE_VECTOR