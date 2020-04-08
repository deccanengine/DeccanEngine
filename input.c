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
        
        key.is_pressed = false;
        key.is_pressed = false;
    }

    return key;
}