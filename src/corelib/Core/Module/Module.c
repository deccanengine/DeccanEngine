/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Module.h"
#include "../Utils.h"

////////////////////////////////////////////////////////////////////////////////
// Module
////////////////////////////////////////////////////////////////////////////////

DE_PRIV void module_none_func() { }

////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_module_t *deccan_module_create(const char *name) {
    deccan_module_t *mod = deccan_alloc(sizeof(deccan_module_t), 1);
    mod->at_beginning = module_none_func;
    mod->at_step = module_none_func;
    mod->at_post_step = module_none_func;
    mod->at_end = module_none_func;
    return mod;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_module_destroy(deccan_module_t *mod) {
    deccan_free(mod);
}

////////////////////////////////////////////////////////////////////////////////
// Module System
////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_module_sys_create(deccan_module_sys_t *modsys) {
    zpl_array_init(modsys->mods, deccan_z_p_l_allocator());
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_module_sys_destroy(deccan_module_sys_t *modsys) {
    for (int i = 0; i < zpl_array_count(modsys->mods); i += 1) {
        deccan_module_destroy(modsys->mods[i]);
    }

    zpl_array_free(modsys->mods);
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_module_sys_push(deccan_module_sys_t *modsys, deccan_module_t *mod) {
    zpl_array_append(modsys->mods, mod);
}

////////////////////////////////////////////////////////////////////////////////

DE_PRIV void module_stage(deccan_module_t *mod, deccan_module_stage_t stage) {
    switch (stage) {
    case DE_SHELL_ATBEGINNING: mod->at_beginning(); break;
    case DE_SHELL_ATSTEP: mod->at_step(); break;
    case DE_SHELL_ATPOSTSTEP: mod->at_post_step(); break;
    case DE_SHELL_ATEND: mod->at_end(); break;
    default: break; /* Huh? */
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_module_sys_iter(deccan_module_sys_t *modsys, deccan_module_stage_t stage, bool order) {
    if (order) {
        for (int i = 0; i < zpl_array_count(modsys->mods); i += 1) {
            module_stage(modsys->mods[i], stage);
        }
    }
    else {
        for (int i = zpl_array_count(modsys->mods) - 1; i >= 0; i -= 1) {
            module_stage(modsys->mods[i], stage);
        }
    }
}
