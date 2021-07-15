/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "scene.h"

////////////////////////////////////////////////////////////////////////////////
// Scene internals
////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_world_add_scene(deccan_scene_t *scene, bool is_replacing);
DE_API void deccan_world_remove_scene(void);

DE_API int deccan_world_get_scene_count(void);
DE_API deccan_scene_t *deccan_world_get_current_scene(void);
