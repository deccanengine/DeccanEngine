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

bool Collider_CheckObject(GameObject *obj1, GameObject *obj2) {
    /* Possible cases where v = vector, r = rect and c = circle
        v <-> v      r <-> r      c <-> c
        v <-> r      c <-> v      r <-> c 
    */
    if(obj1 == NULL || obj2 == NULL) {
        DE_REPORT("Invalid object(s) passed to collision system");
    }

    State2D  *obj1_state    = Object_GetComponent(obj1, "State2D");
    Vector3f  obj1_position = obj1_state->position;
    Collider *obj1_collider = Object_GetComponent(obj1, "Collider");
    
    State2D  *obj2_state    = Object_GetComponent(obj2, "State2D");
    Vector3f  obj2_position = obj2_state->position;
    Collider *obj2_collider = Object_GetComponent(obj2, "Collider");

    int type1 = obj1_collider->type;
    int type2 = obj2_collider->type;
    
    /* Matching cases */
    if(type1 == type2) {
        switch(type1) {
            /* Point collision i.e. v<->v */
            case COLLIDER_Vec: {
                Vector2f v1 = {obj1_position.x + obj1_collider->vec.x, obj1_position.y + obj1_collider->vec.y}; 
                Vector2f v2 = {obj2_position.x + obj2_collider->vec.x, obj2_position.y + obj2_collider->vec.y}; 
                
                return Collision_VecVec(&v1, &v2);    /* Exit */
            }

            /* AABB collision i.e. r<->r */
            case COLLIDER_Rect: { 
                PosRect r1 = {obj1_position.x + obj1_collider->rect.x1, obj1_position.y + obj1_collider->rect.y1,
                              obj1_position.x + obj1_collider->rect.x2, obj1_position.y + obj1_collider->rect.y2};
                PosRect r2 = {obj2_position.x + obj2_collider->rect.x1, obj2_position.y + obj2_collider->rect.y1,
                              obj2_position.x + obj2_collider->rect.x2, obj2_position.y + obj2_collider->rect.y2};

                return Collision_RectRect(&r1, &r2);    /* Exit */
            }

            /* Circle collision i.e. c<->c */
            case COLLIDER_Circle: {
                Circle c1 = {obj1_position.x + obj1_collider->circle.x, obj1_position.y + obj1_collider->circle.y, obj1_collider->circle.radius};
                Circle c2 = {obj2_position.x + obj2_collider->circle.x, obj2_position.y + obj2_collider->circle.y, obj2_collider->circle.radius};

                return Collision_CircleCircle(&c1, &c2);  /* Exit */
            }
        }
    }

    /* Remaining cases */
    bool case_1 = (type1 == COLLIDER_Vec  && type2 == COLLIDER_Rect);
    bool case_2 = (type1 == COLLIDER_Rect && type2 == COLLIDER_Vec);

    /* v<->r */
    if(case_1 || case_2) {
        Vector2f vec;
        PosRect  rect;

        /* v & r */
        if(case_1) {
            vec  = (Vector2f){obj1_position.x + obj1_collider->vec.x,   obj1_position.y + obj1_collider->vec.y};
            rect = (PosRect) {obj2_position.x + obj2_collider->rect.x1, obj2_position.y + obj2_collider->rect.y1,
                              obj2_position.x + obj2_collider->rect.x2, obj2_position.y + obj2_collider->rect.y2};
        }
        /* r & v   */
        else {
            vec  = (Vector2f){obj2_position.x + obj2_collider->vec.x,   obj2_position.y + obj2_collider->vec.y};
            rect = (PosRect) {obj1_position.x + obj1_collider->rect.x1, obj1_position.y + obj1_collider->rect.y1,
                              obj1_position.x + obj1_collider->rect.x2, obj1_position.y + obj1_collider->rect.y2};
        }

        return Collision_VecRect(&vec, &rect);    /* Exit */
    }

    bool case_3 = (type1 == COLLIDER_Circle && type2 == COLLIDER_Vec);
    bool case_4 = (type1 == COLLIDER_Vec    && type2 == COLLIDER_Circle);

    /* c <-> v */
    if(case_3 || case_4) {
        Circle   circle;
        Vector2f vec;

        /* c & v */
        if(case_3) {
            vec    = (Vector2f){obj2_position.x + obj2_collider->vec.x, obj2_position.y + obj2_collider->vec.y};
            circle = (Circle)  {obj1_position.x + obj1_collider->circle.x, obj1_position.y + obj1_collider->circle.y, obj1_collider->circle.radius};
        }
        /* v & c */
        else {
            vec    = (Vector2f){obj1_position.x + obj1_collider->vec.x, obj1_position.y + obj1_collider->vec.y};
            circle = (Circle)  {obj2_position.x + obj2_collider->circle.x, obj2_position.y + obj2_collider->circle.y, obj2_collider->circle.radius};
        }
            
        return Collision_CircleVec(&circle, &vec);   /* Exit */
    }

    bool case_5 = (type1 == COLLIDER_Rect   && type2 == COLLIDER_Circle);
    bool case_6 = (type1 == COLLIDER_Circle && type2 == COLLIDER_Rect);
    
    /* r <-> c */
    if(case_5 || case_6) {
        PosRect rect;
        Circle  circle;

        /* r & c */
        if(case_5) {
            rect   = (PosRect){obj1_position.x + obj1_collider->rect.x1, obj1_position.y + obj1_collider->rect.y1,
                               obj1_position.x + obj1_collider->rect.x2, obj1_position.y + obj1_collider->rect.y2};
            circle = (Circle) {obj2_position.x + obj2_collider->circle.x, obj2_position.y + obj2_collider->circle.y,
                               obj2_collider->circle.radius};
        }
        /* c & r */
        else {
            rect   = (PosRect){obj2_position.x + obj2_collider->rect.x1, obj2_position.y + obj2_collider->rect.y1,
                               obj2_position.x + obj2_collider->rect.x2, obj2_position.y + obj2_collider->rect.y2};
            circle = (Circle) {obj1_position.x + obj1_collider->circle.x, obj1_position.y + obj1_collider->circle.y,
                               obj1_collider->circle.radius};
        }

        return Collision_RectCircle(&rect, &circle);   /* Exit */
    }

    return false;
}

bool Collider_CheckObjectVector(GameObject *obj, Vector2f *vec) {
    if(obj == NULL) {
        DE_REPORT("Invalid object passed to collision system");
        return false;
    }

    Collider *c = OBJECT_GetComponent(obj, Collider);
    if(c == NULL) {
        DE_REPORT("Collider component not found in object: %s", obj->name);
        return false;
    }

    State2D *state = Object_GetComponent(obj, "State2D"); 
    if(state == NULL) {
        DE_REPORT("State component not found in object: %s", obj->name);
        return false;
    }

    Vector3f p = state->position;

    switch(c->type) {
        /* To do more. Done this one now just for mouse hovering */
        case COLLIDER_Rect: {
            PosRect rect = {p.x + c->rect.x1, p.y + c->rect.y1,
                            p.x + c->rect.x2, p.y + c->rect.y2};
            return Collision_VecRect(vec, &rect);
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