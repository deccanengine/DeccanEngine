/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Collider.h"
#include "Transform.h"
#include "../../Modules/Physics/Collision.h"

/////////////////////////////////////////////////
// Collision checking
////////////////////////////////////////////////
#define COLLISION_CHECK_HEADER(obj)                                                                                    \
    const char *name = DE_ObjectGetName(obj);                                                                          \
    DeccanCompCollider *c = DE_ObjectGetComponent(obj, "Collider");                                                    \
    if (c == NULL) {                                                                                                   \
        DE_WARN("Collider component not found in object: %s", name);                                                   \
        return false;                                                                                                  \
    }                                                                                                                  \
    DeccanCompTransform *state = DE_ObjectGetComponent(obj, "Transform");                                              \
    if (state == NULL) {                                                                                               \
        DE_WARN("State component not found in object: %s", name);                                                      \
        return false;                                                                                                  \
    }                                                                                                                  \
    vec3 p;                                                                                                            \
    glm_vec3_copy(state->position, p);

DE_IMPL bool DE_CompColliderCheckObject(DeccanGameObject obj1, DeccanGameObject obj2) {
    COLLISION_CHECK_HEADER(obj1);

    switch (c->type) {
    case COLLIDER_Vec: {
        vec2 vec = {p[0] + c->vec[0], p[1] + c->vec[1]};
        return DE_CompColliderCheckObjectWithVector(obj2, vec);
    }

    case COLLIDER_Rect: {
        vec4 rect = {p[0] + c->rect[0], p[1] + c->rect[1], c->rect[2], c->rect[3]};
        return DE_CompColliderCheckObjectWithRect(obj2, rect);
    }

    case COLLIDER_Circle: {
        vec3 circle = {p[0] + c->circle[0], p[1] + c->circle[1], c->circle[2]};
        return DE_CompColliderCheckObjectWithCircle(obj2, circle);
    }

    default: { return false; }
    }
}

DE_IMPL bool DE_CompColliderCheckObjectWithVector(DeccanGameObject obj, vec2 vec) {
    COLLISION_CHECK_HEADER(obj);

    switch (c->type) {
    case COLLIDER_Vec: {
        vec2 vec2 = {p[0] + c->vec[0], p[1] + c->vec[1]};
        return DE_CollisionVecVec(vec, vec2);
    }

    case COLLIDER_Rect: {
        vec4 rect = {p[0] + c->rect[0], p[1] + c->rect[1], c->rect[2], c->rect[3]};
        return DE_CollisionVecRect(vec, rect);
    }

    case COLLIDER_Circle: {
        vec3 circle = {p[0] + c->circle[0], p[1] + c->circle[1], c->circle[2]};
        return DE_CollisionCircleVec(circle, vec);
    }

    default: { return false; }
    }
}

DE_IMPL bool DE_CompColliderCheckObjectWithRect(DeccanGameObject obj, vec4 rect) {
    COLLISION_CHECK_HEADER(obj);

    switch (c->type) {
    case COLLIDER_Vec: {
        vec2 vec = {p[0] + c->vec[0], p[1] + c->vec[1]};
        return DE_CollisionVecRect(vec, rect);
    }

    case COLLIDER_Rect: {
        vec4 rect2 = {p[0] + c->rect[0], p[1] + c->rect[1], c->rect[2], c->rect[3]};
        return DE_CollisionRectRect(rect, rect2);
    }

    case COLLIDER_Circle: {
        vec3 circle = {p[0] + c->circle[0], p[1] + c->circle[1], c->circle[2]};
        return DE_CollisionRectCircle(rect, circle);
    }

    default: { return false; }
    }
}

DE_IMPL bool DE_CompColliderCheckObjectWithCircle(DeccanGameObject obj, vec3 circle) {
    COLLISION_CHECK_HEADER(obj);

    switch (c->type) {
    case COLLIDER_Vec: {
        vec2 vec = {p[0] + c->vec[0], p[1] + c->vec[1]};
        return DE_CollisionCircleVec(circle, vec);
    }

    case COLLIDER_Rect: {
        vec4 rect = {p[0] + c->rect[0], p[1] + c->rect[1], c->rect[2], c->rect[3]};
        return DE_CollisionRectCircle(rect, circle);
    }

    case COLLIDER_Circle: {
        vec3 circle2 = {p[0] + c->circle[0], p[1] + c->circle[1], c->circle[2]};
        return DE_CollisionCircleCircle(circle, circle2);
    }

    default: { return false; }
    }
}

DE_IMPL bool DE_CompColliderCheck(const char *name1, const char *name2) {
    DeccanGameObject obj1 = DE_SceneGetObject(name1);
    DeccanGameObject obj2 = DE_SceneGetObject(name2);
    return DE_CompColliderCheckObject(obj1, obj2);
}
