/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "collision.h"

Deccan_Collider _priv_Collision_new_rect_collider(Deccan_PosRect rect) {
    Deccan_Collider coll;
    coll.type = ColliderRect;
    coll.rect = rect;
    return coll;
}

Deccan_Collider _priv_Collision_new_circle_collider(Deccan_Circle circle) {
    Deccan_Collider coll;
    coll.type = ColliderCircle;
    coll.circle = circle;
    return coll;
}

bool _priv_Collision_test_vec_vec_from(Deccan_Vector2i *v1, Deccan_Vector2i *v2) {
    return v1->x == v2->x && v1->y == v2->y;
}

bool _priv_Collision_test_rect_rect_from(Deccan_PosRect *r1, Deccan_PosRect *r2) {
    return r1->x1 < r2->x2 && r1->x2 > r2->x1 && r1->y1 < r2->y2 && r1->y2 > r2->y1;
}

bool _priv_Collision_test_circle_circle_from(Deccan_Circle *c1, Deccan_Circle *c2) {
    int64_t distance = ((c1->x-c2->x)*(c1->x-c2->x)) + ((c1->y-c2->y)*(c1->y-c2->y));
    return distance < (c1->radius+c2->radius)*(c1->radius+c2->radius);
}

bool _priv_Collision_test_vec_rect_from(Deccan_Vector2i *vec, Deccan_PosRect *rect) {
    return vec->x > rect->x1 && vec->x < rect->x2 && vec->y > rect->y1 && vec->y < rect->y2;
}

bool _priv_Collision_test_circle_vec_from(Deccan_Circle *circle, Deccan_Vector2i *vec) {
    int64_t distance = ((circle->x-vec->x)*(circle->x-vec->x)) + ((circle->y-vec->y)*(circle->y-vec->y));
    return distance < circle->radius*circle->radius;
}


bool _priv_Collision_test_rect_circle_from(Deccan_PosRect *rect, Deccan_Circle *circle) {
    int32_t cx, cy;     /* Closest X and Y of rect */
    
    /* Find the abscissa of nearest point to the abscissa center of circle */
    if(circle->x < rect->x1) { cx = rect->x1; }
    else if(circle->x > rect->x2) { cx = rect->x2; }
    else { cx = circle->x; }       /* Special case: the x coord of rect is same as x coord of center */

    /* Find the ordinate of nearest point to the ordinate center of circle */
    if(circle->y < rect->y1) { cy = rect->y1; }
    else if(circle->y > rect->y2) { cy = rect->y2; }
    else { cy = circle->y; }       /* Special case: the y coord of rect is same as y coord of center */

    int64_t distance = ((cx-circle->x)*(cx-circle->x)) + ((cy-circle->y)*(cy-circle->y));
    return distance < circle->radius*circle->radius;
}

bool _priv_Collision_test_from(Deccan_GameObject *obj1, Deccan_GameObject *obj2) {
    /* Possible cases where v = vector, r = rect and c = circle
        v <-> v      r <-> r      c <-> c
        v <-> r      c <-> v      r <-> c 
    */
    if(obj1 == NULL || obj2 == NULL) {
        DE_report("Invalid object(s) passed to collision system");
    }
    
    int type1 = obj1->collider.type;
    int type2 = obj2->collider.type;
    
    /* Matching cases */
    if(type1 == type2) {
        switch(type1) {
            /* Point collision i.e. v<->v */
            case ColliderVec: {
                Deccan_Vector2i v1 = {obj1->position.x + obj1->collider.vec.x, obj1->position.y + obj1->collider.vec.y}; 
                Deccan_Vector2i v2 = {obj2->position.x + obj2->collider.vec.x, obj2->position.y + obj2->collider.vec.y}; 
                
                return _priv_Collision_test_vec_vec_from(&v1, &v2);    /* Exit */
            }

            /* AABB collision i.e. r<->r */
            case ColliderRect: { 
                Deccan_PosRect r1 = {obj1->position.x + obj1->collider.rect.x1, obj1->position.y + obj1->collider.rect.y1,
                                     obj1->position.x + obj1->collider.rect.x2, obj1->position.y + obj1->collider.rect.y2};
                Deccan_PosRect r2 = {obj2->position.x + obj2->collider.rect.x1, obj2->position.y + obj2->collider.rect.y1,
                                     obj2->position.x + obj2->collider.rect.x2, obj2->position.y + obj2->collider.rect.y2};

                return _priv_Collision_test_rect_rect_from(&r1, &r2);    /* Exit */
            }

            /* Circle collision i.e. c<->c */
            case ColliderCircle: {
                Deccan_Circle c1 = {obj1->position.x + obj1->collider.circle.x, obj1->position.y + obj1->collider.circle.y, obj1->collider.circle.radius};
                Deccan_Circle c2 = {obj2->position.x + obj2->collider.circle.x, obj2->position.y + obj2->collider.circle.y, obj2->collider.circle.radius};

                return _priv_Collision_test_circle_circle_from(&c1, &c2);  /* Exit */
            }
        }
    }

    /* Remaining cases */
    bool case_1 = (type1 == ColliderVec && type2 == ColliderRect);
    bool case_2 = (type1 == ColliderRect && type2 == ColliderVec);

    /* v<->r */
    if(case_1 || case_2) {
        Deccan_Vector2i vec;
        Deccan_PosRect  rect;

        /* v & r */
        if(case_1) {
            vec  = (Deccan_Vector2i){obj1->position.x + obj1->collider.vec.x,   obj1->position.y + obj1->collider.vec.y};
            rect = (Deccan_PosRect) {obj2->position.x + obj2->collider.rect.x1, obj2->position.y + obj2->collider.rect.y1,
                                     obj2->position.x + obj2->collider.rect.x2, obj2->position.y + obj2->collider.rect.y2};
        }
        /* r & v   */
        else {
            vec  = (Deccan_Vector2i){obj2->position.x + obj2->collider.vec.x,   obj2->position.y + obj2->collider.vec.y};
            rect = (Deccan_PosRect) {obj1->position.x + obj1->collider.rect.x1, obj1->position.y + obj1->collider.rect.y1,
                                     obj1->position.x + obj1->collider.rect.x2, obj1->position.y + obj1->collider.rect.y2};
        }

        return _priv_Collision_test_vec_rect_from(&vec, &rect);    /* Exit */
    }

    bool case_3 = (type1 == ColliderCircle && type2 == ColliderVec);
    bool case_4 = (type1 == ColliderVec && type2 == ColliderCircle);

    /* c <-> v */
    if(case_3 || case_4) {
        Deccan_Circle   circle;
        Deccan_Vector2i vec;

        /* c & v */
        if(case_3) {
            vec    = (Deccan_Vector2i){obj2->position.x + obj2->collider.vec.x, obj2->position.y + obj2->collider.vec.y};
            circle = (Deccan_Circle)  {obj1->position.x + obj1->collider.circle.x, obj1->position.y + obj1->collider.circle.y, obj1->collider.circle.radius};
        }
        /* v & c */
        else {
            vec    = (Deccan_Vector2i){obj1->position.x + obj1->collider.vec.x, obj1->position.y + obj1->collider.vec.y};
            circle = (Deccan_Circle)  {obj2->position.x + obj2->collider.circle.x, obj2->position.y + obj2->collider.circle.y, obj2->collider.circle.radius};
        }
            
        return _priv_Collision_test_circle_vec_from(&circle, &vec);   /* Exit */
    }

    bool case_5 = (type1 == ColliderRect && type2 == ColliderCircle);
    bool case_6 = (type1 == ColliderCircle && type2 == ColliderRect);
    
    /* r <-> c */
    if(case_5 || case_6) {
        Deccan_PosRect rect;
        Deccan_Circle  circle;

        /* r & c */
        if(case_5) {
            rect   = (Deccan_PosRect){obj1->position.x + obj1->collider.rect.x1, obj1->position.y + obj1->collider.rect.y1,
                                      obj1->position.x + obj1->collider.rect.x2, obj1->position.y + obj1->collider.rect.y2};
            circle = (Deccan_Circle) {obj2->position.x + obj2->collider.circle.x, obj2->position.y + obj2->collider.circle.y,
                                      obj2->collider.circle.radius};
        }
        /* c & r */
        else {
            rect   = (Deccan_PosRect){obj2->position.x + obj2->collider.rect.x1, obj2->position.y + obj2->collider.rect.y1,
                                      obj2->position.x + obj2->collider.rect.x2, obj2->position.y + obj2->collider.rect.y2};
            circle = (Deccan_Circle) {obj1->position.x + obj1->collider.circle.x, obj1->position.y + obj1->collider.circle.y,
                                      obj1->collider.circle.radius};
        }

        return _priv_Collision_test_rect_circle_from(&rect, &circle);   /* Exit */
    }

    return false;
}

bool _priv_Collision_test_vec_from(Deccan_GameObject *obj, Deccan_Vector2i *vec) {
    if(obj == NULL) {
        DE_report("Invalid object passed to collision system");
    }

    switch(obj->collider.type) {
        /* To do more. Done this one now just for mouse hovering */
        case ColliderRect: {
            Deccan_PosRect rect = {obj->position.x + obj->collider.rect.x1, obj->position.y + obj->collider.rect.y1,
                                   obj->position.x + obj->collider.rect.x2, obj->position.y + obj->collider.rect.y2};
            return _priv_Collision_test_vec_rect_from(vec, &rect);
        }
    }
}

bool _priv_Collision_test(const char *name1, const char *name2) {
    Deccan_GameObject *obj1 = Deccan_Object.get_object(name1);
    Deccan_GameObject *obj2 = Deccan_Object.get_object(name2);
    return Deccan_Collision.test_from(obj1, obj2);
}