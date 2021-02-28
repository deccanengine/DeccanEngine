void *DE_Alloc(int, int);
void *DE_Realloc(void *, int);
void DE_Free(void *);

#define STB_IMAGE_IMPLEMENTATION
#define STBI_MALLOC(size) DE_Alloc(size, 1)
#define STBI_REALLOC(ptr, size) DE_Realloc(ptr, size)
#define STBI_REALLOC_SIZED(ptr, oldsize, newsize) DE_Realloc(ptr, newsize)
#define STBI_FREE(ptr) DE_Free(ptr)
#define STBI_NO_TGA
#define STBI_NO_GIF
#define STBI_NO_HDR
#define STBI_NO_PIC
#define STBI_NO_PNM

#define STB_DS_IMPLEMENTATION
#define STBDS_REALLOC(context, ptr, size) DE_Realloc(ptr, size)
#define STBDS_FREE(context, ptr) DE_Free(ptr)

#include <depends/flecs/flecs.c>
#include <depends/log.c/src/log.c>
#include <depends/sx/src/handle.c>
#include <depends/sx/src/sx.c>
#include <depends/sx/src/allocator.c>
#include <depends/sx/src/threads.c>
#include <depends/sx/src/string.c>
#include <depends/sx/src/os.c>

#include "../Config.h"
