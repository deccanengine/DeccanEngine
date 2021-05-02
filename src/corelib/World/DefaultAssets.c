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

DE_IMPL DeccanAssetManager *DE_MakeDefaultAssetManager(void) {
    DeccanAssetDescriptor desc[] = {
        {
            .key = "texture",
            .calls.Create = DE_SpriteAssetCreate,
            .calls.Destroy = DE_SpriteAssetDestroy,
        },
    };

    DeccanAssetManager *manager = DE_Alloc(sizeof(DeccanAssetManager), 1);
    DE_AssetInitManager(manager, 1, desc);
    return manager;
}
