/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Physics.h"
#include "../../Scene/Object.h"

/////////////////////////////////////////////////
// Colliders
////////////////////////////////////////////////

/////////////////////////////////////////////////
// Collisions
////////////////////////////////////////////////

bool Collision_VecVec(Vector2f *v1, Vector2f *v2) {
    return v1->x == v2->x && v1->y == v2->y;
}

bool Collision_RectRect(PosRect *r1, PosRect *r2) {
    return r1->x1 < r2->x2 && r1->x2 > r2->x1 && r1->y1 < r2->y2 && r1->y2 > r2->y1;
}

bool Collision_CircleCircle(Circle *c1, Circle *c2) {
    double distance = ((c1->x-c2->x)*(c1->x-c2->x)) + ((c1->y-c2->y)*(c1->y-c2->y));
    return distance < (c1->radius+c2->radius)*(c1->radius+c2->radius);
}

bool Collision_VecRect(Vector2f *vec, PosRect *rect) {
    return vec->x > rect->x1 && vec->x < rect->x2 && vec->y > rect->y1 && vec->y < rect->y2;
}

bool Collision_CircleVec(Circle *circle, Vector2f *vec) {
    double distance = ((circle->x-vec->x)*(circle->x-vec->x)) + ((circle->y-vec->y)*(circle->y-vec->y));
    return distance < circle->radius*circle->radius;
}


bool Collision_RectCircle(PosRect *rect, Circle *circle) {
    float cx, cy;     /* Closest X and Y of rect */
    
    /* Find the abscissa of nearest point to the abscissa center of circle */
    if(circle->x < rect->x1) { cx = rect->x1; }
    else if(circle->x > rect->x2) { cx = rect->x2; }
    else { cx = circle->x; }       /* Special case: the x coord of rect is same as x coord of center */

    /* Find the ordinate of nearest point to the ordinate center of circle */
    if(circle->y < rect->y1) { cy = rect->y1; }
    else if(circle->y > rect->y2) { cy = rect->y2; }
    else { cy = circle->y; }       /* Special case: the y coord of rect is same as y coord of center */

    double distance = ((cx-circle->x)*(cx-circle->x)) + ((cy-circle->y)*(cy-circle->y));
    return distance < circle->radius*circle->radius;
}

bool Collision_ObjectObject(GameObject *obj1, GameObject *obj2) {
    /* Possible cases where v = vector, r = rect and c = circle
        v <-> v      r <-> r      c <-> c
        v <-> r      c <-> v      r <-> c 
    */
    if(obj1 == NULL || obj2 == NULL) {
        DE_REPORT("Invalid object(s) passed to collision system");
    }

    Position *obj1_position = OBJECT_GetComponent(obj1, Position);
    Collider *obj1_collider = OBJECT_GetComponent(obj1, Collider);
    
    Position *obj2_position = OBJECT_GetComponent(obj2, Position);
    Collider *obj2_collider = OBJECT_GetComponent(obj2, Collider);

    int type1 = obj1_collider->type;
    int type2 = obj2_collider->type;
    
    /* Matching cases */
    if(type1 == type2) {
        switch(type1) {
            /* Point collision i.e. v<->v */
            case ColliderVec: {
                Vector2f v1 = {obj1_position->x + obj1_collider->vec.x, obj1_position->y + obj1_collider->vec.y}; 
                Vector2f v2 = {obj2_position->x + obj2_collider->vec.x, obj2_position->y + obj2_collider->vec.y}; 
                
                return Collision_VecVec(&v1, &v2);    /* Exit */
            }

            /* AABB collision i.e. r<->r */
            case ColliderRect: { 
                PosRect r1 = {obj1_position->x + obj1_collider->rect.x1, obj1_position->y + obj1_collider->rect.y1,
                              obj1_position->x + obj1_collider->rect.x2, obj1_position->y + obj1_collider->rect.y2};
                PosRect r2 = {obj2_position->x + obj2_collider->rect.x1, obj2_position->y + obj2_collider->rect.y1,
                              obj2_position->x + obj2_collider->rect.x2, obj2_position->y + obj2_collider->rect.y2};

                return Collision_RectRect(&r1, &r2);    /* Exit */
            }

            /* Circle collision i.e. c<->c */
            case ColliderCircle: {
                Circle c1 = {obj1_position->x + obj1_collider->circle.x, obj1_position->y + obj1_collider->circle.y, obj1_collider->circle.radius};
                Circle c2 = {obj2_position->x + obj2_collider->circle.x, obj2_position->y + obj2_collider->circle.y, obj2_collider->circle.radius};

                return Collision_CircleCircle(&c1, &c2);  /* Exit */
            }
        }
    }

    /* Remaining cases */
    bool case_1 = (type1 == ColliderVec && type2 == ColliderRect);
    bool case_2 = (type1 == ColliderRect && type2 == ColliderVec);

    /* v<->r */
    if(case_1 || case_2) {
        Vector2f vec;
        PosRect  rect;

        /* v & r */
        if(case_1) {
            vec  = (Vector2f){obj1_position->x + obj1_collider->vec.x,   obj1_position->y + obj1_collider->vec.y};
            rect = (PosRect) {obj2_position->x + obj2_collider->rect.x1, obj2_position->y + obj2_collider->rect.y1,
                                     obj2_position->x + obj2_collider->rect.x2, obj2_position->y + obj2_collider->rect.y2};
        }
        /* r & v   */
        else {
            vec  = (Vector2f){obj2_position->x + obj2_collider->vec.x,   obj2_position->y + obj2_collider->vec.y};
            rect = (PosRect) {obj1_position->x + obj1_collider->rect.x1, obj1_position->y + obj1_collider->rect.y1,
                                     obj1_position->x + obj1_collider->rect.x2, obj1_position->y + obj1_collider->rect.y2};
        }

        return Collision_VecRect(&vec, &rect);    /* Exit */
    }

    bool case_3 = (type1 == ColliderCircle && type2 == ColliderVec);
    bool case_4 = (type1 == ColliderVec && type2 == ColliderCircle);

    /* c <-> v */
    if(case_3 || case_4) {
        Circle   circle;
        Vector2f vec;

        /* c & v */
        if(case_3) {
            vec    = (Vector2f){obj2_position->x + obj2_collider->vec.x, obj2_position->y + obj2_collider->vec.y};
            circle = (Circle)  {obj1_position->x + obj1_collider->circle.x, obj1_position->y + obj1_collider->circle.y, obj1_collider->circle.radius};
        }
        /* v & c */
        else {
            vec    = (Vector2f){obj1_position->x + obj1_collider->vec.x, obj1_position->y + obj1_collider->vec.y};
            circle = (Circle)  {obj2_position->x + obj2_collider->circle.x, obj2_position->y + obj2_collider->circle.y, obj2_collider->circle.radius};
        }
            
        return Collision_CircleVec(&circle, &vec);   /* Exit */
    }

    bool case_5 = (type1 == ColliderRect && type2 == ColliderCircle);
    bool case_6 = (type1 == ColliderCircle && type2 == ColliderRect);
    
    /* r <-> c */
    if(case_5 || case_6) {
        PosRect rect;
        Circle  circle;

        /* r & c */
        if(case_5) {
            rect   = (PosRect){obj1_position->x + obj1_collider->rect.x1, obj1_position->y + obj1_collider->rect.y1,
                                      obj1_position->x + obj1_collider->rect.x2, obj1_position->y + obj1_collider->rect.y2};
            circle = (Circle) {obj2_position->x + obj2_collider->circle.x, obj2_position->y + obj2_collider->circle.y,
                                      obj2_collider->circle.radius};
        }
        /* c & r */
        else {
            rect   = (PosRect){obj2_position->x + obj2_collider->rect.x1, obj2_position->y + obj2_collider->rect.y1,
                                      obj2_position->x + obj2_collider->rect.x2, obj2_position->y + obj2_collider->rect.y2};
            circle = (Circle) {obj1_position->x + obj1_collider->circle.x, obj1_position->y + obj1_collider->circle.y,
                                      obj1_collider->circle.radius};
        }

        return Collision_RectCircle(&rect, &circle);   /* Exit */
    }

    return false;
}

bool Collision_ObjectVec(GameObject *obj, Vector2f *vec) {
    if(obj == NULL) {
        DE_REPORT("Invalid object passed to collision system");
        return false;
    }

    Collider *c = OBJECT_GetComponent(obj, Collider);
    if(c == NULL) {
        DE_REPORT("Collider component not found in object: %s", obj->name);
        return false;
    }

    Position *p = OBJECT_GetComponent(obj, Position);
    if(p == NULL) {
        DE_REPORT("Collider component not found in object: %s", obj->name);
        return false;
    }

    switch(c->type) {
        /* To do more. Done this one now just for mouse hovering */
        case ColliderRect: {
            PosRect rect = {p->x + c->rect.x1, p->y + c->rect.y1,
                            p->x + c->rect.x2, p->y + c->rect.y2};
            return Collision_VecRect(vec, &rect);
        }
        default: {
            return false;
        }
    }
}

bool Collision_Test(const char *name1, const char *name2) {
    GameObject *obj1 = Object_GetObject(name1);
    GameObject *obj2 = Object_GetObject(name2);
    return Collision_ObjectObject(obj1, obj2);
}