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

void Collider_Register() {
    ECSystem_RegisterComponent("Collider");
}

Collider *Collider_Init(Collider c) {
    Collider *collider = DE_NEW(Collider, 1);
    *collider = c;

    return collider;
}

/////////////////////////////////////////////////
// Collision checking
////////////////////////////////////////////////

#define COLLISION_CHECK_HEADER(obj)                                         \
    if(obj == NULL) {                                                       \
        DE_REPORT("Invalid object passed to collision system");             \
        return false;                                                       \
    }                                                                       \
    Collider *c = OBJECT_GetComponent(obj, Collider);                       \
    if(c == NULL) {                                                         \
        DE_REPORT("Collider component not found in object: %s", obj->name); \
        return false;                                                       \
    }                                                                       \
    State2D *state = Object_GetComponent(obj, "State2D");                   \
    if(state == NULL) {                                                     \
        DE_REPORT("State component not found in object: %s", obj->name);    \
        return false;                                                       \
    }                                                                       \
    vec3 p; glm_vec3_copy(state->position, p);

bool Collider_CheckObject(GameObject *obj1, GameObject *obj2) {
    if(obj2 == NULL) {
        DE_REPORT("Invalid object passed to collision system");
    }

    COLLISION_CHECK_HEADER(obj1);

    switch(c->type) {
        case COLLIDER_Vec: {
            vec2 vec = {p[0] + c->vec[0], p[1] + c->vec[1]};
            return Collider_CheckObjectWithVector(obj2, vec);
        }

        case COLLIDER_Rect: {
            vec4 rect = {p[0] + c->rect[0], p[1] + c->rect[1], c->rect[2], c->rect[3]};
            return Collider_CheckObjectWithRect(obj2, rect);
        }

        case COLLIDER_Circle: {
            vec3 circle = {p[0] + c->circle[0], p[1] + c->circle[1], c->circle[2]};
            return Collider_CheckObjectWithCircle(obj2, circle);
        }

        default: {
            return false;
        }
    }
}

bool Collider_CheckObjectWithVector(GameObject *obj, vec2 vec) {
    COLLISION_CHECK_HEADER(obj);

    switch(c->type) {
        case COLLIDER_Vec: {
            vec2 vec2 = {p[0] + c->vec[0], p[1] + c->vec[1]};
            return Collision_VecVec(vec, vec2);
        }

        case COLLIDER_Rect: {
            vec4 rect = {p[0] + c->rect[0], p[1] + c->rect[1], c->rect[2], c->rect[3]};
            return Collision_VecRect(vec, rect);
        }

        case COLLIDER_Circle: {
            vec3 circle = {p[0] + c->circle[0], p[1] + c->circle[1], c->circle[2]};
            return Collision_CircleVec(circle, vec);
        }

        default: {
            return false;
        }
    }
}

bool Collider_CheckObjectWithRect(GameObject *obj, vec4 rect) {
    COLLISION_CHECK_HEADER(obj);

    switch(c->type) {
        case COLLIDER_Vec: {
            vec2 vec = {p[0] + c->vec[0], p[1] + c->vec[1]};
            return Collision_VecRect(vec, rect);
        }

        case COLLIDER_Rect: {
            vec4 rect2 = {p[0] + c->rect[0], p[1] + c->rect[1], c->rect[2], c->rect[3]};
            return Collision_RectRect(rect, rect2);
        }

        case COLLIDER_Circle: {
            vec3 circle = {p[0] + c->circle[0], p[1] + c->circle[1], c->circle[2]};
            return Collision_RectCircle(rect, circle);
        }

        default: {
            return false;
        }
    }
}

bool Collider_CheckObjectWithCircle(GameObject *obj, vec3 circle) {
    COLLISION_CHECK_HEADER(obj);

    switch(c->type) {
        case COLLIDER_Vec: {
            vec2 vec = {p[0] + c->vec[0], p[1] + c->vec[1]};
            return Collision_CircleVec(circle, vec);
        }

        case COLLIDER_Rect: {
            vec4 rect = {p[0] + c->rect[0], p[1] + c->rect[1], c->rect[2], c->rect[3]};
            return Collision_RectCircle(rect, circle);
        }

        case COLLIDER_Circle: {
            vec3 circle2 = {p[0] + c->circle[0], p[1] + c->circle[1], c->circle[2]};
            return Collision_CircleCircle(circle, circle2);
        }

        default: {
            return false;
        }
    }
}

bool Collider_Check(const char *name1, const char *name2) {
    GameObject *obj1 = Object_GetObject(name1);
    GameObject *obj2 = Object_GetObject(name2);
    return Collider_CheckObject(obj1, obj2);
}
