/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <deccanengine/core/utils.h>

#include "../renderer/primitive_geometry.h"
#include "default_assets.h"
#include "resources/sprite.h"
#include "resources/geometry.h"

#include "logo.h"

////////////////////////////////////////////////////////////////////////////////
// Default Asset Manager
////////////////////////////////////////////////////////////////////////////////

deccan_asset_manager_t make_default_asset_manager(void) {
    deccan_asset_descriptor_t desc[] = {
        {
            .key = "texture",
            .calls.create = sprite_asset_create,
            .calls.destroy = sprite_asset_destroy,
        },
        {
            .key = "geometry",
            .calls.create = geometry_create,
            .calls.destroy = geometry_destroy,
        },
    };

    deccan_asset_manager_t manager;
    deccan_asset_init_manager(&manager, 2, desc);
    return manager;
}

void load_default_assets(void) {
    deccan_asset_load_from_mem("texture", "_logo_internal", sizeof(logo_internal), logo_internal);

    deccan_asset_load_premade("geometry", "quad", primitive_create_quad());
    deccan_asset_load_premade("geometry", "triangle", primitive_create_triangle());
    deccan_asset_load_premade("geometry", "cube", primitive_create_cube());
}
