#pragma once
#include <Deccan/Config.h>

typedef struct DE_Rect {
    float x, y, w, h;
} DE_Rect;

typedef struct DE_PosRect {
    float x1, y1, x2, y2;
} DE_PosRect;

typedef struct DE_Circle {
    float x, y, radius;
} DE_Circle;

#define MAKE_VECTOR2(p,type)         \
typedef struct DE_Vector2 ## p { \
    type x, y;                       \
} DE_Vector2 ## p;

MAKE_VECTOR2(i, int32_t);
MAKE_VECTOR2(u, uint32_t);
MAKE_VECTOR2(f, float);

#define MAKE_VECTOR3(p,type)         \
typedef struct DE_Vector3 ## p { \
    type x, y, z;                    \
} DE_Vector3 ## p;

MAKE_VECTOR3(i, int32_t);

#undef MAKE_VECTOR

typedef struct DE_msgbuf {
    int msg_count;
    int msg_length;
    int msg_num;
    char **messages;
} DE_msgbuf;

void DE_msg_init(DE_msgbuf *buf, int msg_count, int msg_length);
void DE_msg_send(DE_msgbuf *buf, const char *msg);
bool DE_msg_receive(DE_msgbuf *buf, const char *msg);
void DE_msg_free(DE_msgbuf *buf);

typedef struct DE_Timer DE_Timer;
typedef struct DE_Timer {
    float start_ticks, paused_ticks;
    bool is_running, is_paused;

    void (*Start)(DE_Timer *timer);
    void (*Stop) (DE_Timer *timer);
    void (*Pause)(DE_Timer *timer);
    void (*Reset)(DE_Timer *timer);
    float (*GetTime)(DE_Timer *timer);
    float (*GetTimeMS)(DE_Timer *timer);
} DE_Timer;

static inline void DE_Clock_Delay(int32_t ms) { SDL_Delay(ms); }
DE_Timer DE_Clock_NewTimer();