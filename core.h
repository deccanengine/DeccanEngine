#pragma once

#include "config.h"
#include "log.h"

#define sdlerr SDL_GetError()
#define ttferr TTF_GetError()

#define state_func_ptr(x) void(*x)(void)

/* Forward declaration */
typedef struct deccan_info {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    bool is_running;
    bool is_first_frame;

    float required_fps;

    uint8_t *key_states;

    state_func_ptr(at_begining);
    state_func_ptr(at_step);
    state_func_ptr(at_end);
} deccan_info;

void deccan_set_global_engine(deccan_info *engine);
deccan_info *deccan_get_global_engine();

int  deccan_init(const char *title, int32_t width, int32_t height);
void deccan_quit();
void deccan_run(float required_fps);

void deccan_set_states(state_func_ptr(ab), state_func_ptr(as), state_func_ptr(ae));
