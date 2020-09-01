/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Variable.h"

void DE_Var_Init(DeccanVarManager *manager) {
    manager->vars = NULL;
}

void DE_Var_New(DeccanVarManager *manager, const char *name, DeccanVarType type) {
    DeccanVar *var = DE_Mem_New(sizeof(DeccanVar), 1);
    var->type = type;

    stbds_shput(manager->vars, name, var);
}

void DE_Var_Delete(DeccanVarManager *manager, const char *name) {
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

void DE_Var_SetBool(DeccanVarManager *manager, const char *name, bool value) {
    DeccanVar *var = stbds_shget(manager->vars, name);
    if(var->type == DECCAN_VARTYPE_LOGICAL) {
        var->value.logical = value;
    }
}

void DE_Var_SetNumber(DeccanVarManager *manager, const char *name, double value) {
    DeccanVar *var = stbds_shget(manager->vars, name);
    if(var->type == DECCAN_VARTYPE_NUMBER) {
        var->value.number = value;
    }
}

void DE_Var_SetString(DeccanVarManager *manager, const char *name, const char *value) {
    DeccanVar *var = stbds_shget(manager->vars, name);
    if(var->type == DECCAN_VARTYPE_STRING) {
        var->value.string = DE_String_New(value);
    }
}

bool DE_Var_GetBool(DeccanVarManager *manager, const char *name) {
    DeccanVar *var = stbds_shget(manager->vars, name);
    if(var->type != DECCAN_VARTYPE_LOGICAL) {
        return false;
    }
    return var->value.logical;
};

double DE_Var_GetNumber(DeccanVarManager *manager, const char *name) {
    DeccanVar *var = stbds_shget(manager->vars, name);
    if(var->type != DECCAN_VARTYPE_NUMBER) {
        return 0.0f;
    }
    return var->value.number;
};

char *DE_Var_GetString(DeccanVarManager *manager, const char *name) {
    DeccanVar *var = stbds_shget(manager->vars, name);
    if(var->type != DECCAN_VARTYPE_STRING) {
        return NULL;
    }
    return var->value.string;
};
