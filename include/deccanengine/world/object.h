/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"
#include "../core/utils.h"

////////////////////////////////////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////////////////////////////////////

typedef enum deccan_object_stage_t {
    DE_OBJECT_ATFIRSTFRAME,
    DE_OBJECT_ATBEGINNING,
    DE_OBJECT_ATSTEP,
    DE_OBJECT_ATRENDER,
    DE_OBJECT_ATEND,

    DE_OBJECT_STAGE_COUNT,
} deccan_object_stage_t;

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct deccan_object_t deccan_object_t;

typedef struct deccan_object_desc_t {
    const char *name;
    void (*cb[DE_OBJECT_STAGE_COUNT])(deccan_object_t);
} deccan_object_desc_t;

typedef struct deccan_object_info_t {
    bool visible;
    bool active;
    bool to_remove;

    bool is_beginning;

    void (*cb[DE_OBJECT_STAGE_COUNT])(deccan_object_t);
} deccan_object_info_t;

typedef struct deccan_object_t {
    ecs_entity_t entity;
} deccan_object_t;

////////////////////////////////////////////////////////////////////////////////
// Initialization and instantiator functions
////////////////////////////////////////////////////////////////////////////////

DE_API deccan_object_t deccan_object_new_object(deccan_object_desc_t *desc);
DE_API void deccan_object_delete_object(deccan_object_t obj);
DE_API void deccan_object_free_object(deccan_object_t obj);
DE_API bool deccan_object_is_valid(deccan_object_t obj);

////////////////////////////////////////////////////////////////////////////////
// Prefab and hierarchy functions
////////////////////////////////////////////////////////////////////////////////

DE_API deccan_object_t deccan_object_make_copy(deccan_object_t object);
DE_API void deccan_object_make_prefab(deccan_object_t object);
DE_API void deccan_object_set_parent(deccan_object_t object, deccan_object_t parent);
DE_API void deccan_object_add_child(deccan_object_t object, deccan_object_t child);

////////////////////////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_object_update(deccan_object_t obj);
DE_API void deccan_object_render(deccan_object_t obj);
DE_API void deccan_object_end(deccan_object_t obj);

////////////////////////////////////////////////////////////////////////////////
// Component
////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_object_set_component(deccan_object_t obj, const char *name, void *component);
DE_API void *deccan_object_get_component(deccan_object_t obj, const char *name);
DE_API void deccan_object_remove_component(deccan_object_t obj, const char *name);

DE_API void deccan_object_set_name(deccan_object_t obj, const char *name);
DE_API const char *deccan_object_get_name(deccan_object_t obj);

DE_API void deccan_object_set_tag(deccan_object_t obj, const char *name);
DE_API bool deccan_object_has_tag(deccan_object_t obj, const char *name);

DE_API deccan_object_info_t *deccan_object_get_info(deccan_object_t obj);

////////////////////////////////////////////////////////////////////////////////
// Getters and Setters
////////////////////////////////////////////////////////////////////////////////
DE_API bool deccan_object_is_hidden(deccan_object_t obj);
DE_API void deccan_object_hide(deccan_object_t obj, bool hide);

DE_API bool deccan_object_is_active(deccan_object_t obj);
DE_API void deccan_object_activate(deccan_object_t obj, bool act);
