/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <Deccan/Input.h>

KeyState Input_GetKey(int key_code) {
    KeyState key;
    GameInfo *engine = Core_GetGlobalInfo();

    if(engine->curr_keys[key_code]) { 
        if(!engine->prev_keys[key_code]) { key.is_pressed = true; }
        else { key.is_pressed = false; }
        key.is_held = true; 
        key.is_released = false;
    }
    else {
        if(engine->prev_keys[key_code]) { key.is_released = true; }
        else { key.is_released = false; }
        
        key.is_held = false;
        key.is_pressed = false;
    }

    return key;
}

MouseState Input_GetMouseButton(int button_code) {
    MouseState button = {false, false};
    GameInfo *engine = Core_GetGlobalInfo();

    if(engine->event.button.button == button_code) {
        if(engine->event.type == SDL_MOUSEBUTTONDOWN) { button.is_down = true; }
        else if(engine->event.type == SDL_MOUSEBUTTONUP) { button.is_up = true; }
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
    Vector2f cam = Core_GetGlobalInfo()->camera; 
    
    SDL_GetMouseState(&x, &y);
    pos.x = (float)x + cam.x;
    pos.y = (float)y + cam.y;
    return pos;
}

int Input_MouseScrollHorizontal() {
    GameInfo *engine = Core_GetGlobalInfo();
    if(engine->event.type == SDL_MOUSEWHEEL) {
        if(engine->event.wheel.direction == SDL_MOUSEWHEEL_NORMAL) { return engine->event.wheel.x; }
        else { return -engine->event.wheel.x; }
    }
    return 0;
}

int Input_MouseScrollVertical() {
    GameInfo *engine = Core_GetGlobalInfo();
    if(engine->event.type == SDL_MOUSEWHEEL) {
        if(engine->event.wheel.direction == SDL_MOUSEWHEEL_NORMAL) { return engine->event.wheel.y; }
        else { return -engine->event.wheel.y ;}
    }
    else { return 0; }
}

bool Input_KeyPressed(int key_code) {
    GameInfo *engine = Core_GetGlobalInfo();
    return engine->curr_keys[key_code] && !engine->prev_keys[key_code];
}

bool Input_KeyReleased(int key_code) {
    GameInfo *engine = Core_GetGlobalInfo();
    return !engine->curr_keys[key_code] && engine->prev_keys[key_code];
}

bool Input_KeyHeld(int key_code) {
    return Core_GetGlobalInfo()->curr_keys[key_code];
}

bool Input_ButtonDown(int button_code) {
    GameInfo *engine = Core_GetGlobalInfo();
    return engine->event.type == SDL_MOUSEBUTTONDOWN &&
           engine->event.button.button == button_code;
}

bool Input_ButtonUp(int button_code) {
    GameInfo *engine = Core_GetGlobalInfo();
    return engine->event.type == SDL_MOUSEBUTTONUP &&
           engine->event.button.button == button_code;
}