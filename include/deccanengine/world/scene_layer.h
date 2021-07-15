/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"

////////////////////////////////////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////////////////////////////////////

typedef enum deccan_scenelayer_stage_t {
    DE_SCENE_LAYER_ATBEGINNING,
    DE_SCENE_LAYER_ATSTEP,
    DE_SCENE_LAYER_ATPOSTSTEP,
    DE_SCENE_LAYER_ATEND,

    DE_SCENE_LAYER_STAGE_COUNT,
} deccan_scenelayer_stage_t;

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct deccan_scene_t deccan_scene_t;

typedef struct deccan_scenelayer_desc_t {
    const char *name;
    void (*cb[DE_SCENE_LAYER_STAGE_COUNT])(deccan_scene_t *);
} deccan_scenelayer_desc_t;

typedef struct deccan_scenelayer_t {
    void (*cb[DE_SCENE_LAYER_STAGE_COUNT])(deccan_scene_t *);
} deccan_scenelayer_t;

////////////////////////////////////////////////////////////////////////////////
// Module
////////////////////////////////////////////////////////////////////////////////

DE_API deccan_scenelayer_t *deccan_scenelayer_create(deccan_scenelayer_desc_t *info);
DE_API void deccan_scenelayer_destroy(deccan_scenelayer_t *mod);
