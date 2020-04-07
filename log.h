#pragma once

static void deccan_error(const char *str, ...) {
    va_list args;
    printf("Fatal Error: %s", str);
    va_start(args, str);
    printf("%s", va_arg(args, char*));
    va_end(args);
    printf("\n");
    exit(-1);
}
