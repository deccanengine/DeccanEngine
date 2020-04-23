/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "input.h"

Deccan_KeyState _priv_Input_get_key(int key_code) {
    Deccan_KeyState key;
    Deccan_Info *engine = Deccan_Core.get_global_engine();

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

Deccan_MouseState _priv_Input_get_mouse_button(int button_code) {
    Deccan_MouseState button = {false, false};
    Deccan_Info *engine = Deccan_Core.get_global_engine();

    if(engine->event.button.button == button_code) {
        if(engine->event.type == SDL_MOUSEBUTTONDOWN) { button.is_down = true; }
        else if(engine->event.type == SDL_MOUSEBUTTONUP) { button.is_up = true; }
    }

    return button;
}

Deccan_Vector2i _priv_Input_get_mouse_pos() {
    Deccan_Vector2i pos;
    SDL_GetMouseState(&pos.x, &pos.y);
    return pos;
}

Deccan_Vector2i _priv_Input_get_relative_mouse_pos() {
    Deccan_Vector2i pos;
    Deccan_Vector2i cam = Deccan_Core.get_global_engine()->camera; 
    
    SDL_GetMouseState(&pos.x, &pos.y);
    pos.x += cam.x;
    pos.y += cam.y;
    return pos;
}

int _priv_Input_mouse_scroll_horizontal() {
    Deccan_Info *engine = Deccan_Core.get_global_engine();
    if(engine->event.type == SDL_MOUSEWHEEL) {
        if(engine->event.wheel.direction == SDL_MOUSEWHEEL_NORMAL) { return engine->event.wheel.x; }
        else { return -engine->event.wheel.x; }
    }
    return 0;
}

int _priv_Input_mouse_scroll_vertical() {
    Deccan_Info *engine = Deccan_Core.get_global_engine();
    if(engine->event.type == SDL_MOUSEWHEEL) {
        if(engine->event.wheel.direction == SDL_MOUSEWHEEL_NORMAL) { return engine->event.wheel.y; }
        else { return -engine->event.wheel.y ;}
    }
    else { return 0; }
}

bool _priv_Input_key_pressed(int key_code) {
    Deccan_Info *engine = Deccan_Core.get_global_engine();
    return engine->curr_keys[key_code] && !engine->prev_keys[key_code];
}

bool _priv_Input_key_released(int key_code) {
    Deccan_Info *engine = Deccan_Core.get_global_engine();
    return !engine->curr_keys[key_code] && engine->prev_keys[key_code];
}

bool _priv_Input_key_held(int key_code) {
    return Deccan_Core.get_global_engine()->curr_keys[key_code];
}

bool _priv_Input_button_down(int button_code) {
    Deccan_Info *engine = Deccan_Core.get_global_engine();
    return engine->event.type == SDL_MOUSEBUTTONDOWN &&
           engine->event.button.button == button_code;
}

bool _priv_Input_button_up(int button_code) {
    Deccan_Info *engine = Deccan_Core.get_global_engine();
    return engine->event.type == SDL_MOUSEBUTTONUP &&
           engine->event.button.button == button_code;
}