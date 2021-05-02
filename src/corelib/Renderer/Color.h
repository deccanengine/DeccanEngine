/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"

////////////////////////////////////////////////////////////////////////////////
// Struct
////////////////////////////////////////////////////////////////////////////////

typedef union DeccanColor {
    struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };
    float norm[4];
} DeccanColor;

////////////////////////////////////////////////////////////////////////////////
// Color conversions
////////////////////////////////////////////////////////////////////////////////

DE_API DeccanColor DE_ColorRBGToFloats(DeccanColor col);
DE_API DeccanColor DE_ColorFloatsToRBG(DeccanColor col);
