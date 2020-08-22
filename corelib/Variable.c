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
    DeccanVar *var = DE_NEW(DeccanVar, 1);
    var->type = type;

    stbds_shput(manager->vars, name, var);
}

void DE_Var_Delete(DeccanVarManager *manager, const char *name) {
    //
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
        var->value.string = DE_NEWSTRING(value);
    }
}

bool DE_Var_GetNumber(DeccanVarManager *manager, const char *name) {
    DeccanVar *var = stbds_shget(manager->vars, name);
    if(var->type != DECCAN_VARTYPE_LOGICAL) {

    }

    return var->value.logical;
};

double DE_Var_GetNumber(DeccanVarManager *manager, const char *name) {
    DeccanVar *var = stbds_shget(manager->vars, name);
    if(var->type != DECCAN_VARTYPE_NUMBER) {

    }

    return var->value.number;
};

char *DE_Var_GetNumber(DeccanVarManager *manager, const char *name) {
    DeccanVar *var = stbds_shget(manager->vars, name);
    if(var->type != DECCAN_VARTYPE_STRING) {

    }

    return var->value.string;
};

/*
void Msg_Init(MsgBuf *buf, int count, int length) {
    buf->num = 0;
    buf->count = count;
    buf->length = length;
    buf->messages = DE_NEW(char*, count);
    for(int i=0; i<count; i++) {
        buf->messages[i] = DE_NEW(char, length);
        memset(buf->messages[i], '\0', sizeof(char) * length);
    }
}

void Msg_Send(MsgBuf *buf, const char *msg) {
    for(int i=0; i<buf->count; i++) {
        if(!strcmp(buf->messages[i], "\0")) {
            strncpy(buf->messages[i], msg, buf->length);
            buf->num++; return;
        }
    }

    if(buf->num++ > buf->count) { buf->num = 0; }
    strncpy(buf->messages[buf->num], msg, buf->length);
}

bool Msg_Receive(MsgBuf *buf, const char *msg) {
    for(int i=0; i<buf->count; i++) {
        if(!strcmp(buf->messages[i], msg)) {
            strcpy(buf->messages[i], "\0");
            return true;
        }
    }
    return false;
}

void Msg_Free(MsgBuf *buf) {
    if(buf == NULL || buf->messages == NULL) {
        return;
    }

    for(int i=0; i<buf->count; i++) {
        if(buf->messages[i] != NULL) {
            free(buf->messages[i]);
            buf->messages[i] = NULL;
        }
    }

    free(buf->messages);
    buf->messages = NULL;
}*/
