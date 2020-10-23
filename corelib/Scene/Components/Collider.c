/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Collider.h"
#include "State2D.h"
#include "../../Modules/Physics/Collision.h"

/////////////////////////////////////////////////
// Registers/Constructors/Destructors
////////////////////////////////////////////////

void DE_CompColliderRegister() {
    DE_Flecs_RegisterComponent("Collider", sizeof(DeccanCompCollider), ECS_ALIGNOF(DeccanCompCollider));
}

/////////////////////////////////////////////////
// Collision checking
////////////////////////////////////////////////

#define COLLISION_CHECK_HEADER(obj)                                         \
    if(obj == NULL) {                                                       \
        DE_REPORT("Invalid object passed to collision system");             \
        return false;                                                       \
    }                                                                       \
    DeccanCompCollider *c = Object_GetComponent(obj, "Collider");           \
    if(c == NULL) {                                                         \
        DE_REPORT("Collider component not found in object: %s", "obj->name"); \
        return false;                                                       \
    }                                                                       \
    DeccanCompState2D *state = Object_GetComponent(obj, "State2D");         \
    if(state == NULL) {                                                     \
        DE_REPORT("State component not found in object: %s", "obj->name");  \
        return false;                                                       \
    }                                                                       \
    vec3 p; glm_vec3_copy(state->position, p);

bool DE_CompColliderCheckObject(GameObject *obj1, GameObject *obj2) {
    if(obj2 == NULL) {
        DE_REPORT("Invalid object passed to collision system");
    }

    COLLISION_CHECK_HEADER(obj1);

    switch(c->type) {
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

        default: {
            return false;
        }
    }
}

bool DE_CompColliderCheckObjectWithVector(GameObject *obj, vec2 vec) {
    COLLISION_CHECK_HEADER(obj);

    switch(c->type) {
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

        default: {
            return false;
        }
    }
}

bool DE_CompColliderCheckObjectWithRect(GameObject *obj, vec4 rect) {
    COLLISION_CHECK_HEADER(obj);

    switch(c->type) {
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

        default: {
            return false;
        }
    }
}

bool DE_CompColliderCheckObjectWithCircle(GameObject *obj, vec3 circle) {
    COLLISION_CHECK_HEADER(obj);

    switch(c->type) {
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

        default: {
            return false;
        }
    }
}

bool DE_CompColliderCheck(const char *name1, const char *name2) {
    GameObject *obj1 = Scene_GetObject(name1);
    GameObject *obj2 = Scene_GetObject(name2);
    return DE_CompColliderCheckObject(obj1, obj2);
}
