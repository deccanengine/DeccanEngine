/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include <deccanengine/core/input/input.h>

DE_PRIV struct {
    SDL_Event event;
    uint8_t currkeys[SDL_NUM_SCANCODES];
    uint8_t prevkeys[SDL_NUM_SCANCODES];
} input_info = {0};

////////////////////////////////////////////////////////////////////////////////

#define KEY_IN_BOUNDS(x) (x > DECCAN_KEY_UNKNOWN1 && x < DECCAN_KEY_TOTAL_COUNT)
#define BUTTON_IN_BOUNDS(x) (x >= DECCAN_BUTTON_LEFT && x < DECCAN_BUTTON_TOTAL_COUNT)

////////////////////////////////////////////////////////////////////////////////
// Input management
////////////////////////////////////////////////////////////////////////////////

DE_IMPL SDL_Event *deccan_input_get_event_handler(void) {
    return &input_info.event;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_input_init(void) {
    memcpy(input_info.prevkeys, "\0", sizeof(uint8_t) * (SDL_NUM_SCANCODES - 1));
    memcpy(input_info.currkeys, SDL_GetKeyboardState(NULL), sizeof(uint8_t) * (SDL_NUM_SCANCODES - 1));
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL void deccan_input_update(void) {
    memcpy(input_info.prevkeys, input_info.currkeys, sizeof(uint8_t) * (SDL_NUM_SCANCODES - 1));
    memcpy(input_info.currkeys, SDL_GetKeyboardState(NULL), sizeof(uint8_t) * (SDL_NUM_SCANCODES - 1));

    input_info.event.wheel.x = 0;
    input_info.event.wheel.y = 0;
}

////////////////////////////////////////////////////////////////////////////////
// Keyboard functions
////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_key_state_t deccan_input_get_key(int key_code) {
    deccan_key_state_t key = {false, false, false};

    if (KEY_IN_BOUNDS(key_code)) {
        if (input_info.currkeys[key_code]) {
            if (!input_info.prevkeys[key_code]) {
                key.IsPressed = true;
            }
            key.IsHeld = true;
        }
        else {
            if (input_info.prevkeys[key_code]) {
                key.IsReleased = true;
            }
        }
    }

    return key;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_input_key_pressed(int key_code) {
    if (KEY_IN_BOUNDS(key_code)) {
        return input_info.currkeys[key_code] && !input_info.prevkeys[key_code];
    }
    else {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_input_key_released(int key_code) {
    if (KEY_IN_BOUNDS(key_code)) {
        return !input_info.currkeys[key_code] && input_info.prevkeys[key_code];
    }
    else {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_input_key_held(int key_code) {
    if (KEY_IN_BOUNDS(key_code)) {
        return input_info.currkeys[key_code];
    }
    else {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Mouse functions
////////////////////////////////////////////////////////////////////////////////

DE_IMPL deccan_mouse_state_t deccan_input_get_mouse_button(int button_code) {
    deccan_mouse_state_t button = {false, false};

    if (BUTTON_IN_BOUNDS(button_code)) {
        if (input_info.event.button.button == button_code) {
            if (input_info.event.type == SDL_MOUSEBUTTONDOWN) {
                button.IsDown = true;
            }
            else if (input_info.event.type == SDL_MOUSEBUTTONUP) {
                button.IsUp = true;
            }
        }
    }

    return button;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_input_button_down(int button_code) {
    if (BUTTON_IN_BOUNDS(button_code)) {
        return input_info.event.type == SDL_MOUSEBUTTONDOWN && input_info.event.button.button == button_code;
    }
    else {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL bool deccan_input_button_up(int button_code) {
    if (BUTTON_IN_BOUNDS(button_code)) {
        return input_info.event.type == SDL_MOUSEBUTTONUP && input_info.event.button.button == button_code;
    }
    else {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL vec2s deccan_input_get_mouse_pos(void) {
    int32_t x, y;
    SDL_GetMouseState(&x, &y);

    return (vec2s){ .x = (float)x, .y = (float)y };
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL int deccan_input_mouse_scroll_horizontal(void) {
    if (input_info.event.type == SDL_MOUSEWHEEL) {
        if (input_info.event.wheel.direction == SDL_MOUSEWHEEL_NORMAL) {
            return input_info.event.wheel.x;
        }
        else {
            return -input_info.event.wheel.x;
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

DE_IMPL int deccan_input_mouse_scroll_vertical(void) {
    if (input_info.event.type == SDL_MOUSEWHEEL) {
        if (input_info.event.wheel.direction == SDL_MOUSEWHEEL_NORMAL) {
            return input_info.event.wheel.y;
        }
        else {
            return -input_info.event.wheel.y;
        }
    }
    return 0;
}
