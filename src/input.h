#pragma once
#include "config.h"
#include "core.h"

uint8_t deccan_key_states[SDL_NUM_SCANCODES], deccan_prev_keys[SDL_NUM_SCANCODES];

typedef struct {
    bool is_pressed;
    bool is_released;
    bool is_held;
} deccan_key_state;

typedef struct {
    bool is_down;
    bool is_up;
} deccan_mouse_state;

typedef struct {
    int32_t x, y;
} deccan_mouse_pos;

deccan_key_state deccan_key_get(int key_code);
deccan_mouse_state deccan_mouse_get(int button_code);
deccan_mouse_pos deccan_mouse_get_pos();