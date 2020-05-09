/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Input.h>
#include <Deccan/Core.h>

static SDL_Event _input_event;
static uint8_t _input_curr_keys [SDL_NUM_SCANCODES];
static uint8_t _input_prev_keys [SDL_NUM_SCANCODES];

SDL_Event *_input_get_event() {
    return &_input_event;
}

void _input_init() {
    memcpy(_input_prev_keys, "\0", sizeof(uint8_t)*SDL_NUM_SCANCODES);
    memcpy(_input_curr_keys, SDL_GetKeyboardState(NULL), sizeof(uint8_t)*SDL_NUM_SCANCODES);
}

void _input_update() {
    memcpy(_input_prev_keys, _input_curr_keys, sizeof(uint8_t)*SDL_NUM_SCANCODES);
    memcpy(_input_curr_keys, SDL_GetKeyboardState(NULL), sizeof(uint8_t)*SDL_NUM_SCANCODES);
}

KeyState Input_GetKey(int key_code) {
    KeyState key;

    if(_input_curr_keys[key_code]) { 
        if(!_input_prev_keys[key_code]) { key.is_pressed = true; }
        else { key.is_pressed = false; }
        key.is_held = true; 
        key.is_released = false;
    }
    else {
        if(_input_prev_keys[key_code]) { key.is_released = true; }
        else { key.is_released = false; }
        
        key.is_held = false;
        key.is_pressed = false;
    }

    return key;
}

MouseState Input_GetMouseButton(int button_code) {
    MouseState button = {false, false};

    if(_input_event.button.button == button_code) {
        if(_input_event.type == SDL_MOUSEBUTTONDOWN) { button.is_down = true; }
        else if(_input_event.type == SDL_MOUSEBUTTONUP) { button.is_up = true; }
    }

    return button;
}

Vector2i Input_GetMousePos() {
    Vector2i pos;
    SDL_GetMouseState(&pos.x, &pos.y);
    return pos;
}

Vector2f Input_GetRelativeMousePos() {
    int32_t x, y;
    Vector2f pos;
    Vector2f cam = Camera_GetPosition(); 
    
    SDL_GetMouseState(&x, &y);
    pos.x = (float)x + cam.x;
    pos.y = (float)y + cam.y;
    return pos;
}

int Input_MouseScrollHorizontal() {
    if(_input_event.type == SDL_MOUSEWHEEL) {
        if(_input_event.wheel.direction == SDL_MOUSEWHEEL_NORMAL) { return _input_event.wheel.x; }
        else { return -_input_event.wheel.x; }
    }
    return 0;
}

int Input_MouseScrollVertical() {
    if(_input_event.type == SDL_MOUSEWHEEL) {
        if(_input_event.wheel.direction == SDL_MOUSEWHEEL_NORMAL) { return _input_event.wheel.y; }
        else { return -_input_event.wheel.y ;}
    }
    else { return 0; }
}

bool Input_KeyPressed(int key_code) {
    return _input_curr_keys[key_code] && !_input_prev_keys[key_code];
}

bool Input_KeyReleased(int key_code) {
    return !_input_curr_keys[key_code] && _input_prev_keys[key_code];
}

bool Input_KeyHeld(int key_code) {
    return _input_curr_keys[key_code];
}

bool Input_ButtonDown(int button_code) {
    return _input_event.type == SDL_MOUSEBUTTONDOWN &&
           _input_event.button.button == button_code;
}

bool Input_ButtonUp(int button_code) {
    return _input_event.type == SDL_MOUSEBUTTONUP &&
           _input_event.button.button == button_code;
}