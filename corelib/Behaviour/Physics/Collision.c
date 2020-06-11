/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Collision.h"

/////////////////////////////////////////////////
// Collisions
////////////////////////////////////////////////

bool Collision_VecVec(Vector2 v1, Vector2 v2) {
    return v1.x == v2.x && 
           v1.y == v2.y;
}

bool Collision_RectRect(Rect r1, Rect r2) {
    return r1.x < r2.x + r2.w && 
           r1.x + r1.w > r2.x && 
           r1.y < r2.y + r2.h && 
           r1.y + r1.y > r2.y;
}

bool Collision_CircleCircle(Circle c1, Circle c2) {
    double distance = ((c1.x - c2.x) * (c1.x - c2.x)) + 
                      ((c1.y - c2.y) * (c1.y - c2.y));
    return distance < (c1.radius + c2.radius) * (c1.radius + c2.radius);
}

bool Collision_VecRect(Vector2 vec, Rect rect) {
    return vec.x > rect.x          && 
           vec.x < rect.x + rect.w && 
           vec.y > rect.y          && 
           vec.y < rect.y + rect.h;
}

bool Collision_CircleVec(Circle circle, Vector2 vec) {
    double distance = ((circle.x - vec.x) * (circle.x - vec.x)) + 
                      ((circle.y - vec.y) * (circle.y - vec.y));
    return distance < circle.radius * circle.radius;
}


bool Collision_RectCircle(Rect rect, Circle circle) {
    float cx, cy;     /* Closest X and Y of rect */
    
    /* Find the abscissa of nearest point to the abscissa center of circle */
    if(circle.x < rect.x) { cx = rect.x; }
    else if(circle.x > rect.x + rect.w) { cx = rect.x + rect.w; }
    else { cx = circle.x; }       /* Special case: the x coord of rect is same as x coord of center */

    /* Find the ordinate of nearest point to the ordinate center of circle */
    if(circle.y < rect.y) { cy = rect.y; }
    else if(circle.y > rect.y + rect.h) { cy = rect.y + rect.w; }
    else { cy = circle.y; }       /* Special case: the y coord of rect is same as y coord of center */

    double distance = ((cx - circle.x) * (cx - circle.x)) + 
                      ((cy - circle.y) * (cy - circle.y));
    return distance < circle.radius * circle.radius;
}