#pragma once
#include "../config.h"
#include "rect.h"
#include "../utils/vector.h"

enum {
    Collider_Rect
};

typedef struct Deccan_Collider {
    int type;
    union {
        struct { Deccan_Rect rect; };
    };
} Deccan_Collider;

Deccan_Collider _priv_Collision_new_rect_collider(Deccan_Rect rect);
bool _priv_Collision_check_rect_vec(Deccan_Rect rect, Deccan_Vector2i vec);

#ifdef __STDC__
    typedef struct _priv_Collision {
        Deccan_Collider (*new_rect_collider)(Deccan_Rect rect);
        bool (*check_rect_vec)(Deccan_Rect rect, Deccan_Vector2i vec);
    } _priv_Collision;

    static _priv_Collision Deccan_Collision = { 
        _priv_Collision_new_rect_collider,
        _priv_Collision_check_rect_vec
    };
#elif __cplusplus

#endif