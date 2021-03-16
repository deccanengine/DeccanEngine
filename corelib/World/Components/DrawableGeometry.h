/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../Config.h"
#include "../../Renderer/RenderTypes.h"

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct DeccanCompDrawableGeometry {
    DeccanGeometry geometry;
} DeccanCompDrawableGeometry;

/////////////////////////////////////////////////
// Registers/Constructors/Destructors
////////////////////////////////////////////////

void DE_CompDrawableGeometryRegister(void);
