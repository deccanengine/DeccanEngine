/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#pragma once
#include <Deccan/Config.h>
#include <Deccan/Core.h>

/* Key Codes */
typedef struct KeyList {
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
} KeyList;

static KeyList Key = { 
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

/* Button Codes */
typedef struct ButtonList {
    int left, middle, right, x1, x2; 
} ButtonList;

static ButtonList Button = {
    1, 2, 3, 4, 5
};

/* Functions and Structs */
typedef struct {
    bool is_pressed;
    bool is_released;
    bool is_held;
} KeyState;

typedef struct {
    bool is_down;
    bool is_up;
} MouseState;

KeyState Input_GetKey(int key_code);
MouseState Input_GetMouseButton(int button_code);
Vector2i Input_GetMousePos();
Vector2f Input_GetRelativeMousePos();
int Input_MouseScrollHorizontal();
int Input_MouseScrollVertical();

bool Input_KeyPressed(int key_code);
bool Input_KeyReleased(int key_code);
bool Input_KeyHeld(int key_code);
bool Input_ButtonDown(int button_code);
bool Input_ButtonUp(int button_code);