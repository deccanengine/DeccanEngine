/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once

typedef struct Deccan_Rect {
    int32_t x, y, w, h;
} Deccan_Rect;

typedef struct Deccan_PosRect {
    int32_t x1, y1, x2, y2;
} Deccan_PosRect;

typedef struct Deccan_Circle {
    int32_t x, y, radius;
} Deccan_Circle;