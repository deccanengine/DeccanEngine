/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include "../config.h"

typedef struct DE_msgbuf {
    int msg_count;
    int msg_length;
    int msg_num;
    char **messages;
} DE_msgbuf;

void DE_msg_init(DE_msgbuf *buf, int msg_count, int msg_length);
void DE_msg_send(DE_msgbuf *buf, const char *msg);
bool DE_msg_receive(DE_msgbuf *buf, const char *msg);
void DE_msg_free(DE_msgbuf *buf);