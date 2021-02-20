/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Variable.h"

void DE_VarInit(DeccanVarManager *manager) {
    manager->vars = NULL;
}

void DE_VarQuit(DeccanVarManager *manager) {
    for(int i = 0; i < stbds_shlen(manager->vars); i++) {
        DeccanVar *var = manager->vars[i].value;

        if(var->type == DECCAN_VARTYPE_STRING) {
            DE_Free(var->value.string);
        }

        DE_Free(var);
    }

    stbds_shfree(manager->vars);
}

void DE_VarNew(DeccanVarManager *manager, const char *name, DeccanVarType type) {
    DeccanVar *var = DE_Alloc(sizeof(DeccanVar), 1);
    var->type = type;

    stbds_shput(manager->vars, name, var);
}

void DE_VarDelete(DeccanVarManager *manager, const char *name) {
    DeccanVar *var = stbds_shget(manager->vars, name);
    if(var->type == DECCAN_VARTYPE_STRING) {
        if(var->value.string != NULL) {
            free(var->value.string);
            var->value.string = NULL;
        }
    }

    stbds_shdel(manager->vars, name);

    free(var);
    var = NULL;
}

void DE_VarSetBool(DeccanVarManager *manager, const char *name, bool value) {
    DeccanVar *var = stbds_shget(manager->vars, name);
    if(var->type == DECCAN_VARTYPE_LOGICAL) {
        var->value.logical = value;
    }
}

void DE_VarSetNumber(DeccanVarManager *manager, const char *name, double value) {
    DeccanVar *var = stbds_shget(manager->vars, name);
    if(var->type == DECCAN_VARTYPE_NUMBER) {
        var->value.number = value;
    }
}

void DE_VarSetString(DeccanVarManager *manager, const char *name, const char *value) {
    DeccanVar *var = stbds_shget(manager->vars, name);
    if(var->type == DECCAN_VARTYPE_STRING) {
        var->value.string = DE_StringNew(value);
    }
}

bool DE_VarGetBool(DeccanVarManager *manager, const char *name) {
    DeccanVar *var = stbds_shget(manager->vars, name);
    if(var->type != DECCAN_VARTYPE_LOGICAL) {
        return false;
    }
    return var->value.logical;
};

double DE_VarGetNumber(DeccanVarManager *manager, const char *name) {
    DeccanVar *var = stbds_shget(manager->vars, name);
    if(var->type != DECCAN_VARTYPE_NUMBER) {
        return 0.0f;
    }
    return var->value.number;
};

char *DE_VarGetString(DeccanVarManager *manager, const char *name) {
    DeccanVar *var = stbds_shget(manager->vars, name);
    if(var->type != DECCAN_VARTYPE_STRING) {
        return NULL;
    }
    return var->value.string;
};
