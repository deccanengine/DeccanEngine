#include "collision.h"

Deccan_Collider _priv_Collision_new_rect_collider(Deccan_Rect rect) {
    Deccan_Collider coll;
    coll.type = Collider_Rect;
    coll.rect = rect;
    return coll;
}

bool _priv_Collision_check_rect_vec(Deccan_Rect rect, Deccan_Vector2i vec) {
    bool are_colliding = false;

    if(vec.x > rect.x && vec.x < rect.x+rect.w) {
       if(vec.y > rect.y && vec.y < rect.y+rect.h) { are_colliding = true; } 
    }

    return are_colliding;
}