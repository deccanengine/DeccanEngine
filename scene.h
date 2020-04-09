#pragma once

#include "config.h"

#define state_func_ptr(x) void(*x)(void)

typedef struct {
    char *name;
    state_func_ptr(at_begining);
    state_func_ptr(at_step);
    state_func_ptr(at_end);
} deccan_scene;

deccan_scene *deccan_new_scene(const char *name, state_func_ptr(ab), state_func_ptr(as), state_func_ptr(ae));
