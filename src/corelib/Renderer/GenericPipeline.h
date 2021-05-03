/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "PrimitiveGeometry.h"
#include "RenderTypes.h"
#include "../World/Camera.h"

////////////////////////////////////////////////////////////////////////////////
// Pipeline constructor/destructor
////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_generic_pipeline_create(void);
DE_API void deccan_generic_pipeline_destroy(void);

////////////////////////////////////////////////////////////////////////////////
// Pipeline action
////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_generic_pipeline_begin(deccan_camera_t *camera);
DE_API void deccan_generic_pipeline_draw(deccan_draw_action_t action);
DE_API void deccan_generic_pipeline_end(void);
