/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Collider.h"
#include "State2D.h"
#include "../../Behaviour/Physics/Collision.h"


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
    Vector3 p = state->position;

bool Collider_CheckObject(GameObject *obj1, GameObject *obj2) {
    if(obj2 == NULL) {
        DE_REPORT("Invalid object passed to collision system");
    }

    COLLISION_CHECK_HEADER(obj1);
    
    switch(c->type) {
        case COLLIDER_Vec: {
            Vector2 vec = {p.x + c->vec.x, p.y + c->vec.y};
            return Collider_CheckObjectWithVector(obj2, vec);
        }

        case COLLIDER_Rect: {
            Rect rect = {p.x + c->rect.x, p.y + c->rect.y, c->rect.w, c->rect.h};
            return Collider_CheckObjectWithRect(obj2, rect);
        }

        case COLLIDER_Circle: {
            Circle circle = {p.x + c->circle.x, p.y + c->circle.y, c->circle.radius};
            return Collider_CheckObjectWithCircle(obj2, circle);
        }

        default: {
            return false;
        } 
    }
}

bool Collider_CheckObjectWithVector(GameObject *obj, Vector2 vec) {
    COLLISION_CHECK_HEADER(obj);

    switch(c->type) {
        case COLLIDER_Vec: {
            Vector2 vec2 = {p.x + c->vec.x, p.y + c->vec.y};
            return Collision_VecVec(vec, vec2);
        }

        case COLLIDER_Rect: {
            Rect rect = {p.x + c->rect.x, p.y + c->rect.y, c->rect.w, c->rect.h};
            return Collision_VecRect(vec, rect);
        }

        case COLLIDER_Circle: {
            Circle circle = {p.x + c->circle.x, p.y + c->circle.y, c->circle.radius};
            return Collision_CircleVec(circle, vec);
        }

        default: {
            return false;
        }
    }
}

bool Collider_CheckObjectWithRect(GameObject *obj, Rect rect) {
    COLLISION_CHECK_HEADER(obj);

    switch(c->type) {
        case COLLIDER_Vec: {
            Vector2 vec = {p.x + c->vec.x, p.y + c->vec.y};
            return Collision_VecRect(vec, rect);
        }

        case COLLIDER_Rect: {
            Rect rect2 = {p.x + c->rect.x, p.y + c->rect.y, c->rect.w, c->rect.h};
            return Collision_RectRect(rect, rect2);
        }

        case COLLIDER_Circle: {
            Circle circle = {p.x + c->circle.x, p.y + c->circle.y, c->circle.radius};
            return Collision_RectCircle(rect, circle);
        }

        default: {
            return false;
        }
    }
}

bool Collider_CheckObjectWithCircle(GameObject *obj, Circle circle) {
    COLLISION_CHECK_HEADER(obj);

    switch(c->type) {
        case COLLIDER_Vec: {
            Vector2 vec = {p.x + c->vec.x, p.y + c->vec.y};
            return Collision_CircleVec(circle, vec);
        }

        case COLLIDER_Rect: {
            Rect rect = {p.x + c->rect.x, p.y + c->rect.y, c->rect.w, c->rect.h};
            return Collision_RectCircle(rect, circle);
        }

        case COLLIDER_Circle: {
            Circle circle2 = {p.x + c->circle.x, p.y + c->circle.y, c->circle.radius};
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