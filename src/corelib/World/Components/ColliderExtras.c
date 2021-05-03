/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Collider.h"
#include "Transform.h"
#include "../../Physics/Collision.h"

////////////////////////////////////////////////////////////////////////////////
// Collision checking
////////////////////////////////////////////////////////////////////////////////

#define COLLISION_CHECK_HEADER(obj)                                                                                    \
    const char *name = deccan_object_get_name(obj);                                                                    \
    deccan_comp_collider_t *c = deccan_object_get_component(obj, "Collider");                                          \
    if (c == NULL) {                                                                                                   \
        DE_WARN("Collider component not found in object: %s", name);                                                   \
        return false;                                                                                                  \
    }                                                                                                                  \
    deccan_comp_transform_t *state = deccan_object_get_component(obj, "Transform");                                    \
    if (state == NULL) {                                                                                               \
        DE_WARN("State component not found in object: %s", name);                                                      \
        return false;                                                                                                  \
    }                                                                                                                  \
    vec3 p;                                                                                                            \
    glm_vec3_copy(state->position, p);

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_comp_collider_check_object(deccan_game_object_t obj1, deccan_game_object_t obj2) {
    COLLISION_CHECK_HEADER(obj1);

    switch (c->type) {
    case DECCAN_COLLIDER_VEC: {
        vec2 vec = {p[0] + c->vec[0], p[1] + c->vec[1]};
        return deccan_comp_collider_check_object_with_vector(obj2, vec);
    }

    case DECCAN_COLLIDER_RECT: {
        vec4 rect = {p[0] + c->rect[0], p[1] + c->rect[1], c->rect[2], c->rect[3]};
        return deccan_comp_collider_check_object_with_rect(obj2, rect);
    }

    case DECCAN_COLLIDER_CIRCLE: {
        vec3 circle = {p[0] + c->circle[0], p[1] + c->circle[1], c->circle[2]};
        return deccan_comp_collider_check_object_with_circle(obj2, circle);
    }

    default: { return false; }
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_comp_collider_check_object_with_vector(deccan_game_object_t obj, vec2 vec) {
    COLLISION_CHECK_HEADER(obj);

    switch (c->type) {
    case DECCAN_COLLIDER_VEC: {
        vec2 vec2 = {p[0] + c->vec[0], p[1] + c->vec[1]};
        return deccan_collision_vec_vec(vec, vec2);
    }

    case DECCAN_COLLIDER_RECT: {
        vec4 rect = {p[0] + c->rect[0], p[1] + c->rect[1], c->rect[2], c->rect[3]};
        return deccan_collision_vec_rect(vec, rect);
    }

    case DECCAN_COLLIDER_CIRCLE: {
        vec3 circle = {p[0] + c->circle[0], p[1] + c->circle[1], c->circle[2]};
        return deccan_collision_circle_vec(circle, vec);
    }

    default: { return false; }
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_comp_collider_check_object_with_rect(deccan_game_object_t obj, vec4 rect) {
    COLLISION_CHECK_HEADER(obj);

    switch (c->type) {
    case DECCAN_COLLIDER_VEC: {
        vec2 vec = {p[0] + c->vec[0], p[1] + c->vec[1]};
        return deccan_collision_vec_rect(vec, rect);
    }

    case DECCAN_COLLIDER_RECT: {
        vec4 rect2 = {p[0] + c->rect[0], p[1] + c->rect[1], c->rect[2], c->rect[3]};
        return deccan_collision_rect_rect(rect, rect2);
    }

    case DECCAN_COLLIDER_CIRCLE: {
        vec3 circle = {p[0] + c->circle[0], p[1] + c->circle[1], c->circle[2]};
        return deccan_collision_rect_circle(rect, circle);
    }

    default: { return false; }
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_comp_collider_check_object_with_circle(deccan_game_object_t obj, vec3 circle) {
    COLLISION_CHECK_HEADER(obj);

    switch (c->type) {
    case DECCAN_COLLIDER_VEC: {
        vec2 vec = {p[0] + c->vec[0], p[1] + c->vec[1]};
        return deccan_collision_circle_vec(circle, vec);
    }

    case DECCAN_COLLIDER_RECT: {
        vec4 rect = {p[0] + c->rect[0], p[1] + c->rect[1], c->rect[2], c->rect[3]};
        return deccan_collision_rect_circle(rect, circle);
    }

    case DECCAN_COLLIDER_CIRCLE: {
        vec3 circle2 = {p[0] + c->circle[0], p[1] + c->circle[1], c->circle[2]};
        return deccan_collision_circle_circle(circle, circle2);
    }

    default: { return false; }
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_comp_collider_check(const char *name1, const char *name2) {
    deccan_game_object_t obj1 = deccan_scene_get_object(name1);
    deccan_game_object_t obj2 = deccan_scene_get_object(name2);
    return deccan_comp_collider_check_object(obj1, obj2);
}
