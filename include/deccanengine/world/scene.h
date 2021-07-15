/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "../core/utils.h"
#include "../core/string.h"
#include "../world/camera.h"
#include "object.h"
#include "scene_layer.h"

#define MAX_ADD_MODULES 16

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct deccan_scene_desc_t {
    const char *name;
    deccan_scenelayer_t *layers[MAX_ADD_MODULES];
} deccan_scene_desc_t;

typedef struct scenelayer_sys_t {
    zpl_array(deccan_scenelayer_t *) mods;
} scenelayer_sys_t;

typedef struct deccan_scene_t {
    char *name;
    bool is_paused;
    bool is_first_frame;

    ecs_world_t *world;
    deccan_camera_t *camera;

    cpSpace *physics_space;

    scenelayer_sys_t modsys;
} deccan_scene_t;

////////////////////////////////////////////////////////////////////////////////
// Constructor and destructor
////////////////////////////////////////////////////////////////////////////////

DE_API deccan_scene_t *deccan_scene_new_scene(deccan_scene_desc_t *info);

////////////////////////////////////////////////////////////////////////////////
// Layer systems
////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_scene_push_layer(deccan_scene_t *scene, deccan_scenelayer_t *mod);

////////////////////////////////////////////////////////////////////////////////
// Object handling
////////////////////////////////////////////////////////////////////////////////

DE_API deccan_object_t deccan_scene_instantiate_object(deccan_scene_t *scene, const char *name, deccan_object_t object);
DE_API deccan_object_t deccan_scene_get_object(deccan_scene_t *scene, const char *name);
DE_API void deccan_scene_iterate_object(deccan_scene_t *scene, void (*func)(deccan_object_t this));
DE_API void deccan_scene_iterate_object_of_type(deccan_scene_t *scene, const char *type, void (*func)(deccan_object_t this));

////////////////////////////////////////////////////////////////////////////////
// Scene status
////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_scene_pause_scene(deccan_scene_t *scene, bool pause);
DE_API bool deccan_scene_is_scene_paused(deccan_scene_t *scene);

DE_API void deccan_scene_set_camera(deccan_scene_t *scene, deccan_camera_t *camera);
DE_API deccan_camera_t *deccan_scene_get_camera(deccan_scene_t *scene);
