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

bool _priv_Collision_test_vec(Deccan_GameObject *obj, Deccan_Vector2i vec) {
    switch(obj->collider.type) {
        case Deccan_ColliderType_Rect: {
            int32_t x1 = obj->position.x + obj->collider.rect.x1;
            int32_t y1 = obj->position.y + obj->collider.rect.y1;
            int32_t x2 = x1 + obj->collider.rect.x2;
            int32_t y2 = y1 + obj->collider.rect.y2;

            if(vec.x > x1 && vec.x < x2 && vec.y > y1 && vec.y < y2) { return true; }
            break;
        }
    }
    return false;
}