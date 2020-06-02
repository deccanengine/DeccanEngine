#pragma once
#include "Config.h"

typedef struct MsgBuf {
    int count;
    int length;
    int num;
    char **messages;
} MsgBuf;

void Msg_Init(MsgBuf *buf, int count, int length);
void Msg_Send(MsgBuf *buf, const char *msg);
bool Msg_Receive(MsgBuf *buf, const char *msg);
void Msg_Free(MsgBuf *buf);