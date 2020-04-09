#pragma once
#include "config.h"
#include "core.h"

uint8_t _key_states[SDL_NUM_SCANCODES], _prev_keys[SDL_NUM_SCANCODES];

typedef struct {
    bool is_pressed;
    bool is_released;
    bool is_held;
} deccan_KeyState;

typedef struct {
    bool is_down;
    bool is_up;
} deccan_MouseState;

typedef struct {
    int32_t x, y;
} deccan_MousePos;

deccan_KeyState deccan_input_get_key(int key_code);
deccan_MouseState deccan_input_get_mouse_button(int button_code);
deccan_MousePos deccan_input_get_mouse_pos();