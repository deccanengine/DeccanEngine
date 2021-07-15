/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"

////////////////////////////////////////////////////////////////////////////////
// Collisions
////////////////////////////////////////////////////////////////////////////////

DE_API bool deccan_collision_vec_vec(vec2 v1, vec2 v2);
DE_API bool deccan_collision_rect_rect(vec4 r1, vec4 r2);
DE_API bool deccan_collision_circle_circle(vec3 c1, vec3 c2);
DE_API bool deccan_collision_vec_rect(vec2 vec, vec4 rect);
DE_API bool deccan_collision_circle_vec(vec3 circle, vec2 vec);
DE_API bool deccan_collision_rect_circle(vec4 rect, vec3 circle);
