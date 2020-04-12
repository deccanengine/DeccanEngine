#pragma once

static void _priv_error(const char *str, ...) {
    va_list args;
    printf("Fatal Error: %s: ", str);
    va_start(args, str);
    printf("%s", va_arg(args, char*));
    va_end(args);
    printf("\n");
    exit(-1);
}

typedef struct _priv_Log {
    void (*error)(const char *str, ...);
} _priv_Log;

static _priv_Log Deccan_Log = { _priv_error };