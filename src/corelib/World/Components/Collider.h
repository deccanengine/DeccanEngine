/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../Config.h"
#include "../../Core/Utils.h"
#include "../Object.h"

////////////////////////////////////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////////////////////////////////////

typedef enum { 
    COLLIDER_Vec, 
    COLLIDER_Rect, 
    COLLIDER_Circle 
} deccan_comp_collider_type_t;

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct deccan_comp_collider_t {
    deccan_comp_collider_type_t type;
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
} deccan_comp_collider_t;

////////////////////////////////////////////////////////////////////////////////
// Collision checking
////////////////////////////////////////////////////////////////////////////////

DE_API bool deccan_comp_collider_check_object(deccan_game_object_t obj1, deccan_game_object_t obj2);
DE_API bool deccan_comp_collider_check_object_with_vector(deccan_game_object_t obj, vec2 vec);
DE_API bool deccan_comp_collider_check_object_with_rect(deccan_game_object_t obj, vec4 vec);
DE_API bool deccan_comp_collider_check_object_with_circle(deccan_game_object_t obj, vec3 vec);
DE_API bool deccan_comp_collider_check(const char *name1, const char *name2);
