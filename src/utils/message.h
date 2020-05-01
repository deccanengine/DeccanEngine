/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"

typedef struct DE_MsgBuf {
    int msg_count;
    int msg_length;
    int msg_num;
    char **messages;
} DE_MsgBuf;

void DE_Msg_init(DE_MsgBuf *buf, int msg_count, int msg_length);
void DE_Msg_send(DE_MsgBuf *buf, const char *msg);
bool DE_Msg_receive(DE_MsgBuf *buf, const char *msg);