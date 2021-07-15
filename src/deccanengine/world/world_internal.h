/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include <deccanengine/config.h>

////////////////////////////////////////////////////////////////////////////////
// World internals
////////////////////////////////////////////////////////////////////////////////

void world_create(void);
void world_free_all_scene(void);
void world_make_scene_changes(void);
void world_update(void);
void world_quit_scene(void);
