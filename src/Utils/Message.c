/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Config.h>

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
    /* Store the message */
    for(int i=0; i<buf->count; i++) {
        if(!strcmp(buf->messages[i], "\0")) {
            strncpy(buf->messages[i], msg, buf->length);
            buf->num++; return;
        }
    }

    /* Out of space? Store from the 0th index */
    if(buf->num++ > buf->count) { buf->num = 0; }
    strncpy(buf->messages[buf->num], msg, buf->length);
}

bool Msg_Receive(MsgBuf *buf, const char *msg) {
    /* Find the message */
    for(int i=0; i<buf->count; i++) {
        if(!strcmp(buf->messages[i], msg)) {
            strcpy(buf->messages[i], "\0");
            return true;
        }
    }
    /* There is no message */
    return false;
}

void Msg_Free(MsgBuf *buf) {
    for(int i=0; i<buf->count; i++) {
        free(buf->messages[i]);
    }
    free(buf->messages);
}