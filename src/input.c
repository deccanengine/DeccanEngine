/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "input.h"

Deccan_KeyState _priv_Input_get_key(int key_code) {
    Deccan_KeyState key;

    if(_key_states[key_code]) { 
        if(!_prev_keys[key_code]) { key.is_pressed = true; }
        else { key.is_pressed = false; }
        key.is_held = true; 
        key.is_released = false;
    }
    else {
        if(_prev_keys[key_code]) { key.is_released = true; }
        else { key.is_released = false; }
        
        key.is_held = false;
        key.is_pressed = false;
    }

    return key;
}

Deccan_MouseState _priv_Input_get_mouse_button(int button_code) {
    Deccan_MouseState button = {false, false};

    if(Deccan_Core.get_global_engine()->event.type == SDL_MOUSEBUTTONDOWN) {
        if(Deccan_Core.get_global_engine()->event.button.button == button_code) { button.is_down = true; }
        else { button.is_up = true; }
    }

    return button;
}

Deccan_Vector2i _priv_Input_get_mouse_pos() {
    Deccan_Vector2i pos;
    SDL_GetMouseState(&pos.x, &pos.y);
    return pos;
}
