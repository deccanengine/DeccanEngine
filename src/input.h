#pragma once
#include "config.h"
#include "core.h"

uint8_t _key_states[SDL_NUM_SCANCODES], _prev_keys[SDL_NUM_SCANCODES];

typedef struct _key_code_list {
    int unknown, 
        
        a, b, c, d, e, f, 
        g, h, i, j, k, l, 
        m, n, o, p, q, r, 
        s, t, u, v, w, x, 
        y, z,
        
        num0, num1, num2, num3, num4,
        num5, num6, num7, num8, num9,
        
        enter,     escape,    backspace, 
        tab,       space,     minus, 
        equals,    lbrac,     rbrac, 
        backslash, semicolon, apostrophe, 
        grave,     comma,     period, 
        slash,     caps,

        f1, f2, f3,  f4,  f5,  f6, 
        f7, f8, f9, f10, f11, f12,

        printscreen, scrolllock, pause,
        insert,      home,       pageup, 
        del,         end,        pagedown, 
        right,       left,       down, 
        up;
} _key_code_list;

static _key_code_list deccan_key = { 
     0, 
     4,  5,  6,  7,  8,  9,
    10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21,
    22, 23, 24, 25, 26, 27,
    28, 29, 
    30, 31, 32, 33, 34, 
    35, 36, 37, 38, 39,

    40, 41, 42, 43, 44, 45,
    46, 47, 48, 49, 51, 52, 
    53, 54, 55, 56, 57,

    58, 59, 60, 61, 62, 63, 
    64, 65, 66, 67, 68, 69,

    70, 71, 72, 73, 74, 75,
    76, 77, 78, 79, 80, 81,
    82
};

typedef struct _button_code_list {
    int left, middle, right, x1, x2; 
} _button_code_list;

static _button_code_list deccan_button = {
    1, 2, 3, 4, 5
};

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