/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once

#include "../Config.h"
#include "Components/Collider.h"
#include "Components/Transform.h"
#include "Components/DrawableGeometry.h"
#include "Components/DrawableSprite.h"

////////////////////////////////////////////////////////////////////////////////
// Registrar
////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_components_register_all(void);
