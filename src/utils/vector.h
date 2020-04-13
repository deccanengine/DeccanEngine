#pragma once

#define MAKE_VECTOR2(p,type)         \
typedef struct Deccan_Vector2 ## p { \
    type x, y;                       \
} Deccan_Vector2 ## p;

MAKE_VECTOR2(i, int32_t);
MAKE_VECTOR2(u, uint32_t);
MAKE_VECTOR2(f, float);

#define MAKE_VECTOR3(p,type)         \
typedef struct Deccan_Vector3 ## p { \
    type x, y, z;                    \
} Deccan_Vector3 ## p;

MAKE_VECTOR3(i, int32_t);

#undef MAKE_VECTOR