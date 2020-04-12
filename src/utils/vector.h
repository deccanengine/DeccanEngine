#pragma once

#define MAKE_VECTOR(p,type)   \
typedef struct Deccan_Vector2 ## p { \
    type x, y;                \
} Deccan_Vector2 ## p;

MAKE_VECTOR(i, int32_t);
MAKE_VECTOR(u, uint32_t);
MAKE_VECTOR(f, float);

#undef MAKE_VECTOR