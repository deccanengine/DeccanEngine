#include "input.h"

deccan_key_state deccan_key_get(int key_code) {
    deccan_key_state key;

    if(deccan_key_states[key_code]) { 
        if(!deccan_prev_keys[key_code]) { key.is_pressed = true; }
        else { key.is_pressed = false; }
        key.is_held = true; 
        key.is_released = false;
    }
    else {
        if(deccan_prev_keys[key_code]) { key.is_released = true; }
        else { key.is_released = false; }
        
        key.is_held = false;
        key.is_pressed = false;
    }

    return key;
}

deccan_mouse_state deccan_mouse_get(int button_code) {
    deccan_mouse_state button = {false, false};

    if(deccan_get_global_engine()->event.type == SDL_MOUSEBUTTONDOWN) {
        if(deccan_get_global_engine()->event.button.button == button_code) { button.is_down = true; }
        else { button.is_up = true; }
    }

    return button;
}

deccan_mouse_pos deccan_mouse_get_pos() {
    deccan_mouse_pos pos;
    SDL_GetMouseState(&pos.x, &pos.y);
    return pos;
}
