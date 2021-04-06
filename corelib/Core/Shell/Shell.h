/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../../Config.h"
#include "../Array.h"

/////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////

typedef enum DeccanShellStage {
    DE_SHELL_ATBEGINNING,
    DE_SHELL_ATSTEP,
    DE_SHELL_ATPOSTSTEP,
    DE_SHELL_ATEND
} DeccanShellStage;

/////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////

typedef struct DeccanShell {
    void (*AtBeginning)();
    void (*AtStep)();
    void (*AtPostStep)();
    void (*AtEnd)();
} DeccanShell;

typedef struct DeccanShellSys {
    DeccanArray shells;
} DeccanShellSys;

/////////////////////////////////////////////////
// Shell
////////////////////////////////////////////////

DE_API DeccanShell *DE_ShellCreate(const char *name);
DE_API void DE_ShellDestroy(DeccanShell *shell);

/////////////////////////////////////////////////
// Shell System
////////////////////////////////////////////////

DE_API void DE_ShellSysCreate(DeccanShellSys *shsys);
DE_API void DE_ShellSysDestroy(DeccanShellSys *shsys);
DE_API void DE_ShellSysPush(DeccanShellSys *shsys, DeccanShell *shell);
DE_API void DE_ShellSysIter(DeccanShellSys *shsys, DeccanShellStage stage, bool order);
