/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once

typedef struct DE_Rect {
    float x, y, w, h;
} DE_Rect;

typedef struct DE_PosRect {
    float x1, y1, x2, y2;
} DE_PosRect;

typedef struct DE_Circle {
    float x, y, radius;
} DE_Circle;