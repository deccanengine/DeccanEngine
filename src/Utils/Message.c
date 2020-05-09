/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Config.h>

void msg_init(msgbuf *buf, int msg_count, int msg_length) {
    buf->msg_num = 0;
    buf->msg_count = msg_count;
    buf->msg_length = msg_length;
    buf->messages = DE_NEW(char*, msg_count);
    for(int i=0; i<msg_count; i++) {
        buf->messages[i] = DE_NEW(char, msg_length);
        memset(buf->messages[i], '\0', sizeof(char)*msg_length);
    }
}

void msg_send(msgbuf *buf, const char *msg) {
    /* Store the message */
    for(int i=0; i<buf->msg_count; i++) {
        if(!strcmp(buf->messages[i], "\0")) {
            strncpy(buf->messages[i], msg, buf->msg_length);
            buf->msg_num++; return;
        }
    }

    /* Out of space? Store from the 0th index */
    if(buf->msg_num++ > buf->msg_count) { buf->msg_num = 0; }
    strncpy(buf->messages[buf->msg_num], msg, buf->msg_length);
}

bool msg_receive(msgbuf *buf, const char *msg) {
    /* Find the message */
    for(int i=0; i<buf->msg_count; i++) {
        if(!strcmp(buf->messages[i], msg)) {
            strcpy(buf->messages[i], "\0");
            return true;
        }
    }
    /* There is no message */
    return false;
}

void msg_free(msgbuf *buf) {
    for(int i=0; i<buf->msg_count; i++) {
        free(buf->messages[i]);
    }
    free(buf->messages);
}