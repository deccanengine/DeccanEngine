/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../Config.h"
#include "Memory.h"

typedef enum DeccanVarType {
    DECCAN_VARTYPE_UNDEFINED = 0,
    DECCAN_VARTYPE_LOGICAL,
    DECCAN_VARTYPE_NUMBER,
    DECCAN_VARTYPE_STRING
} DeccanVarType;

typedef struct DeccanVar {
    DeccanVarType type;
    union {
        struct { bool logical;  };
        struct { double number; };
        struct { char *string;  };
    } value;
} DeccanVar;

typedef struct DeccanVarManager {
    struct vars {
        char *key;
        DeccanVar *value;
    } *vars;
} DeccanVarManager;

void DE_Var_Init(DeccanVarManager *manager);
void DE_Var_New(DeccanVarManager *manager, const char *name, DeccanVarType type);
void DE_Var_Delete(DeccanVarManager *manaer, const char *name);

void DE_Var_SetBool(DeccanVarManager *manager, const char *name, bool value);
void DE_Var_SetNumber(DeccanVarManager *manager, const char *name, double value);
void DE_Var_SetString(DeccanVarManager *manager, const char *name, const char *value);

bool DE_Var_GetBool(DeccanVarManager *manager, const char *name);
double DE_Var_GetNumber(DeccanVarManager *manager, const char *name);
char *DE_Var_GetString(DeccanVarManager *manager, const char *name);


