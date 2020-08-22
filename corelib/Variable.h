#pragma once
#include "Config.h"

/*
typedef struct MsgBuf {
    int count;
    int length;
    int num;
    char **messages;
} MsgBuf;
*/

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

//void DE_Var_Init(DeccanVarManager *manager);
void DE_Var_New(DeccanVarManager *manager, const char *name, DeccanVarType type);
void DE_Var_SetBool(DeccanVarManager *manager, const char *name, bool value);
void DE_Var_SetNumber(DeccanVarManager *manager, const char *name, double value);
void DE_Var_SetString(DeccanVarManager *manager, const char *name, const char *value);

/*
void Msg_Init(MsgBuf *buf, int count, int length);
void Msg_Send(MsgBuf *buf, const char *msg);
bool Msg_Receive(MsgBuf *buf, const char *msg);
void Msg_Free(MsgBuf *buf);
*/
