#pragma once

#include "core.h"

uint8_t deccan_key_states[SDL_NUM_SCANCODES], deccan_prev_keys[SDL_NUM_SCANCODES];

typedef struct {
    bool is_pressed;
    bool is_released;
    bool is_held;
} deccan_key_state;

deccan_key_state deccan_key_get(int key_code);