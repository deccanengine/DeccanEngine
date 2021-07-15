/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <deccanengine/world/scene_layer.h>
#include <deccanengine/core/utils.h>

////////////////////////////////////////////////////////////////////////////////
// Module
////////////////////////////////////////////////////////////////////////////////

DE_PRIV void module_none_func() { }

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_scenelayer_t *deccan_scenelayer_create(deccan_scenelayer_desc_t *info) {
    deccan_scenelayer_t *mod = deccan_alloc(sizeof(deccan_scenelayer_t), 1);

    for (int i = 0; i < DE_SCENE_LAYER_STAGE_COUNT; i += 1) {
        mod->cb[i] = info->cb[i] != NULL ? info->cb[i] : module_none_func;
    }

    return mod;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_scenelayer_destroy(deccan_scenelayer_t *mod) {
    deccan_free(mod);
}
