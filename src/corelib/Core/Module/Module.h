/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../Config.h"

////////////////////////////////////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////////////////////////////////////

typedef enum deccan_module_stage_t {
    DE_SHELL_ATBEGINNING,
    DE_SHELL_ATSTEP,
    DE_SHELL_ATPOSTSTEP,
    DE_SHELL_ATEND
} deccan_module_stage_t;

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct deccan_module_t {
    void (*AtBeginning)();
    void (*AtStep)();
    void (*AtPostStep)();
    void (*AtEnd)();
} deccan_module_t;

typedef struct deccan_module_sys_t {
    zpl_array(deccan_module_t *) mods;
} deccan_module_sys_t;

////////////////////////////////////////////////////////////////////////////////
// Module
////////////////////////////////////////////////////////////////////////////////

DE_API deccan_module_t *deccan_module_create(const char *name);
DE_API void deccan_module_destroy(deccan_module_t *mod);

////////////////////////////////////////////////////////////////////////////////
// Module System
////////////////////////////////////////////////////////////////////////////////

DE_API void deccan_module_sys_create(deccan_module_sys_t *modsys);
DE_API void deccan_module_sys_destroy(deccan_module_sys_t *modsys);
DE_API void deccan_module_sys_push(deccan_module_sys_t *modsys, deccan_module_t *mod);
DE_API void deccan_module_sys_iter(deccan_module_sys_t *modsys, deccan_module_stage_t stage, bool order);
