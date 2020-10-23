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
    struct {
        char *key;
        DeccanVar *value;
    } *vars;
} DeccanVarManager;

void DE_VarInit(DeccanVarManager *manager);
void DE_VarQuit(DeccanVarManager *manager);
void DE_VarNew(DeccanVarManager *manager, const char *name, DeccanVarType type);
void DE_VarDelete(DeccanVarManager *manaer, const char *name);

void DE_VarSetBool(DeccanVarManager *manager, const char *name, bool value);
void DE_VarSetNumber(DeccanVarManager *manager, const char *name, double value);
void DE_VarSetString(DeccanVarManager *manager, const char *name, const char *value);

bool DE_VarGetBool(DeccanVarManager *manager, const char *name);
double DE_VarGetNumber(DeccanVarManager *manager, const char *name);
char *DE_VarGetString(DeccanVarManager *manager, const char *name);


