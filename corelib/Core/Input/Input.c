/* Deccan Game Engine - C11 2D SDL Game Engine.
 * Copyright 2020, 2021 Ayush Bardhan Tripathy
 *
 * This software is licensed under MIT License.
 * See LICENSE.md included with this package for more info.
 */

#include "Input.h"

DE_PRIV struct {
    SDL_Event event;
    uint8_t currKeys [SDL_NUM_SCANCODES];
    uint8_t prevKeys [SDL_NUM_SCANCODES];
} Input_Info = {0};

#define KEY_IN_BOUNDS(x)    (x > DECCAN_KEY_UNKNOWN1 && x < DECCAN_KEY_TOTAL_COUNT)
#define BUTTON_IN_BOUNDS(x) (x >= DECCAN_BUTTON_LEFT && x < DECCAN_BUTTON_TOTAL_COUNT)

/////////////////////////////////////////////////
// Input management
////////////////////////////////////////////////

DE_IMPL SDL_Event *DE_InputGetEventHandler(void) {
    return &Input_Info.event;
}

DE_IMPL void DE_InputInit(void) {
    memcpy(Input_Info.prevKeys, "\0", sizeof(uint8_t) * (SDL_NUM_SCANCODES - 1));
    memcpy(Input_Info.currKeys, SDL_GetKeyboardState(NULL), sizeof(uint8_t) * (SDL_NUM_SCANCODES - 1));
}

DE_IMPL void DE_InputUpdate(void) {
    memcpy(Input_Info.prevKeys, Input_Info.currKeys, sizeof(uint8_t) * (SDL_NUM_SCANCODES - 1));
    memcpy(Input_Info.currKeys, SDL_GetKeyboardState(NULL), sizeof(uint8_t) * (SDL_NUM_SCANCODES - 1));

    Input_Info.event.wheel.x = 0;
    Input_Info.event.wheel.y = 0;
}

/////////////////////////////////////////////////
// Keyboard functions
////////////////////////////////////////////////

DE_IMPL DeccanKeyState DE_InputGetKey(int key_code) {
    DeccanKeyState key = {
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

DE_IMPL bool DE_InputKeyPressed(int key_code) {
    if(KEY_IN_BOUNDS(key_code)) {
        return Input_Info.currKeys[key_code] &&
              !Input_Info.prevKeys[key_code];
    }
    else {
        return false;
    }
}

DE_IMPL bool DE_InputKeyReleased(int key_code) {
    if(KEY_IN_BOUNDS(key_code)) {
        return !Input_Info.currKeys[key_code] &&
                Input_Info.prevKeys[key_code];
    }
    else {
        return false;
    }
}

DE_IMPL bool DE_InputKeyHeld(int key_code) {
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

DE_IMPL DeccanMouseState DE_InputGetMouseButton(int button_code) {
    DeccanMouseState button = {
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

DE_IMPL bool DE_InputButtonDown(int button_code) {
    if(BUTTON_IN_BOUNDS(button_code)) {
        return Input_Info.event.type == SDL_MOUSEBUTTONDOWN &&
               Input_Info.event.button.button == button_code;
    }
    else {
        return false;
    }
}

DE_IMPL bool DE_InputButtonUp(int button_code) {
    if(BUTTON_IN_BOUNDS(button_code)) {
        return Input_Info.event.type == SDL_MOUSEBUTTONUP &&
            Input_Info.event.button.button == button_code;
    }
    else {
        return false;
    }
}

DE_IMPL void DE_InputGetMousePos(vec2 pos) {
    int32_t x, y;
    SDL_GetMouseState(&x, &y);
    pos[0] = (float)x;
    pos[1] = (float)y;
}

DE_IMPL int DE_InputMouseScrollHorizontal(void) {
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

DE_IMPL int DE_InputMouseScrollVertical(void) {
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
