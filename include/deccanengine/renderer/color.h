/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"

////////////////////////////////////////////////////////////////////////////////
// Struct
////////////////////////////////////////////////////////////////////////////////

typedef union deccan_color_t {
    struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };
    float norm[4];
} deccan_color_t;

////////////////////////////////////////////////////////////////////////////////
// Color conversions
////////////////////////////////////////////////////////////////////////////////

DE_API deccan_color_t deccan_color_rgb_to_floats(deccan_color_t col);
DE_API deccan_color_t deccan_color_floats_to_rgb(deccan_color_t col);
