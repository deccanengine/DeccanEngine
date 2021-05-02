/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "../Core/Module/Module.h"
#include "../Core/Utils.h"
#include "../Core/String.h"
#include "../World/Camera.h"
#include "Object.h"

////////////////////////////////////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct deccan_game_scene_t {
    char *name;
    bool is_paused;
    bool is_first_frame;

    ecs_world_t *world;
    deccan_camera_t *camera;

    deccan_module_sys_t modsys;
} deccan_game_scene_t;

////////////////////////////////////////////////////////////////////////////////
// Scene internals
////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_scene_sys_create(void);
DE_API deccan_game_scene_t **deccan_scene_get_scene_array(void);
DE_API int deccan_scene_get_scene_count(void);
DE_API void deccan_scene_free_all(void);
DE_API void deccan_scene_update(void);
DE_API void deccan_scene_quit(void);

////////////////////////////////////////////////////////////////////////////////
// Constructor and destructor
////////////////////////////////////////////////////////////////////////////////

DE_API deccan_game_scene_t *deccan_scene_new_scene(const char *name);
DE_API void deccan_scene_add_scene(deccan_game_scene_t *scene, bool is_replacing);
DE_API void deccan_scene_remove_scene(void);
DE_API void deccan_scene_make_changes(void);

////////////////////////////////////////////////////////////////////////////////
// Module systems
////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_scene_push_module(deccan_game_scene_t *scene, deccan_module_t *mod);

////////////////////////////////////////////////////////////////////////////////
// Object handling
////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_scene_instantiate_object(deccan_game_object_t object);
DE_API deccan_game_object_t deccan_scene_get_object(const char *name);
DE_API void deccan_scene_iterate_object(void (*func)(deccan_game_object_t this));
DE_API void deccan_scene_iterate_object_of_type(const char *type, void (*func)(deccan_game_object_t this));

////////////////////////////////////////////////////////////////////////////////
// Scene status
////////////////////////////////////////////////////////////////////////////////

DE_API deccan_game_scene_t *deccan_scene_current_scene(void);
DE_API void deccan_scene_pause_scene(bool pause);
DE_API bool deccan_scene_is_scene_paused(void);

DE_API void deccan_scene_set_camera(deccan_camera_t *camera);
DE_API deccan_camera_t *deccan_scene_get_camera(void);
