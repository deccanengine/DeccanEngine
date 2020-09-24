#pragma once
#include "../Config.h"

void *DE_Mem_New(size_t size, int count);
void *DE_Mem_Alloc(size_t size, int count);
void *DE_Mem_Realloc(void *mem, size_t size);
void DE_Mem_Delete(void *mem);

char *DE_String_New(const char *source);
