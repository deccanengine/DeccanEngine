/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <deccanengine/world/components/legacy_collider.h>
#include <deccanengine/world/components/transform.h>
#include <deccanengine/physics/collision.h>
#include <deccanengine/world/world.h>

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
    vec3s p = state->position;

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_comp_collider_check_object(deccan_object_t obj1, deccan_object_t obj2) {
    COLLISION_CHECK_HEADER(obj1);

    switch (c->type) {
    case DECCAN_COLLIDER_VEC: {
        vec2 vec = {p.x + c->vec.x, p.y + c->vec.y};
        return deccan_comp_collider_check_object_with_vector(obj2, vec);
    }

    case DECCAN_COLLIDER_RECT: {
        vec4 rect = {p.x + c->rect.x, p.y + c->rect.y, c->rect.z, c->rect.w};
        return deccan_comp_collider_check_object_with_rect(obj2, rect);
    }

    case DECCAN_COLLIDER_CIRCLE: {
        vec3 circle = {p.x + c->circle.x, p.y + c->circle.y, c->circle.z};
        return deccan_comp_collider_check_object_with_circle(obj2, circle);
    }

    default: { return false; }
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_comp_collider_check_object_with_vector(deccan_object_t obj, vec2 vec) {
    COLLISION_CHECK_HEADER(obj);

    switch (c->type) {
    case DECCAN_COLLIDER_VEC: {
        vec2 vec2 = {p.x + c->vec.x, p.y + c->vec.y};
        return deccan_collision_vec_vec(vec, vec2);
    }

    case DECCAN_COLLIDER_RECT: {
        vec4 rect = {p.x + c->rect.x, p.y + c->rect.y, c->rect.z, c->rect.w};
        return deccan_collision_vec_rect(vec, rect);
    }

    case DECCAN_COLLIDER_CIRCLE: {
        vec3 circle = {p.x + c->circle.x, p.y + c->circle.y, c->circle.z};
        return deccan_collision_circle_vec(circle, vec);
    }

    default: { return false; }
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_comp_collider_check_object_with_rect(deccan_object_t obj, vec4 rect) {
    COLLISION_CHECK_HEADER(obj);

    switch (c->type) {
    case DECCAN_COLLIDER_VEC: {
        vec2 vec = {p.x + c->vec.x, p.y + c->vec.y};
        return deccan_collision_vec_rect(vec, rect);
    }

    case DECCAN_COLLIDER_RECT: {
        vec4 rect2 = {p.x + c->rect.x, p.y + c->rect.y, c->rect.z, c->rect.w};
        return deccan_collision_rect_rect(rect, rect2);
    }

    case DECCAN_COLLIDER_CIRCLE: {
        vec3 circle = {p.x + c->circle.x, p.y + c->circle.y, c->circle.z};
        return deccan_collision_rect_circle(rect, circle);
    }

    default: { return false; }
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_comp_collider_check_object_with_circle(deccan_object_t obj, vec3 circle) {
    COLLISION_CHECK_HEADER(obj);

    switch (c->type) {
    case DECCAN_COLLIDER_VEC: {
        vec2 vec = {p.x + c->vec.x, p.y + c->vec.y};
        return deccan_collision_circle_vec(circle, vec);
    }

    case DECCAN_COLLIDER_RECT: {
        vec4 rect = {p.x + c->rect.x, p.y + c->rect.y, c->rect.z, c->rect.w};
        return deccan_collision_rect_circle(rect, circle);
    }

    case DECCAN_COLLIDER_CIRCLE: {
        vec3 circle2 = {p.x + c->circle.x, p.y + c->circle.y, c->circle.z};
        return deccan_collision_circle_circle(circle, circle2);
    }

    default: { return false; }
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_comp_collider_check(const char *name1, const char *name2) {
    deccan_scene_t *scene = deccan_world_get_current_scene();
    deccan_object_t obj1 = deccan_scene_get_object(scene, name1);
    deccan_object_t obj2 = deccan_scene_get_object(scene, name2);
    return deccan_comp_collider_check_object(obj1, obj2);
}
