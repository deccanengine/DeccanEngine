#include "Memory.h"

void *DE_Mem_New(size_t size, int count) {
    return malloc(size * count);
}

void DE_Mem_Delete(void *mem) {
    if(!mem) return;
    else {
        free(mem);
        mem = NULL;
    }
}

char *DE_String_New(const char *source) {
    size_t len = strlen(source);
	char *string = DE_Mem_New(sizeof(char), len + 1);
    strncpy(string, source, len);
	string[len] = '\0';
    return string;
}
