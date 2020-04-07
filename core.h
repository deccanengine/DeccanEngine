#pragma once

#include "config.h"
#include "log.h"

#define sdlerr SDL_GetError()
#define ttferr TTF_GetError()

#define state_func_ptr(x) void(*x)(deccan_info*)

/* Forward declaration */
typedef struct deccan_info deccan_info;

typedef struct deccan_info {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    bool is_running;
    bool is_first_frame;

    float required_fps;

    state_func_ptr(at_begining);
    state_func_ptr(at_step);
    state_func_ptr(at_end);
} deccan_info;

int  deccan_init(deccan_info *engine, const char *title, int32_t width, int32_t height);
void deccan_quit(deccan_info *engine);
void deccan_run(deccan_info *engine, float required_fps);

void deccan_set_states(deccan_info *engine, state_func_ptr(ab), state_func_ptr(as), state_func_ptr(ae));
