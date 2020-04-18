/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "collision.h"

Deccan_Collider _priv_Collision_new_rect_collider(Deccan_PosRect rect) {
    Deccan_Collider coll;
    coll.type = Deccan_ColliderType_Rect;
    coll.rect = rect;
    return coll;
}

Deccan_Collider _priv_Collision_new_circle_collider(Deccan_Circle circle) {
    Deccan_Collider coll;
    coll.type = Deccan_ColliderType_Circle;
    coll.circle = circle;
    return coll;
}

bool _priv_Collision_test_vec(Deccan_GameObject *obj, Deccan_Vector2i vec) {
    switch(obj->collider.type) {
        case Deccan_ColliderType_Vec : {
            return obj->collider.vec.x == vec.x && obj->collider.vec.y == vec.y;
        }
        case Deccan_ColliderType_Rect: {
            int32_t x1 = obj->position.x + obj->collider.rect.x1;
            int32_t y1 = obj->position.y + obj->collider.rect.y1;
            int32_t x2 = x1 + obj->collider.rect.x2;
            int32_t y2 = y1 + obj->collider.rect.y2;

            return vec.x > x1 && vec.x < x2 && vec.y > y1 && vec.y < y2;
        }
        case Deccan_ColliderType_Circle: {
            int32_t x = obj->position.x + obj->collider.circle.x;
            int32_t y = obj->position.y + obj->collider.circle.y;
            
            double distance = sqrt(((x-vec.x)*(x-vec.x)) + ((y-vec.y)*(y-vec.y)));
            if(distance < obj->collider.circle.radius) { return true; }
        }
        default: { return false; }
    }
    return false;
}

bool _priv_Collision_test_object(Deccan_GameObject *obj1, Deccan_GameObject *obj2) {
    /* Possible cases where v = vector, r = rect and c = circle
        v <-> v      r <-> r      c <-> c
        v <-> r      c <-> v      r <-> c 
    */
    
    int type1 = obj1->collider.type;
    int type2 = obj2->collider.type;
    
    /* Matching cases */
    if(type1 == type2) {
        switch(type1) {
            case Deccan_ColliderType_Vec: {
                return obj1->collider.vec.x == obj2->collider.vec.x &&
                       obj1->collider.vec.y == obj2->collider.vec.y;
            }
            case Deccan_ColliderType_Rect: { /* To do */ }
            case Deccan_ColliderType_Circle: { /* To do */}
        }
    }

    /* Remaining cases */
    if(type1 == Deccan_ColliderType_Vec && type2 == Deccan_ColliderType_Vec) { }
    else if(type1 == Deccan_ColliderType_Circle && type2 == Deccan_ColliderType_Vec) { }
    else if(type1 == Deccan_ColliderType_Rect && type2 == Deccan_ColliderType_Circle) { }
}