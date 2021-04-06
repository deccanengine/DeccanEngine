/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Shell.h"
#include "../Utils.h"

/////////////////////////////////////////////////
// Shell
////////////////////////////////////////////////

DE_PRIV void NullFunction() {
}

DE_IMPL DeccanShell *DE_ShellCreate(const char *name) {
    DeccanShell *shell = DE_Alloc(sizeof(DeccanShell), 1);
    shell->AtBeginning = NullFunction;
    shell->AtStep = NullFunction;
    shell->AtPostStep = NullFunction;
    shell->AtEnd = NullFunction;
    return shell;
}

DE_IMPL void DE_ShellDestroy(DeccanShell *shell) {
    DE_Free(shell);
}

/////////////////////////////////////////////////
// Shell System
////////////////////////////////////////////////

DE_IMPL void DE_ShellSysCreate(DeccanShellSys *shsys) {
    DE_ArrayCreate(&shsys->shells);
}

DE_IMPL void DE_ShellSysDestroy(DeccanShellSys *shsys) {
    for (int i = 0; i < shsys->shells.length; i += 1) {
        DE_ShellDestroy((DeccanShell *)&shsys->shells.data[i]);
    }

    DE_ArrayDestroy(&shsys->shells);
}

DE_IMPL void DE_ShellSysPush(DeccanShellSys *shsys, DeccanShell *shell) {
    DE_ArrayAddItem(&shsys->shells, (void *)shell);
}

DE_PRIV void ShellStage(DeccanShell *shell, DeccanShellStage stage) {
    switch (stage) {
    case DE_SHELL_ATBEGINNING: shell->AtBeginning(); break;
    case DE_SHELL_ATSTEP: shell->AtStep(); break;
    case DE_SHELL_ATPOSTSTEP: shell->AtPostStep(); break;
    case DE_SHELL_ATEND: shell->AtEnd(); break;
    default: break; /* Huh? */
    }
}

DE_IMPL void DE_ShellSysIter(DeccanShellSys *shsys, DeccanShellStage stage, bool order) {
    if (order) {
        for (int i = 0; i < shsys->shells.length; i += 1) {
            ShellStage((DeccanShell *)shsys->shells.data[i], stage);
        }
    }
    else {
        for (int i = shsys->shells.length - 1; i >= 0; i -= 1) {
            ShellStage((DeccanShell *)shsys->shells.data[i], stage);
        }
    }
}
