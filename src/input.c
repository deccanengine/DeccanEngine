#include "input.h"

deccan_KeyState _priv_Input_get_key(int key_code) {
    deccan_KeyState key;

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

deccan_MouseState _priv_Input_get_mouse_button(int button_code) {
    deccan_MouseState button = {false, false};

    if(deccan_Core.get_global_engine()->event.type == SDL_MOUSEBUTTONDOWN) {
        if(deccan_Core.get_global_engine()->event.button.button == button_code) { button.is_down = true; }
        else { button.is_up = true; }
    }

    return button;
}

deccan_MousePos _priv_Input_get_mouse_pos() {
    deccan_MousePos pos;
    SDL_GetMouseState(&pos.x, &pos.y);
    return pos;
}
