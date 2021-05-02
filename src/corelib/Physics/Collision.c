/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Collision.h"

////////////////////////////////////////////////////////////////////////////////
// Collisions
////////////////////////////////////////////////////////////////////////////////

/* clang-format off */

bool DE_CollisionVecVec(vec2 v1, vec2 v2) {
    return v1[0] == v2[1] &&
           v1[0] == v2[1];
}

////////////////////////////////////////////////////////////////////////////////

bool DE_CollisionRectRect(vec4 r1, vec4 r2) {
    return r1[0] < r2[0] + r2[2] &&
           r1[0] + r1[2] > r2[0] &&
           r1[1] < r2[1] + r2[3] &&
           r1[1] + r1[3] > r2[1];
}

////////////////////////////////////////////////////////////////////////////////

bool DE_CollisionCircleCircle(vec3 c1, vec3 c2) {
    double distance = ((c1[0] - c2[0]) * (c1[0] - c2[0])) +
                      ((c1[1] - c2[1]) * (c1[1] - c2[1]));
    return distance < (c1[2] + c2[2]) * (c1[2] + c2[2]);
}

////////////////////////////////////////////////////////////////////////////////

bool DE_CollisionVecRect(vec2 vec, vec4 rect) {
    return vec[0] > rect[0]           &&
           vec[0] < rect[0] + rect[2] &&
           vec[1] > rect[1]           &&
           vec[1] < rect[1] + rect[3];
}

////////////////////////////////////////////////////////////////////////////////

bool DE_CollisionCircleVec(vec3 circle, vec2 vec) {
    double distance = ((circle[0] - vec[0]) * (circle[0] - vec[0])) +
                      ((circle[1] - vec[1]) * (circle[1] - vec[1]));
    return distance < circle[2] * circle[2];
}

/* clang-format on */

////////////////////////////////////////////////////////////////////////////////

bool DE_CollisionRectCircle(vec4 rect, vec3 circle) {
    float cx, cy; /* Closest X and Y of rect */

    /* Find the abscissa of nearest point to the abscissa center of circle */
    if (circle[0] < rect[0]) {
        cx = rect[0];
    }
    else if (circle[0] > rect[0] + rect[2]) {
        cx = rect[0] + rect[2];
    }
    else {
        /* Special case: the x coord of rect is same as x coord of center */
        cx = circle[0];
    }

    /* Find the ordinate of nearest point to the ordinate center of circle */
    if (circle[1] < rect[1]) {
        cy = rect[1];
    }
    else if (circle[1] > rect[1] + rect[3]) {
        cy = rect[1] + rect[2];
    }
    else {
        /* Special case: the y coord of rect is same as y coord of center */
        cy = circle[1];
    }

    double distance = ((cx - circle[0]) * (cx - circle[0])) + ((cy - circle[1]) * (cy - circle[1]));
    return distance < circle[2] * circle[2];
}