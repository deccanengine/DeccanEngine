/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once

FILE *logfile;

static void _priv_Log_error(const char *str, ...) {
    va_list args;
    printf("Fatal Error: ");
    va_start(args, str);
    vprintf(str, args);
    va_end(args);
    printf("\n");
    exit(-1);
}

static void _priv_Log_report(const char *str, ...) {
#ifdef DECCAN_REPORTS_ENABLED
    va_list args;
    va_start(args, str);
    vfprintf(logfile, str, args);
    va_end(args);
    fprintf(logfile, "\n");
#endif
}

#ifdef __STDC__

typedef struct _priv_Log {
    void (*error) (const char *str, ...);
    void (*report)(const char *str, ...);
} _priv_Log;

static _priv_Log Deccan_Log = { 
    _priv_Log_error, 
    _priv_Log_report 
};

#elif __cplusplus

#endif