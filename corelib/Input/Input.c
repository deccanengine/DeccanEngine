/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Input.h"
#include "../Renderer/Camera.h"

static struct { 
    SDL_Event event;
    uint8_t currKeys [SDL_NUM_SCANCODES];
    uint8_t prevKeys [SDL_NUM_SCANCODES];
} Input_Info = {0};

#define KEY_IN_BOUNDS(x)    (x > KeyCode_Unknown1 && x < KeyCodeTotalCount)
#define BUTTON_IN_BOUNDS(x) (x >= ButtonCode_Left && x < ButtonCodeTotalCount)

/////////////////////////////////////////////////
// Input management
////////////////////////////////////////////////

SDL_Event *Input_GetEventHandler() {
    return &Input_Info.event;
}

void Input_Init() {
    memcpy(Input_Info.prevKeys, "\0", sizeof(uint8_t) * (SDL_NUM_SCANCODES - 1));
    memcpy(Input_Info.currKeys, SDL_GetKeyboardState(NULL), sizeof(uint8_t) * (SDL_NUM_SCANCODES - 1));
}

void Input_Update() {
    memcpy(Input_Info.prevKeys, Input_Info.currKeys, sizeof(uint8_t) * (SDL_NUM_SCANCODES - 1));
    memcpy(Input_Info.currKeys, SDL_GetKeyboardState(NULL), sizeof(uint8_t) * (SDL_NUM_SCANCODES - 1));

    Input_Info.event.wheel.x = 0;
    Input_Info.event.wheel.y = 0;
}

/////////////////////////////////////////////////
// Keyboard functions
////////////////////////////////////////////////

KeyState Input_GetKey(int key_code) {
    KeyState key = {
        false, false, false
    };

    if(KEY_IN_BOUNDS(key_code)) {
        if(Input_Info.currKeys[key_code]) { 
            if(!Input_Info.prevKeys[key_code]) { 
                key.IsPressed = true; 
            }
            key.IsHeld = true; 
        }
        else {
            if(Input_Info.prevKeys[key_code]) { 
                key.IsReleased = true; 
            }
        }
    }

    return key;
}

bool Input_KeyPressed(int key_code) {
    if(KEY_IN_BOUNDS(key_code)) {
        return Input_Info.currKeys[key_code] && 
              !Input_Info.prevKeys[key_code];
    }
    else {
        return false;
    }
}

bool Input_KeyReleased(int key_code) {
    if(KEY_IN_BOUNDS(key_code)) {
        return !Input_Info.currKeys[key_code] && 
                Input_Info.prevKeys[key_code];
    }
    else {
        return false;
    }
}

bool Input_KeyHeld(int key_code) {
    if(KEY_IN_BOUNDS(key_code)) {
        return Input_Info.currKeys[key_code];
    }
    else {
        return false;
    }
}

/////////////////////////////////////////////////
// Mouse functions
////////////////////////////////////////////////

MouseState Input_GetMouseButton(int button_code) {
    MouseState button = {
        false, false
    };

    if(BUTTON_IN_BOUNDS(button_code)) {
        if(Input_Info.event.button.button == button_code) {
            if(Input_Info.event.type == SDL_MOUSEBUTTONDOWN) { 
                button.IsDown = true; 
            }
            else if(Input_Info.event.type == SDL_MOUSEBUTTONUP) { 
                button.IsUp = true; 
            }
        }
    }

    return button;
}

bool Input_ButtonDown(int button_code) {
    if(BUTTON_IN_BOUNDS(button_code)) {
        return Input_Info.event.type == SDL_MOUSEBUTTONDOWN &&
               Input_Info.event.button.button == button_code;
    }
    else {
        return false;
    }
}

bool Input_ButtonUp(int button_code) {
    if(BUTTON_IN_BOUNDS(button_code)) {
        return Input_Info.event.type == SDL_MOUSEBUTTONUP &&
            Input_Info.event.button.button == button_code;
    }
    else {
        return false;
    }
}

Vector2 Input_GetMousePos() {
    int32_t x, y;
    SDL_GetMouseState(&x, &y);
    return (Vector2){x, y};
}

Vector2 Input_GetRelativeMousePos() {
    int32_t x, y;
    Vector2 pos;
    Vector2 cam = Camera_GetPosition(); 
    
    SDL_GetMouseState(&x, &y);
    pos.x = (float)x + cam.x;
    pos.y = (float)y + cam.y;
    return pos;
}

int Input_MouseScrollHorizontal() {
    if(Input_Info.event.type == SDL_MOUSEWHEEL) {
        if(Input_Info.event.wheel.direction == SDL_MOUSEWHEEL_NORMAL) { 
            return Input_Info.event.wheel.x; 
        }
        else { 
            return -Input_Info.event.wheel.x; 
        }
    }
    return 0;
}

int Input_MouseScrollVertical() {
    if(Input_Info.event.type == SDL_MOUSEWHEEL) {
        if(Input_Info.event.wheel.direction == SDL_MOUSEWHEEL_NORMAL) { 
            return Input_Info.event.wheel.y; 
        }
        else { 
            return -Input_Info.event.wheel.y;
        }
    }
    return 0;
}