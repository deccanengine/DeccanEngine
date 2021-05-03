/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "DefaultAssets.h"
#include "Resources/Sprite.h"
#include "../Core/Utils.h"

////////////////////////////////////////////////////////////////////////////////
// Default Asset Manager
////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_asset_manager_t *deccan_make_default_asset_manager(void) {
    deccan_asset_descriptor_t desc[] = {
        {
            .key = "texture",
            .calls.create = deccan_sprite_asset_create,
            .calls.destroy = deccan_sprite_asset_destroy,
        },
    };

    deccan_asset_manager_t *manager = deccan_alloc(sizeof(deccan_asset_manager_t), 1);
    deccan_asset_init_manager(manager, 1, desc);
    return manager;
}
