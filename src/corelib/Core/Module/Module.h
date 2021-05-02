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

typedef enum DeccanModuleStage {
    DE_SHELL_ATBEGINNING,
    DE_SHELL_ATSTEP,
    DE_SHELL_ATPOSTSTEP,
    DE_SHELL_ATEND
} DeccanModuleStage;

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct DeccanModule {
    void (*AtBeginning)();
    void (*AtStep)();
    void (*AtPostStep)();
    void (*AtEnd)();
} DeccanModule;

typedef struct DeccanModuleSys {
    zpl_array(DeccanModule *) mods;
} DeccanModuleSys;

////////////////////////////////////////////////////////////////////////////////
// Module
////////////////////////////////////////////////////////////////////////////////

DE_API DeccanModule *DE_ModuleCreate(const char *name);
DE_API void DE_ModuleDestroy(DeccanModule *mod);

////////////////////////////////////////////////////////////////////////////////
// Module System
////////////////////////////////////////////////////////////////////////////////

DE_API void DE_ModuleSysCreate(DeccanModuleSys *modsys);
DE_API void DE_ModuleSysDestroy(DeccanModuleSys *modsys);
DE_API void DE_ModuleSysPush(DeccanModuleSys *modsys, DeccanModule *mod);
DE_API void DE_ModuleSysIter(DeccanModuleSys *modsys, DeccanModuleStage stage, bool order);
